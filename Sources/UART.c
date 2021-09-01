#include "TFC.h"
#define SDA_SERIAL_BAUD 9600
#define CORE_CLOCK 48000000
/********************************************************************/
/*
 * Wait for a character to be received on the specified uart
 *
 * Parameters:
 *  channel      UART channel to read from
 *
 * Return Values:
 *  the received character
 */
char uart_getchar (UART_MemMapPtr channel)
{
      /* Wait until character has been received */
      while (!(UART_S1_REG(channel) & UART_S1_RDRF_MASK));
    
      /* Return the 8-bit data from the receiver */
      return UART_D_REG(channel);
}
/********************************************************************/
/*
 * Wait for space in the uart Tx FIFO and then send a character
 *
 * Parameters:
 *  channel      UART channel to send to
 *  ch			 character to send
 */ 
void uart_putchar (UART_MemMapPtr channel, char ch)
{
      /* Wait until space is available in the FIFO */
      while(!(UART_S1_REG(channel) & UART_S1_TDRE_MASK));
    
      /* Send the character */
      UART_D_REG(channel) = (uint8)ch;
    
 }
/********************************************************************/
/*
 * Check to see if a character has been received
 *
 * Parameters:
 *  channel      UART channel to check for a character
 *
 * Return values:
 *  0       No character received
 *  1       Character has been received
 */
int uart_getchar_present (UART_MemMapPtr channel)
{
    return (UART_S1_REG(channel) & UART_S1_RDRF_MASK);
}
/********************************************************************/
/*
 * Wait for space in the uart Tx FIFO and then send a string
 *
 * Parameters:
 *  channel      UART channel to send to
 *  str			 string to send
 */ 
void UARTprintf(UART_MemMapPtr channel,char* str){
	volatile unsigned char i;
	
	for (i=0 ; str[i] ; i++){
	
	      while(!(UART_S1_REG(channel) & UART_S1_TDRE_MASK)); /* Wait until space is available in the FIFO */
	    
	      UART_D_REG(channel) = str[i]; /* Send the character */
	}
}

