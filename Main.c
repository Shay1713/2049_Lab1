/************** ECE2049 DEMO CODE ******************/
/**************  13 March 2019   ******************/
/***************************************************/

#include <msp430.h>
#include <stdlib.h>

/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are. It is often useful to organize
 * your code by putting like functions together in files.
 * You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"

// Function Prototypes
void swDelay2(char numLoops);
void sendSimon(int sequence, int length);
int loadSequence(int sequence, int count);
void printNum(char input);
void printNum(char input);
void countDown(void);
//unsigned char dispSz = 0;

// Declare globals here
enum GAME_STATE {WELCOME, STARTING, SEQUENCE, INPUT};

// Main
void main(void)

{
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
                                     // You can then configure it properly, if desired
    unsigned char currKey=0;

    // Define some local variables
    unsigned int length = 32;
    int sequence[length];
//    unsigned int playerInput[length];
    unsigned int currentLength = 4;
    unsigned int currentIndex = 0;
    enum GAME_STATE state = WELCOME;

//    sequence = loadSequence(sequence, length);
    int i = 0;
    for (i = 0; i < length; i++) {
            int num = (rand() % (4)) + 1;
            sequence[i] = num;
     }



    // Useful code starts here
    initLeds();
    configDisplay();
    configKeypad();

    Graphics_clearDisplay(&g_sContext); // Clear the display
    Graphics_drawStringCentered(&g_sContext, "SIMON", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT); // instructing player
    Graphics_drawStringCentered(&g_sContext, "Press '*'", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT); // instructing player
    Graphics_flushBuffer(&g_sContext);

    while (1)    // Forever loop
    {
        // Check if any keys have been pressed on the 3x4 keypad
        currKey = getKey();

        switch (state) {

            case WELCOME:
                Graphics_drawStringCentered(&g_sContext, "SIMON", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
                if (currKey == '*') {
                    state = STARTING;
                }
            break;

            case STARTING:
                countDown();
                state = SEQUENCE;

            break;

            case SEQUENCE:
//                sendSimon(sequence, currentLength);
                for (i = 0; i < currentLength; i++) {
                        setLeds(sequence[i] - 0x30);
                        BuzzerOn();
                        swDelay2(2);
                        BuzzerOff();
                        setLeds(0);
                }

                state = INPUT;
                currentIndex = 0;

            break;

            case INPUT:
                printNum(currKey);

                if (currKey == '1' && sequence[currentIndex] == 1) {
                    currentIndex++;
                } else if (currKey == '2' && sequence[currentIndex] == 2) {
                    currentIndex++;
                } else if (currKey == '3' && sequence[currentIndex] == 3) {
                    currentIndex++;
                } else if (currKey == '4' && sequence[currentIndex] == 4) {
                    currentIndex++;
                } else if ((currKey >= '1') && (currKey <= '4')) {
                    state = WELCOME;
                }
                if (currentLength - currentIndex == 1) {
                    state = SEQUENCE;
                    currentLength++;
                }


            break;
        }

    }  // end while (1)
}

void countDown(void) {
    int i = 0;
    unsigned char dispThree[3];
    dispThree[0] = ' ';
    dispThree[2] = ' ';

    for (i = 3; i > 0; i--) {
        dispThree[1] = i;
        Graphics_clearDisplay(&g_sContext); // Clear
        Graphics_drawStringCentered(&g_sContext, dispThree, AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);
        swDelay2(2);
    }
}

void printNum(char input) {
    unsigned char dispThree[3];
    unsigned char dispSz = 0;
    dispThree[0] = ' ';
    dispThree[2] = ' ';

    if ((input >= '1') && (input <= '4')) {
        dispThree[1] = input;
    }
    if (input == '1') {
        Graphics_drawStringCentered(&g_sContext, dispThree, dispSz, 12, 55, OPAQUE_TEXT);
    } else if (input == '2') {
        Graphics_drawStringCentered(&g_sContext, dispThree, dispSz, 36, 55, OPAQUE_TEXT);
    } else if (input == '3') {
        Graphics_drawStringCentered(&g_sContext, dispThree, dispSz, 60, 55, OPAQUE_TEXT);
    } else if (input == '4') {
        Graphics_drawStringCentered(&g_sContext, dispThree, dispSz, 84, 55, OPAQUE_TEXT);
    }
    Graphics_flushBuffer(&g_sContext);

}

//void loadSequence(int& sequence, int count) {
//    for (int i = 0; i < count; i++) {
//        int num = (rand() % (4)) + 1;
//        sequence[i] = num;
//    }
//}

//void sendSimon(int& sequence, int length) {
//    for (int i = 0; i < length; i++) {
//        setLeds(sequence[i] - 0x30);
//        BuzzerOn();
//        swDelay(2);
//        BuzzerOff();
//        setLeds(0);
//    }
//
//}


void swDelay2(char numLoops)
{
    // This function is a software delay. It performs
    // useless loops to waste a bit of time
    //
    // Input: numLoops = number of delay loops to execute
    // Output: none
    //
    // smj, ECE2049, 25 Aug 2013

    volatile unsigned int i,j;  // volatile to prevent removal in optimization
                                // by compiler. Functionally this is useless code

    for (j=0; j<numLoops; j++)
    {
        i = 50000 ;                 // SW Delay
        while (i > 0)               // could also have used while (i)
           i--;
    }
}
