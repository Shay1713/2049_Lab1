/************** ECE2049 Lab1 CODE ******************/
/**************  28 March 2023   ******************/
/***************************************************/

/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are.*/
#include <msp430.h>
#include "peripherals.h"
#include <stdio.h>
#include <stdlib.h>


// Declare globals here

int randomNum; // prep for random number generator
int cChecker = 2;; // counter
int arrayIndex = 0; // position in any array
int arrayIndexP = 0; // position in pattern array
int arrayIndexU = 0; // position in user array
int sequenceMax = 1; // max game length
int patternArray[] = {}; // random led pattern
int userArray[] = {}; //saves user press button data
unsigned int time = 50000; // time integer loop
unsigned char currKey=0, dispSz = 3; // DO NOT CHANGE
unsigned char dispThree[3]; // DO NOT CHANGE



// Function Prototypes
void swDelay(char numLoops);
void incPatternDisp (); // incrementing and displaying pattern
void clearingPatternUserArrays(); // if player loses, resetting arrays
void checkIfEqual();
void endGameReached();
void time2(int numLoops2, int c);


// Main
void main(void)
{
    // Useful code starts here
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
    initLeds();
    configDisplay();
    configKeypad();
    // *** Intro Screen ***
    Graphics_clearDisplay(&g_sContext); // Clear the display
    Graphics_drawStringCentered(&g_sContext, "SIMON", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "Press *", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "to begin", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
    Graphics_flushBuffer(&g_sContext);
    dispThree[0] = ' ';
    dispThree[2] = ' ';
    
        while (1)    // Forever loop
           {
               // Check if any keys have been pressed on the 3x4 keypad
               currKey = getKey();
               if (currKey == '*'){ // counting down
                   setLeds('3' - 0x30);
                   BuzzerOn();
                   Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 10, 55, TRANSPARENT_TEXT);
                   Graphics_flushBuffer(&g_sContext);
                   swDelay(2);
                   BuzzerOff();
                   swDelay(2);
                   setLeds('2' - 0x30);
                   BuzzerOn();
                   Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 30, 55, TRANSPARENT_TEXT);
                   Graphics_flushBuffer(&g_sContext);
                   swDelay(2);
                   BuzzerOff();
                   swDelay(2);
                   setLeds('1' - 0x30);
                   BuzzerOn();
                   Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 50, 55, TRANSPARENT_TEXT);
                   Graphics_flushBuffer(&g_sContext);
                   swDelay(2);
                   BuzzerOff();
                   swDelay(2);
                   setLeds('*'-0x30);
                   BuzzerOn();
                   Graphics_drawStringCentered(&g_sContext, "GO", AUTO_STRING_LENGTH, 70, 55, TRANSPARENT_TEXT);
                   Graphics_flushBuffer(&g_sContext);
                   swDelay(2);
                   BuzzerOff();
                   setLeds(0);
                   swDelay(2);
                   // calling first round to LCD screen
                   endGameReached();
                   Graphics_clearDisplay(&g_sContext); // preparing to prompt the user
                   Graphics_flushBuffer(&g_sContext);
                   incPatternDisp(); // displaying pattern to user
                   Graphics_clearDisplay(&g_sContext); // clearing pattern numbers
                   Graphics_drawStringCentered(&g_sContext, "Repeat Pattern", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT); // instructing player
                   //Graphics_drawStringCentered(&g_sContext, "Press '#'", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT); // instructing player
                   //Graphics_drawStringCentered(&g_sContext, "When Done", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT); // instructing player
                   Graphics_flushBuffer(&g_sContext);
                   swDelay(3);
                   //arrayIndexU++;
               }
               /*if (currKey == '#'){
                  setLeds(currKey - 0x30);
               }*/
               if (currKey == '1'){
                   setLeds(currKey - 0x30);
               }
               if (currKey == '2'){
                  setLeds(currKey - 0x30);
               }
               if (currKey == '3'){
                   setLeds(currKey - 0x30);
               }
               if (currKey == '4'){
                   setLeds(currKey - 0x30);
               }
               if (currKey == '9'){
                   setLeds(currKey - 0x30);
               }
               if (currKey == '0'){
                   setLeds('8' - 0x30);
               }

               // ____________________________________________
               if (currKey) // back to the buttons
               {
                   dispThree[1] = currKey;
                   if ((currKey >= '5') && (currKey <= '8')){
                       setLeds(0);
                       printf("Button 5-8 pressed\n");
                   }
                   if (currKey == '1'){
                       Graphics_drawStringCentered(&g_sContext, dispThree, dispSz, 20, 55, OPAQUE_TEXT);
                       printf("Button 1 pressed\n");
                       userArray[arrayIndexU] = 1;
                       //printf("sequenceMax pressed 1 is: %d\n", sequenceMax);
                       printf("userArray is %d and arrayIndexU is %d\n ", userArray[arrayIndexU], arrayIndexU);
                       arrayIndexU++;
                       checkIfEqual();
                   }
                   if (currKey == '2'){
                      Graphics_drawStringCentered(&g_sContext, dispThree, dispSz, 40, 55, OPAQUE_TEXT);
                      printf("Button 2 pressed\n");
                      userArray[arrayIndexU] = 2;
                      //printf("sequenceMax pressed 2 is: %d\n", sequenceMax);
                      printf("userArray is %d and arrayIndexU is %d\n ", userArray[arrayIndexU], arrayIndexU);
                      arrayIndexU++;
                      checkIfEqual();
                   }
                   if (currKey == '3'){
                       Graphics_drawStringCentered(&g_sContext, dispThree, dispSz, 60, 55, OPAQUE_TEXT);
                       printf("Button 3 pressed\n");
                       userArray[arrayIndexU] = 3;
                       //printf("sequenceMax pressed 3 is: %d\n", sequenceMax);
                       printf("userArray is %d and arrayIndexU is %d\n ", userArray[arrayIndexU], arrayIndexU);
                       arrayIndexU++;
                       checkIfEqual();
                   }
                   if (currKey == '4'){
                       Graphics_drawStringCentered(&g_sContext, dispThree, dispSz, 80, 55, OPAQUE_TEXT);
                       printf("Button 4 pressed\n");
                       userArray[arrayIndexU] = 4;
                       //printf("sequenceMax pressed 4 is: %d\n", sequenceMax);
                       printf("userArray is %d and arrayIndexU is %d\n ", userArray[arrayIndexU], arrayIndexU);
                       arrayIndexU++;
                       checkIfEqual();
                   }
                   if (currKey == '0'){
                      clearingPatternUserArrays();
                      printf("Button 0 pressed\n");
                      //printf("sequenceMax pressed 0 is: %d\n", sequenceMax);
                      Graphics_drawStringCentered(&g_sContext, "YOU LOSE", AUTO_STRING_LENGTH, 48, 50, TRANSPARENT_TEXT); // restarting game
                      Graphics_drawStringCentered(&g_sContext, "Press '9'", AUTO_STRING_LENGTH, 48, 60, TRANSPARENT_TEXT);
                      Graphics_flushBuffer(&g_sContext);
                      swDelay(4);
                      arrayIndexP = 0; // resetting player button Array Index
                      arrayIndexU = -1;
                      sequenceMax = 1; // resetting rounds
                   }
                   if (currKey == '9'){
                      printf("Button 9 pressed\n");
                      //printf("sequenceMax pressed 9 is: %d\n", sequenceMax);
                      Graphics_drawStringCentered(&g_sContext, "Press *", AUTO_STRING_LENGTH, 48, 50, TRANSPARENT_TEXT); // restarting game
                      Graphics_drawStringCentered(&g_sContext, "to begin", AUTO_STRING_LENGTH, 48, 60, TRANSPARENT_TEXT);
                      Graphics_flushBuffer(&g_sContext);
                      swDelay(4);
                      arrayIndexP = 0; // resetting player button Array Index
                      arrayIndexU = -1;
                      sequenceMax = 1; // resetting rounds
                   }
                   /*if (currKey == '#'){
                      checkIfEqual();
                   }*/

                   // Refresh the display so it shows the new data
                   Graphics_flushBuffer(&g_sContext);
                   BuzzerOn();
                   swDelay(2);
                   BuzzerOff();
                   setLeds(0);
                   Graphics_clearDisplay(&g_sContext); // Clear the display
                   Graphics_drawStringCentered(&g_sContext, "SIMON", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                   Graphics_flushBuffer(&g_sContext);
               }
           }  // end while (1)

}
// functions start here
void swDelay(char numLoops)
{
    // This function is a software delay.

    volatile unsigned int i,j;  // volatile to prevent removal in optimization
                                // by compiler. Functionally this is useless code
    for (j=0; j<numLoops; j++)
    {
        i = 50000 ;         // SW Delay
        while (i > 0)               // could also have used while (i)
           i--;
    }
}
void time2(numLoops2, c) {
    for (arrayIndex=0; arrayIndex<numLoops2; arrayIndex++)
    {
        while (time > 0)
        {
           time--;
        }
    }
    time = time-c;
}
void incPatternDisp () //generating random pattern array
{
    for (arrayIndexP = 0; arrayIndexP < sequenceMax; arrayIndexP++){ // generating here
        randomNum = (rand() % 4) +1;
        if (randomNum == 1){
            Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 20, 55, TRANSPARENT_TEXT);
            setLeds('1' - 0x30);
            Graphics_flushBuffer(&g_sContext); // fresh
            BuzzerOn();
            time2(12, 900);
            BuzzerOff();
            setLeds(0);
            Graphics_clearDisplay(&g_sContext); // clear
            patternArray[arrayIndexP] = 1;
            printf("patternArray is %d and arrayIndexP is %d and randomNum is %d\n ", patternArray[arrayIndexP], arrayIndexP, randomNum);
        }
        if (randomNum == 2){
            Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 40, 55, TRANSPARENT_TEXT);
            setLeds('2' - 0x30);
            Graphics_flushBuffer(&g_sContext); // refresh
            BuzzerOn();
            time2(12, 900);
            BuzzerOff();
            setLeds(0);
            Graphics_clearDisplay(&g_sContext); // clear
            patternArray[arrayIndexP] = 2;
            printf("patternArray is %d and arrayIndexP is %d and randomNum is %d\n ", patternArray[arrayIndexP], arrayIndexP, randomNum);
        }
        if (randomNum == 3){
            Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 60, 55, TRANSPARENT_TEXT);
            setLeds('3' - 0x30);
            Graphics_flushBuffer(&g_sContext); // refresh
            BuzzerOn();
            time2(12, 900);
            BuzzerOff();
            setLeds(0);
            Graphics_clearDisplay(&g_sContext); // clear
            patternArray[arrayIndexP] = 3;
            printf("patternArray is %d and arrayIndexP is %d and randomNum is %d\n ", patternArray[arrayIndexP], arrayIndexP, randomNum);
        }
        if (randomNum == 4){
            Graphics_drawStringCentered(&g_sContext, "4", AUTO_STRING_LENGTH, 80, 55, TRANSPARENT_TEXT);
            setLeds('4' - 0x30);
            Graphics_flushBuffer(&g_sContext); // refresh
            BuzzerOn();
            time2(12, 900);
            BuzzerOff();
            setLeds(0);
            Graphics_clearDisplay(&g_sContext); // clear
            patternArray[arrayIndexP] = 4;
            printf("patternArray is %d and arrayIndexP is %d and randomNum is %d\n ", patternArray[arrayIndexP], arrayIndexP, randomNum);
        }
    }

}
void checkIfEqual() { // are arrays equal
    if (arrayIndexU == arrayIndexP) { // would prompt array check if both same length
        printf("START HERE: arrayIndexU %d, arrayIndexP %d\n", arrayIndexU, arrayIndexP);

        for (arrayIndexP = 0; arrayIndex < sequenceMax; arrayIndex++){
            printf("u %d\n", userArray[arrayIndex]); // clearing user array
            printf("p %d\n", patternArray[arrayIndex]); // clearing random pattern array
        }
        for (arrayIndex = 0; arrayIndex < sequenceMax; arrayIndex++){
            if (userArray[arrayIndex] == patternArray[arrayIndex]){
                printf("arrayIndex %d, userArray[arrayIndex] %d, patternArray[arrayIndex] %d\n", arrayIndex, userArray[arrayIndex], patternArray[arrayIndex]);
                printf("same %d\n", arrayIndex);
                cChecker = 1;
            } else {
                cChecker = 0;
                printf("arrayIndex %d, userArray[arrayIndex] %d, patternArray[arrayIndex] %d\n", arrayIndex, userArray[arrayIndex], patternArray[arrayIndex]);
                printf("not same %d\n", arrayIndex);
                break;
            }
        }
        if (cChecker == 1) {
            printf("successful round %d\n", sequenceMax);
            cChecker = 2;
            Graphics_drawStringCentered(&g_sContext, "SUCESSFUL", AUTO_STRING_LENGTH, 50, 35, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "ROUND", AUTO_STRING_LENGTH, 50, 45, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Press '*'", AUTO_STRING_LENGTH, 50, 65, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "To Start", AUTO_STRING_LENGTH, 50, 75, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Next Round", AUTO_STRING_LENGTH, 50, 85, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext); // refresh
            swDelay(5);
            clearingPatternUserArrays();
            sequenceMax++;
            arrayIndexP = 0;
            arrayIndexU = -1;
        } else if (cChecker == 0) {
            cChecker = 2;
            printf("U %d and P %d\n", userArray[arrayIndex], patternArray[arrayIndex]);
            printf("not same %d\n", arrayIndex);
            Graphics_drawStringCentered(&g_sContext, "GAME OVER", AUTO_STRING_LENGTH, 50, 35, TRANSPARENT_TEXT);
            Graphics_drawStringCentered(&g_sContext, "Press '0'", AUTO_STRING_LENGTH, 50, 45, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext); // refresh
            swDelay(5);
            clearingPatternUserArrays();
        }
    }
}
void clearingPatternUserArrays() { // clearing the pattern and user arrays to restart
    for (arrayIndex = 0; arrayIndex < sequenceMax; arrayIndex++){
        userArray[arrayIndex] = 0; // clearing user array
        patternArray[arrayIndex] = 0; // clearing random pattern array
    }
    printf("arrays are cleared\n");
}
void endGameReached() {
    if (sequenceMax==40){ // setting game limit max rounds
        Graphics_clearDisplay(&g_sContext); // Clear the display
        Graphics_drawStringCentered(&g_sContext, "YOU WIN", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
        Graphics_flushBuffer(&g_sContext);
        swDelay(10);
        sequenceMax=1; // resetting game rounds
   }
}
