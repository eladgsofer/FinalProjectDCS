#ifndef TFC_hal_H_
#define TFC_hal_H_


#define SENSOR_TRIG 2
#define SENSOR_ECHO 0 
#define SERVO_TPM	1
#define DEG_DIFF 	2


void PORTD_IRQHandler(void);
//void PIT_IRQHandler(void);
void UART0_IRQHandler(void);
void DMA0_IRQHandler(void);
void DMA1_IRQHandler(void);
void dma_file_trans(void);

#endif /* TFC_hal_H_ */
