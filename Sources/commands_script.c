#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int commandsParser() {
    char string[50] = "0102\n041E\n0201\n0302\n05\n0623\n0101\n07143C\n08";
    char leftDegree[3], rightDegree[3],  fullOperand[10];
    int operandVal =0, delay=5, leftAngle, rightAngle, opcode;

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
                //blinkRGB(operandVal, delay);
                break;
            case 2  :
                //lcdCountDown(operandVal, delay);
                break;
            case 3:
                //lcdCountUp(operandVal, delay);
                break;
            case 4:
                delay = operandVal;
                break;
            case 5:
                //RGB_LED_OFF;
                break;
            case 6:
                //servoDegree(operandVal);
                break;
            case 7:
                // Extract scanning range
                sscanf(fullOperand, "%2c%2c", leftDegree, rightDegree);
                leftAngle = (int)strtol(leftDegree, NULL, 16);
                rightAngle = (int)strtol(rightDegree, NULL, 16);

                //servoScan(leftAngle, rightAngle);
                break;
            case 8:
                //wait();
                break;
                /* you can have any number of case statements */
            default : /* Optional */
                break;
        }
    }
    return 0;
}