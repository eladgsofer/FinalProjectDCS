#include <stdint.h>

#ifndef BSP_H_
#define BSP_H_


#define TFC_HBRIDGE_EN_LOC			(uint32_t)(1<<21)
#define TFC_HBRIDGE_FAULT_LOC     	(uint32_t)(1<<20)

#define TFC_HBRIDGE_ENABLE			GPIOE_PSOR = TFC_HBRIDGE_EN_LOC	
#define TFC_HBRIDGE_DISABLE			GPIOE_PCOR = TFC_HBRIDGE_EN_LOC	

#define TFC_DIP_SWITCH0_LOC			((uint32_t)(1<<2))
#define TFC_DIP_SWITCH1_LOC			((uint32_t)(1<<3))
#define TFC_DIP_SWITCH2_LOC			((uint32_t)(1<<4))
#define TFC_DIP_SWITCH3_LOC			((uint32_t)(1<<5))

#define TFC_PUSH_BUTT0N0_LOC		((uint32_t)(1<<7))
#define TFC_PUSH_BUTT0N1_LOC		((uint32_t)(1<<6))	

#define TFC_BAT_LED0_LOC			((uint32_t)(1<<8))
#define TFC_BAT_LED1_LOC			((uint32_t)(1<<9))
#define TFC_BAT_LED2_LOC			((uint32_t)(1<<10))
#define TFC_BAT_LED3_LOC			((uint32_t)(1<<11))
//-------------  RGB LEDs ---------------------------------------------
#define RED_LED_LOC	         		((uint32_t)(1<<18))
#define GREEN_LED_LOC	         	((uint32_t)(1<<19))
#define BLUE_LED_LOC	         	((uint32_t)(1<<1))
#define PORT_LOC(x)        	        ((uint32_t)(1<<x))

#define RED_LED_OFF          		GPIOB_PSOR |= RED_LED_LOC
#define GREEN_LED_OFF	         	GPIOB_PSOR |= GREEN_LED_LOC
#define BLUE_LED_OFF	            GPIOD_PSOR |= BLUE_LED_LOC
#define RGB_LED_OFF	                RED_LED_OFF,GREEN_LED_OFF,BLUE_LED_OFF

#define RED_LED_TOGGLE          	GPIOB_PTOR |= RED_LED_LOC
#define GREEN_LED_TOGGLE	        GPIOB_PTOR |= GREEN_LED_LOC
#define BLUE_LED_TOGGLE	            GPIOD_PTOR |= BLUE_LED_LOC
#define RGB_LED_TOGGLE	            RED_LED_TOGGLE,GREEN_LED_TOGGLE,BLUE_LED_TOGGLE

#define RED_LED_ON          		GPIOB_PCOR |= RED_LED_LOC
#define GREEN_LED_ON	         	GPIOB_PCOR |= GREEN_LED_LOC
#define BLUE_LED_ON	                GPIOD_PCOR |= BLUE_LED_LOC
#define RGB_LED_ON	                RED_LED_ON,GREEN_LED_ON,BLUE_LED_ON

#define SW7_POS 0x80  //PTD7
#define SW6_POS 0x40  //PTD6
//---------------------------------------------------------------------
#define TFC_BAT_LED0_ON				GPIOB_PSOR = TFC_BAT_LED0_LOC
#define TFC_BAT_LED1_ON				GPIOB_PSOR = TFC_BAT_LED1_LOC
#define TFC_BAT_LED2_ON				GPIOB_PSOR = TFC_BAT_LED2_LOC
#define TFC_BAT_LED3_ON				GPIOB_PSOR = TFC_BAT_LED3_LOC

#define TFC_BAT_LED0_OFF			GPIOB_PCOR = TFC_BAT_LED0_LOC
#define TFC_BAT_LED1_OFF			GPIOB_PCOR = TFC_BAT_LED1_LOC
#define TFC_BAT_LED2_OFF			GPIOB_PCOR = TFC_BAT_LED2_LOC
#define TFC_BAT_LED3_OFF			GPIOB_PCOR = TFC_BAT_LED3_LOC

#define TFC_BAT_LED0_TOGGLE			GPIOB_PTOR = TFC_BAT_LED0_LOC
#define TFC_BAT_LED1_TOGGLE			GPIOB_PTOR = TFC_BAT_LED1_LOC
#define TFC_BAT_LED2_TOGGLE			GPIOB_PTOR = TFC_BAT_LED2_LOC
#define TFC_BAT_LED3_TOGGLE			GPIOB_PTOR = TFC_BAT_LED3_LOC

#define TFC_PUSH_BUTTON_0_PRESSED	((GPIOC_PDIR&TFC_PUSH_BUTT0N0_LOC)>0) 	//PTD7
#define TFC_PUSH_BUTTON_1_PRESSED	((GPIOC_PDIR&TFC_PUSH_BUTT0N1_LOC)>0)	//PTD6
//------------------ DMA ------------------------------------------------
#define  ADC_READS 1000

//------------ LCD Configurations ---------------------------------------
// #define CHECKBUSY	1  // using this define, only if we want to read from LCD

#ifdef CHECKBUSY
	#define	LCD_WAIT lcd_check_busy()
#else
	#define LCD_WAIT DelayMs(5)
#endif

/*----------------------------------------------------------
  CONFIG: change values according to your port pin selection
------------------------------------------------------------*/
#define LCD_EN(a)	(!a ? (GPIOE_PDOR &=~PORT_LOC(5)) : (GPIOE_PDOR|=PORT_LOC(5))) // PE5 is lcd enable pin
#define LCD_EN_DDR(a)	(!a ? (GPIOE_PDDR=~PORT_LOC(5)) : (GPIOE_PDDR|=PORT_LOC(5))) // PE5 pin direction 
#define LCD_EN_PCR  (PORTE_PCR5 = PORT_PCR_MUX(1)) //PE5 pin IO

#define LCD_RS(a)	(!a ? (GPIOE_PDOR &=~PORT_LOC(3)) : (GPIOE_PDOR|=PORT_LOC(3))) // PE3 is lcd RS pin
#define LCD_RS_DDR(a)	(!a ? (GPIOE_PDDR &=~PORT_LOC(3)) : (GPIOE_PDDR |= PORT_LOC(3))) // PE3 pin direction  
#define LCD_RS_PCR  (PORTE_PCR3 = PORT_PCR_MUX(1)) //PE3 pin IO

#define LCD_RW(a)	(!a ? (GPIOE_PDOR &=~PORT_LOC(4)) : (GPIOE_PDOR|=PORT_LOC(4))) // PE4 is lcd RW pin
#define LCD_RW_DDR(a)	(!a ? (GPIOE_PDDR=~PORT_LOC(4)) : (GPIOE_PDDR|=PORT_LOC(4))) // PE4  pin direction 
#define LCD_RW_PCR  (PORTE_PCR4 = PORT_PCR_MUX(1)) //PE4 pin IO

  
 

#define LCD_DATA_OFFSET 0x00 //data pin selection offset for 4 bit mode, variable range is 0-4, default 0 - Px.0-3, no offset

#define LCD_DATA_WRITE	GPIOB_PDOR
#define LCD_DATA_DDR	GPIOE_PDDR
/*---------------------------------------------------------
  END CONFIG
-----------------------------------------------------------*/
#define FOURBIT_MODE	0x0
#define EIGHTBIT_MODE	0x1
#define LCD_MODE        FOURBIT_MODE
   
#define OUTPUT_PIN      1	
#define INPUT_PIN       0	
#define OUTPUT_DATA     (LCD_MODE ? 0xFF : (0x0F << LCD_DATA_OFFSET))
#define INPUT_DATA      0x0	

#define LCD_STROBE_READ(value)	LCD_EN(1), \
				asm("nop"), asm("nop"), \
				value=LCD_DATA_READ, \
				LCD_EN(0) 

#define	lcd_cursor(x)		lcd_cmd(((x)&0x7F)|0x80)
#define lcd_clear()		lcd_cmd(0x01)
#define lcd_putchar(x)		lcd_data(x)
#define lcd_goto(x)		lcd_cmd(0x80+(x))
#define lcd_cursor_right()	lcd_cmd(0x14)
#define lcd_cursor_left()	lcd_cmd(0x10)
#define lcd_display_shift()	lcd_cmd(0x1C)
#define lcd_home()		lcd_cmd(0x02)
#define cursor_off()              lcd_cmd(0x0C)
#define cursor_on()               lcd_cmd(0x0F) 
#define lcd_function_set()        lcd_cmd(0x3C) // 8bit,two lines,5x10 dots 
#define lcd_new_line()            lcd_cmd(0xC0)

void InitGPIO();
void InitTPM(char x);
uint8_t TFC_GetDIP_Switch();
void ClockSetup();
void InitPIT();

extern void lcd_cmd(unsigned char);
extern void lcd_data(unsigned char);
extern void lcd_puts(const char * s);
extern void lcd_init();
extern void lcd_strobe();
extern void DelayMs(unsigned int);
extern void DelayUs(unsigned int);

extern uint16_t  value[ADC_READS];
char ready;

void dma_init(void);

#endif /* BSP_H_ */
