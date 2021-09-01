#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int commandsParser() {
    char string[50] = "0102\n041E\n0201\n0302\n05\n0623\n0101\n07143C\n08";
    char leftDegree[3], rightDegree[3],  fullOperand[10];
    int operandVal =0, leftAngle, rightAngle, opcode;

    // Extract the first token
    char * token = strtok(string, "\n");
    // loop through the string to extract all other tokens
    while( token != NULL ) {
        printf( "%s\n", token ); //printing each token
        // Extract opcode and operand
        sscanf(token, "%2d%s", &opcode, fullOperand);
        token = strtok(NULL, "\n");
        // convert Hex string to int
        operandVal = (int)strtol(fullOperand, NULL, 16);

        switch(opcode)
        {

            case 1  :
            	blink_rgb(operandVal);
                break;
            case 2  :
            	lcd_count_down(operandVal);
                break;
            case 3:
            	lcd_count_up(operandVal);
                break;
            case 4:
            	set_delay(operandVal);
                break;
            case 5:
            	clear_all_leds();
                break;
            case 6:
            	servo_deg(operandVal);
                break;
            case 7:
                // Extract scanning range
                sscanf(fullOperand, "%2c%2c", leftDegree, rightDegree);
                leftAngle = (int)strtol(leftDegree, NULL, 16);
                rightAngle = (int)strtol(rightDegree, NULL, 16);

                servo_scan(leftAngle, rightAngle);
                break;
            case 8:
                sleep();
                break;
                /* you can have any number of case statements */
            default : /* Optional */
                break;
        }
    }
    return 0;
}
