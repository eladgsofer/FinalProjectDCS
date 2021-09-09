#ifndef TFC_hal_H_
#define TFC_hal_H_


#define SENSOR_TRIG 2
#define SENSOR_ECHO 0 
#define SERVO_TPM	1
#define DEG_DIFF 	5


void PORTD_IRQHandler(void);
//void PIT_IRQHandler(void);
void UART0_IRQHandler(void);
void DMA0_IRQHandler(void);
void DMA1_IRQHandler(void);
void dma_file_trans(void);
void enable_sensor(int enable);
void setServoAtDegree(void);
void blink_rgb(int x);
void lcd_count_down(int x);
void lcd_count_up(int x);
void set_delay(int d);
void clear_all_leds(void);
void servo_deg(int p);
void servo_scan(int l, int r);

void Delay_d(void);
void Delay_Ms(int ms);

#endif /* TFC_hal_H_ */
