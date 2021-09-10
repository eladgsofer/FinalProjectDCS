#include "TFC.h"
#include "mcg.h"
#include "servo.h"

#define TRIGGER_MODULO_REGISTER 0xC350 - 1 // 50,000

char ready;

//-----------------------------------------------------------------
//  UART0 configuration
//-----------------------------------------------------------------
void InitUARTs(int baudRate){
	
    SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; // Make sure clock for PORTA is enabled
    SIM_SCGC4 |= SIM_SCGC4_UART0_MASK; // Enable peripheral clock
 
	PORTA_PCR1 = PORT_PCR_MUX(2) | PORT_PCR_DSE_MASK;  // RX 
	PORTA_PCR2 = PORT_PCR_MUX(2) | PORT_PCR_DSE_MASK;  // TX
	
	//Select PLL/2 Clock
	SIM_SOPT2 &= ~(3<<26);
	SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1); 
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
	
	//We have to feed this function the clock in KHz!
	Uart0_Br_Sbr(CORE_CLOCK/2/1000, baudRate);
	 //Enable receive interrupts
     
	UART0_C2 = UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK | UART_C2_RIE_MASK; // Enable Transmitter, Receiver, Receive interrupt
	set_irq_priority(INT_UART0-16,0);
	enable_irq(INT_UART0-16);
	
}

//--------------------------------------------------------------------
//  UART0 - Selection of BR (Baud Rate) and OSR (Over Sampling Ratio)
//--------------------------------------------------------------------
void Uart0_Br_Sbr(int sysclk, int baud){
	
    uint8 i;
    uint32 calculated_baud = 0;
    uint32 baud_diff = 0;
    uint32 osr_val = 0;
    uint32 sbr_val, uart0clk;
    uint32 baud_rate;
    uint32 reg_temp = 0;
    uint32 temp = 0;
    
    SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
    
    // Disable UART0 before changing registers
    UART0_C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);
  
    // Verify that a valid clock value has been passed to the function 
    if ((sysclk > 50000) || (sysclk < 32))
    {
        sysclk = 0;
        reg_temp = SIM_SOPT2;
        reg_temp &= ~SIM_SOPT2_UART0SRC_MASK;
        reg_temp |= SIM_SOPT2_UART0SRC(0);
        SIM_SOPT2 = reg_temp;
			
			  // Enter infinite loop because the 
			  // the desired system clock value is 
			  // invalid!!
			  while(1);
				
    }
   
    
    // Initialize baud rate
    baud_rate = baud;
    
    // Change units to Hz
    uart0clk = sysclk * 1000;
    // Calculate the first baud rate using the lowest OSR value possible.  
    i = 4;
    sbr_val = (uint32)(uart0clk/(baud_rate * i));
    calculated_baud = (uart0clk / (i * sbr_val));
        
    if (calculated_baud > baud_rate)
        baud_diff = calculated_baud - baud_rate;
    else
        baud_diff = baud_rate - calculated_baud;
    
    osr_val = i;
        
    // Select the best OSR value
    for (i = 5; i <= 32; i++)
    {
        sbr_val = (uint32)(uart0clk/(baud_rate * i));
        calculated_baud = (uart0clk / (i * sbr_val));
        
        if (calculated_baud > baud_rate)
            temp = calculated_baud - baud_rate;
        else
            temp = baud_rate - calculated_baud;
        
        if (temp <= baud_diff)
        {
            baud_diff = temp;
            osr_val = i; 
        }
    }
    
    if (baud_diff < ((baud_rate / 100) * 3))
    {
        // If the OSR is between 4x and 8x then both
        // edge sampling MUST be turned on.  
        if ((osr_val >3) && (osr_val < 9))
            UART0_C5|= UART0_C5_BOTHEDGE_MASK;
        
        // Setup OSR value 
        reg_temp = UART0_C4;
        reg_temp &= ~UART0_C4_OSR_MASK;
        reg_temp |= UART0_C4_OSR(osr_val-1);
    
        // Write reg_temp to C4 register
        UART0_C4 = reg_temp;
        
        reg_temp = (reg_temp & UART0_C4_OSR_MASK) + 1;
        sbr_val = (uint32)((uart0clk)/(baud_rate * (reg_temp)));
        
         /* Save off the current value of the uartx_BDH except for the SBR field */
        reg_temp = UART0_BDH & ~(UART0_BDH_SBR(0x1F));
   
        UART0_BDH = reg_temp |  UART0_BDH_SBR(((sbr_val & 0x1F00) >> 8));
        UART0_BDL = (uint8)(sbr_val & UART0_BDL_SBR_MASK);
        
        /* Enable receiver and transmitter */
        UART0_C2 |= (UART0_C2_TE_MASK
                    | UART0_C2_RE_MASK );
    }
    else
		{
        // Unacceptable baud rate difference
        // More than 3% difference!!
        // Enter infinite loop!
        while(1);
			
		}					
    
}


// set I/O for switches and LEDs
void InitGPIO()
{
	//enable Clocks to all ports - page 206, enable clock to Ports
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
	
	//Setup Pins as Timer Output PWM
	PORTE_PCR22 	= PORT_PCR_MUX(3)| PORT_PCR_DSE_MASK; 	//PTE22 pin TMP2_CH0 - ALT3, Edge Aligned PWM,	Trigger
	PORTE_PCR29 	= PORT_PCR_MUX(3); 						//PTE29 pin TMP0_CH2 - ALT3, input-capture,		Echo
	PORTA_PCR12 	= PORT_PCR_MUX(3) | PORT_PCR_DSE_MASK;	//PTA12 pin TPM1_CH0 - ALT3, Edge Aligned PWM
		
	//GPIO Configuration - LEDs - Output
	PORTD_PCR1 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;  //Blue
	GPIOD_PDDR |= BLUE_LED_LOC; //Setup as output pin	
	PORTB_PCR18 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; //Red  
	PORTB_PCR19 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; //Green
	GPIOB_PDDR |= RED_LED_LOC + GREEN_LED_LOC; //Setup as output pins
	
	//GPIO Configuration - DIP Switches - Input
	PORTC_PCR4 = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK ; // assign PTC4 as GPIO
	PORTC_PCR5 = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK ; // assign PTC5 as GPIO
	PORTC_PCR6 = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK ; // assign PTC6 as GPIO
	//Configure ports to input
	GPIOC_PDDR &= ~PORT_LOC(4);
	GPIOC_PDDR &= ~PORT_LOC(5);
	GPIOC_PDDR &= ~PORT_LOC(6);
	
	//GPIO Configuration - Pushbutton - Input
	PORTD_PCR7 = PORT_PCR_MUX(1); // assign PTD7 as GPIO
	PORTD_PCR6 = PORT_PCR_MUX(1); // assign PTD6 as GPIO
	GPIOD_PDDR &= ~PORT_LOC(7);  // PTD7 is Input
	GPIOD_PDDR &= ~PORT_LOC(6);  // PTD6 is Input
	PORTD_PCR7 |= PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_PFE_MASK | PORT_PCR_IRQC(0x0a);
	PORTD_PCR6 |= PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_PFE_MASK | PORT_PCR_IRQC(0x0a);
	enable_irq(INT_PORTD-16); // Enable Interrupts 
	set_irq_priority (INT_PORTD-16,0);  // Interrupt priority = 0 = max
	

	//GPIO Configuration - LCD - Input
	PORTB_PCR0 = PORT_PCR_MUX(1); // assign  as GPIO (DB4) PTB0
	PORTB_PCR1 = PORT_PCR_MUX(1); // assign  as GPIO (DB5) PTB1
	PORTB_PCR2 = PORT_PCR_MUX(1); // assign  as GPIO (DB6) PTB2
	PORTB_PCR3 = PORT_PCR_MUX(1); // assign  as GPIO (DB7) PTB3
	
	GPIOB_PDDR |= 0x0F;
		
	PORTE_PCR3 = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK ; // assign  as GPIO (RS) Pin4 LCD -> PTE3
	PORTE_PCR4 = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK ; // assign  as GPIO (R/W) PIN5 -> PTE4
	PORTE_PCR5 = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK ; // assign  as GPIO (E) PTE5
}
//-----------------------------------------------------------------
// DipSwitch data reading
//-----------------------------------------------------------------
uint8_t TFC_GetDIP_Switch()
{
	uint8_t DIP_Val=0;
	
	DIP_Val = (GPIOC_PDIR>>4) & 0xF;

	return DIP_Val;
}
//-----------------------------------------------------------------
// TPMx - Initialization
//-----------------------------------------------------------------
void InitTPMx(char x){  // x={0,1,2}
	switch(x){ 
	case 0: // Echo
		
		TPM0_SC = 0; // to ensure that the counter is not running
		TPM0_SC = TPM_SC_PS(5); //Prescaler = 32, up-mode, counter-disable
		TPM0_MOD = 0xFFFF;
		TPM0_C2SC = 0;
		TPM0_C2SC |= TPM_CnSC_ELSA_MASK + TPM_CnSC_ELSB_MASK + TPM_CnSC_CHIE_MASK;	//capture triggered on edge
		
		TPM0_CONF = TPM_CONF_DBGMODE(3);
		
		TPM0_C2V = 0;
		enable_irq(INT_TPM0-16); // Enable Interrupts 
		set_irq_priority (INT_TPM0-16,0);  // Interrupt priority = 0 = max
		break;
		
	case 1: // Servo
		
		TPM1_SC = 0; // to ensure that the counter is not running
		TPM1_SC |= TPM_SC_PS(6) + TPM_SC_TOIE_MASK; //Prescaler =64, up-mode, counter-disable
		// TPM period = (MOD + 1) * CounterClock_period
		TPM1_MOD = MOTOR_MUDULO_REGISTER; // PWM frequency of 40Hz = 24MHz/(16x60,000)
		TPM1_C0SC = 0;
		// Edge Aligned , High-True pulse, channel interrupts enabled
		TPM1_C0SC |= TPM_CnSC_MSB_MASK + TPM_CnSC_ELSB_MASK + TPM_CnSC_CHIE_MASK;
		TPM1_C0V = (int)((MIN_T_ON / WAVE_PERIOD) * MOTOR_MUDULO_REGISTER);
		TPM1_CONF = 0;//TPM_CONF_DBGMODE(3); //LPTPM counter continues in debug mode
		
		break;
	case 2: // Trigger
		
		TPM2_SC = 0; // to ensure that the counter is not running
		TPM2_SC |= TPM_SC_PS(5) + TPM_SC_TOIE_MASK;  //Prescaler = 32, up-mode, counter-disable
		// TPM period = (MOD + 1) * CounterClock_period
		TPM2_MOD = TRIGGER_MODULO_REGISTER;  // PWM frequency of 15Hz = 24MHz/(32x50,000)
		TPM2_C0SC = 0;
		// Edge Aligned , High-True pulse, channel interrupts enabled
		TPM2_C0SC |= TPM_CnSC_MSB_MASK + TPM_CnSC_ELSB_MASK + TPM_CnSC_CHIE_MASK;
		TPM2_C0V = 0xA; // Duty Cycle( > 10us)
		TPM2_CONF = 0;
		break;
	}
}

void clearTPMxCNT(char x)
{
	switch (x) {
	case 0:
		TPM0_CNT = 0xFFFF;
		break;
	case 1:
		TPM1_CNT = 0xFFFF;
		break;
	case 2:
		TPM2_CNT = 0xFFFF;
		break;
	}
}

void SetTPMxDutyCycle(char x, int dutyCycle) {

	switch (x) {
	case 0:
		break;
	case 1:
		TPM1_C0V = dutyCycle;
		break;
	case 2:
		TPM2_C1V = dutyCycle;
		break;
	}
}

//-----------------------------------------------------------------
// Start TPMx
//-----------------------------------------------------------------
void StartTPMx(char x, int start) {
	switch (x) {
	case 0:
		if (start)
			TPM0_SC |= TPM_SC_CMOD(1); //Start the TPM0 counter
		else
			TPM0_SC &= ~TPM_SC_CMOD(1); //Stop the TPM0 counter
		break;
	case 1:
		if (start)
			TPM1_SC |= TPM_SC_CMOD(1); //Start the TPM1 counter
		else
			TPM1_SC &= ~TPM_SC_CMOD(1); //Stop the TPM1 counter
		break;
	case 2:
		if (start)
			TPM2_SC |= TPM_SC_CMOD(1); //Start the TPM2 counter
		else
			TPM2_SC &= ~TPM_SC_CMOD(1); //Stop the TPM2 counter
		break;
	}
}
void clearTPM0() {
	TPM0_CNT = 0;
	TPM0_C2V = 0;
}

//-----------------------------------------------------------------
// TPMx - Clock Setup
//-----------------------------------------------------------------
void ClockSetupTPM(){
	    
	pll_init(8000000, LOW_POWER, CRYSTAL,4,24,MCGOUT); //Core Clock is now at 48MHz using the 8MHZ Crystal
	
	//Clock Setup for the TPM requires a couple steps.
	//1st,  set the clock mux
	//See Page 124 of f the KL25 Sub-Family Reference Manual
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;// We Want MCGPLLCLK/2=24MHz (See Page 196 of the KL25 Sub-Family Reference Manual
	SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); //We want the MCGPLLCLK/2 (See Page 196 of the KL25 Sub-Family Reference Manual
	//Enable the Clock to the TPM0 and PIT Modules
	//See Page 207 of f the KL25 Sub-Family Reference Manual
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK + SIM_SCGC6_TPM1_MASK + SIM_SCGC6_TPM2_MASK;
	// TPM_clock = 24MHz	    
}


//-----------------------------------------------------------------
// PIT - Initialisation
//-----------------------------------------------------------------
void InitPIT(){
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK; //Enable the Clock to the PIT Modules
	// Timer 0
	PIT_LDVAL0 = 0x00186A00; // setup timer 0 for 15hz counting period
	//PIT_TCTRL0 = PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK; //enable PIT0 and its interrupt
	PIT_MCR |= PIT_MCR_FRZ_MASK; // stop the pit when in debug mode
	PIT_MCR &= ~PIT_MCR_MDIS_MASK;
	
	enable_irq(INT_PIT-16); //  //Enable PIT IRQ on the NVIC
	set_irq_priority(INT_PIT-16,0);  // Interrupt priority = 0 = max
}
//------------------------------------------------------------------
// PIT Config
//------------------------------------------------------------------
void set_PIT_max_val(int ms)
{
	unsigned int timer_val = ms*24000; //calc timer start value
	PIT_LDVAL0 = timer_val;
}

void PIT_enable(int start)
{
	if(start)
	{
		PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
	}
	else if(!start)
	{
		PIT_TCTRL0 &= ~(PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK);
	}
}

//------------------------------------------------------------------
//		DMA
//------------------------------------------------------------------
void dma_init(void)
{
	
	// Enable clocks
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;
	
	// Disable DMA Mux channels
	DMAMUX0_CHCFG0 = 0x00;
	DMAMUX0_CHCFG1 = 0x00;
	
	// Configure DMA0
	DMA_DSR_BCR0 = DMA_DSR_BCR_DONE_MASK;
	DMA_SAR0 = (uint32_t)&UART0_D;
	
	DMA_DCR0 |= (DMA_DCR_EINT_MASK|		// Enable interrupt
				 DMA_DCR_ERQ_MASK |		// Enable peripheral request
				 DMA_DCR_CS_MASK  |		// Cycle Steal
				 DMA_DCR_SSIZE(1) |		// Set source size to 8 bits = 1 byte
				 DMA_DCR_DINC_MASK|		// Set increments to destination address
				 DMA_DCR_DMOD(15)  |     // Destination address modulo of 2K Bytes
				 DMA_DCR_DSIZE(1));		// Set destination size of 8 bits = 1 byte 
				 
	
	//Config DMA Mux for UART0  receiver operation, Enable DMA channel and source
	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_SOURCE(2); // Set UART0 receiver as source
	
	// Configure DMA1
	DMA_DSR_BCR1 = DMA_DSR_BCR_DONE_MASK;
	DMA_DAR1 = (uint32_t)&UART0_D;
 
	
	DMA_DCR1 |= (DMA_DCR_EINT_MASK|		// Enable interrupt
				 DMA_DCR_ERQ_MASK |		// Enable peripheral request
				 DMA_DCR_CS_MASK  |
				 DMA_DCR_SSIZE(1) |		// Set source size to 8 bits = 1 byte
				 DMA_DCR_SINC_MASK|		// Set increments to source address
				 DMA_DCR_SMOD(15)  |     // Destination address modulo of 2K Bytes
				 DMA_DCR_DSIZE(1)|		// Set destination size of 8 bits = 1 byte
				 DMA_DCR_AA_MASK);		// Enable auto alignment 
	
	DMAMUX0_CHCFG1 |= DMAMUX_CHCFG_SOURCE(3);
	
	// Enable interrupt
	enable_irq(INT_DMA0 - 16);
	enable_irq(INT_DMA1 - 16);
}

//******************************************************************
// send a command to the LCD
//******************************************************************
void lcd_cmd(unsigned char c){
  
	LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

	if (LCD_MODE == FOURBIT_MODE)
	{
		LCD_DATA_WRITE &= ~OUTPUT_DATA;// clear bits before new write
				LCD_DATA_WRITE |= ((c >> 4) & 0x0F) << LCD_DATA_OFFSET;
		lcd_strobe();
				LCD_DATA_WRITE &= ~OUTPUT_DATA;
			LCD_DATA_WRITE |= (c & (0x0F)) << LCD_DATA_OFFSET;
		lcd_strobe();
	}
	else
	{
		LCD_DATA_WRITE = c;
		lcd_strobe();
	}
}
//******************************************************************
// send data to the LCD
//******************************************************************
void lcd_data(unsigned char c){
        
	LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

	LCD_DATA_WRITE &= ~OUTPUT_DATA;       
	LCD_RS(1);
	if (LCD_MODE == FOURBIT_MODE)
	{
			LCD_DATA_WRITE &= ~OUTPUT_DATA;
				LCD_DATA_WRITE |= ((c >> 4) & 0x0F) << LCD_DATA_OFFSET;  
		lcd_strobe();		
				LCD_DATA_WRITE &= ~OUTPUT_DATA;
		LCD_DATA_WRITE |= (c & 0x0F) << LCD_DATA_OFFSET; 
		lcd_strobe();
	}
	else
	{
		LCD_DATA_WRITE = c;
		lcd_strobe();
	}
		  
	LCD_RS(0); 
}
//******************************************************************
// write a string of chars to the LCD
//******************************************************************
void lcd_puts(const char * s){
  
	while(*s)
		lcd_data(*s++);
}

//******************************************************************
// initialize the LCD
//******************************************************************
void lcd_init(){
  
	char init_value;

	if (LCD_MODE == FOURBIT_MODE) init_value = 0x3 << LCD_DATA_OFFSET;
		else init_value = 0x3F;
	
	LCD_RS_DDR(OUTPUT_PIN);
	LCD_EN_DDR(OUTPUT_PIN);
	LCD_RW_DDR(OUTPUT_PIN);
	LCD_DATA_DDR |= OUTPUT_DATA;
	LCD_RS(0);
	LCD_EN(0);
	LCD_RW(0);
	LCD_RW_PCR;
	LCD_RS_PCR;
	LCD_EN_PCR;
		
	DelayMs(15*48);
	LCD_DATA_WRITE &= ~OUTPUT_DATA;
	LCD_DATA_WRITE |= init_value;
	lcd_strobe();
	DelayMs(5*48);
	LCD_DATA_WRITE &= ~OUTPUT_DATA;
	LCD_DATA_WRITE |= init_value;
	lcd_strobe();
	DelayUs(200*48);
	LCD_DATA_WRITE &= ~OUTPUT_DATA;
	LCD_DATA_WRITE |= init_value;
	lcd_strobe();
	
	if (LCD_MODE == FOURBIT_MODE){
		LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h
		LCD_DATA_WRITE &= ~OUTPUT_DATA;
		LCD_DATA_WRITE |= 0x2 << LCD_DATA_OFFSET; // Set 4-bit mode
		lcd_strobe();
		lcd_cmd(0x28); // Function Set
	}
		else lcd_cmd(0x3C); // 8bit,two lines,5x10 dots 
	
	lcd_cmd(0xF); //Display On, Cursor On, Cursor Blink
	lcd_cmd(0x1); //Display Clear
	lcd_cmd(0x6); //Entry Mode
	lcd_cmd(0x80); //Initialize DDRAM address to zero
}
//******************************************************************
// Delay usec functions
//******************************************************************
void DelayUs(unsigned int cnt){
  
	unsigned char i;
        for(i=cnt ; i>0 ; i--) // tha command asm("nop") takes raphly 1usec
        	asm("nop"); 
	
}
//******************************************************************
// Delay msec functions
//******************************************************************
void DelayMs(unsigned int cnt){
  
	unsigned char i;
        for(i=cnt ; i>0 ; i--) // tha command asm("nop") takes raphly 1usec
        	DelayUs(1000); 
	
}
//******************************************************************
// lcd strobe functions
//******************************************************************
void lcd_strobe(){
  LCD_EN(1);
  asm("nop");
  asm("nop");
  LCD_EN(0);
}

//******************************************************************
// Init UART Configuration
//******************************************************************
void InitUARTConf(char b, char p, char s){
	UART0_C2 &= 0xF3;			   // stop bit only be changed when the transmitter(bit3) and receiver(bit2) are both disabled
	int baud = 9600;

	switch (b){    //Check baud rate
		case '9': baud = 9600; break;
		case '2': baud = 2400; break;
		case '1': baud = 19200; break;
		case '3': baud = 38400; break;
	}

	InitUARTs(baud);

	switch (p){   //Check parity bit
		case 'N': UART0_C1 &= 0xFD; break;                         // Parity = none  UART0_C1.PE = 0
		case 'E': UART0_C1 |= 0x02; UART0_C1 &= 0xFE; break;       // Parity = even  UART0_C1.PE = 1 + UART0_C1.PT = 0
		case 'O': UART0_C1 |= 0x02; UART0_C1 |= 0x01; break;	   // Parity = odd   UART0_C1.PE = 1 + UART0_C1.PT = 1
	}
	
	switch (s){	//Check stop bits									
	   case '1': UART0_BDH &= 0xDF; break;							      // Stop bit = 1	UART0_BDH.SBNS = 0
	   case '2': UART0_BDH |= 0x20; break;								  // Stop bit = 2   UART0_BDH.SBNS = 1
	}
	
	UART0_C2 = UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK | UART_C2_RIE_MASK; // Enable Transmitter, Receiver, Receive interrupt	
}



