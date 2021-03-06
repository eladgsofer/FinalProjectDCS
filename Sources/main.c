/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


//#include "derivative.h" /* include peripheral declarations */
# include "TFC.h"

int main(void){

	InitApp();
	
	while(1){

		// FSM Mode - IDLE_STATE_0, Radar_Detector_1, Telemeter_2, Script_Mode_3, Script_Receive_4

		if(dataready)
		{
			state_decode();
			dataready = 0;
		}

		switch (state)
		{
			case Radar_Detector_1:
				
				rad_detect();
				
				break;
				
			case Telemeter_2:
				
				telemeter();
				
				break;
				
			case Script_Mode_3:
				
				script_mode();
				
				break;
				
			case Script_Receive_4:
				
				script_receive_flow();
				
				break;
			
			case UART_Configuration_5:
				
				set_uart_configurations();
				
				break;
				
			case IDLE_STATE_0:
				
				wait();
				
				break;
				
			default:
				break;
		}
	} // End of while(1)
	return 0;
}
