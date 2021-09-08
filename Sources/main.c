/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


//#include "derivative.h" /* include peripheral declarations */
# include "TFC.h"

// Declarations of externs
volatile int distance_ready = FALSE;
volatile int signal_taken = FALSE;
volatile unsigned int acc_distance = 0;
volatile unsigned int out_distance = 0;
volatile unsigned int distance = 0;
volatile unsigned int rising_edge = 0;
volatile unsigned int falling_edge = 0;


int main(void){

	InitApp();
	
	while(1){

		// FSM Mode - IDLE_STATE_0, Radar_Detector_1, Telemeter_2, Script_Mode_3, Script_Receive_4

		while (!dataready);
		state_decode();
		dataready = 0;

		switch (state)
		{
			case Radar_Detector_1:
				// START scan command - PIT_MCR &= ~PIT_MCR_MDIS_MASK; //Enable the PIT module 
				//sensor's TPM start:
				/*
					TPM2_SC |= TPM_SC_CMOD(1); //Start the TPM2 counter
					TPM0_SC |= TPM_SC_CMOD(1); //Start the TPM0 counter
				 */
				break;
				
			case Telemeter_2:
				// START scan command - PIT_MCR &= ~PIT_MCR_MDIS_MASK; //Enable the PIT module 
				//sensor's TPM start:
				/*
					TPM2_SC |= TPM_SC_CMOD(1); //Start the TPM2 counter
					TPM0_SC |= TPM_SC_CMOD(1); //Start the TPM0 counter
				 */
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
				
			default:
				break;
		}
	} // End of while(1)
	return 0;
}
