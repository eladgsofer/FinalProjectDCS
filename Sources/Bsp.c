#include "TFC.h"
#include "mcg.h"

#define MUDULO_REGISTER  0x2EE0

char ready;

// set I/O for switches and LEDs
void InitGPIO()
{
	//enable Clocks to all ports - page 206, enable clock to Ports
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
	
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
void InitTPM(char x){  // x={0,1,2}
	switch(x){
	case 0:
		TPM0_SC = 0; // to ensure that the counter is not running
		TPM0_SC |= TPM_SC_PS(3)+TPM_SC_TOIE_MASK; //Prescaler =128, up-mode, counter-disable
		TPM0_MOD = MUDULO_REGISTER; // PWM frequency of 250Hz = 24MHz/(8x12,000)
		TPM0_C1SC |= TPM_CnSC_MSB_MASK + TPM_CnSC_ELSB_MASK + TPM_CnSC_CHIE_MASK;
		TPM0_C1V = 0xFFFF;
		TPM0_CONF = 0; 
		break;
	case 1:
		
		break;
	case 2: 
		TPM2_SC = 0; // to ensure that the counter is not running
		TPM2_SC |= TPM_SC_PS(3)+TPM_SC_TOIE_MASK; //Prescaler =128, up-mode, counter-disable
		TPM2_MOD = MUDULO_REGISTER; // PWM frequency of 250Hz = 24MHz/(8x12,000)
		TPM2_C0SC |= TPM_CnSC_MSB_MASK + TPM_CnSC_ELSB_MASK + TPM_CnSC_CHIE_MASK;
		TPM2_C0V = 0xFFFF; 
		TPM2_C1SC |= TPM_CnSC_MSB_MASK + TPM_CnSC_ELSB_MASK + TPM_CnSC_CHIE_MASK;
		TPM2_C1V = 0xFFFF;
		TPM2_CONF = 0;
		break;
	}
}
//-----------------------------------------------------------------
// TPMx - Clock Setup
//-----------------------------------------------------------------
void ClockSetup(){
	    
	    pll_init(8000000, LOW_POWER, CRYSTAL,4,24,MCGOUT); //Core Clock is now at 48MHz using the 8MHZ Crystal
		
	    //Clock Setup for the TPM requires a couple steps.
	    //1st,  set the clock mux
	    //See Page 124 of f the KL25 Sub-Family Reference Manual
	    SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;// We Want MCGPLLCLK/2=24MHz (See Page 196 of the KL25 Sub-Family Reference Manual
	    SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);
	    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); //We want the MCGPLLCLK/2 (See Page 196 of the KL25 Sub-Family Reference Manual
		//Enable the Clock to the TPM0 and PIT Modules
		//See Page 207 of f the KL25 Sub-Family Reference Manual
		SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK + SIM_SCGC6_TPM2_MASK;
	    // TPM_clock = 24MHz , PIT_clock = 48MHz
	    
}
//-----------------------------------------------------------------
// PIT - Initialisation
//-----------------------------------------------------------------
void InitPIT(){
	// Enable PIT clock
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
	
	// Turn on PIT
	PIT_MCR = 0;
	// Stop the pit when in debug mode
	//PIT_MCR |= PIT_MCR_FRZ_MASK; 
	
	
	// Configure PIT to produce an interrupt every 1s
	PIT_LDVAL0 = 0x1312CFF;	// 1/20Mhz = 50ns   (1s/50ns)-1= 19,999,999 cycles or 0x1312CFF
	PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK; // Enable interrupt and enable timer
	
	//Enable interrupt registers ISER and ICPR
	//enable_irq(INT_PIT - 16);
	
	//set_irq_priority(INT_PIT-16,0);  // Interrupt priority = 0 = max
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
