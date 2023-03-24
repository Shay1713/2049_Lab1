#include <stdio.h>
#include <stdlib.h>
int main()
{
  // defining intial variables
  char LED1; 
  char LED2;
  char LED3;
  char LED4;
  int randNum;
  int buzzer;
  int on = 1;
  int off = 0;
  int round = 0; // how long the game 
  int arrayIndex; // the position in each array
  int sequenceMax = 40;
  int patternArray[] = {};
  int userArray[] = {};

  
  
  // telling which LED to light up based on random number during pattern step
  int lightingButtons(randNum) { // will light and sound the LED
    for (arrayIndex = 0; arrayIndex<round+1; arrayIndex++){
      if (randNum == 1){
        LED1 = on;
        LED2 = LED3 = LED4 = off;
        buzzer = on; buzzer = off;// beep buzzer once
        // display 1 on the screen
      } else if (randNum == 2){
        LED2 = on;
        LED1 = LED3 = LED4 = off;
        buzzer = on; buzzer = off;// beep buzzer once
        // display 2 on the screen
      } else if (randNum == 3){
        LED3 = on;
        LED2 = LED1 = LED4 = off;
        buzzer = on; buzzer = off;// beep buzzer once
        // display 3 on the screen
      } else if (randNum == 4){
        LED4 = on;
        LED2 = LED3 = LED1 = off;
        buzzer = on; buzzer = off;// beep buzzer once
        // display 4 on the screen
      }
    }
  }
  
    
  // random defining LED characters to their decimal values
  for (int i = 0; i<sequenceMax; i++){
    randNum = (rand() % 4) + 1 ;
    printf("%d \n", randNum);
    //patternArray[i] = randNum;
    lightingButtons(randNum);
    
  } 
  
  
    // start up screen, while game is playing, master function
  int playingTheGame() {
    // display 'SIMON hit * to Begin' on the screen
    // clear userArray
    round = 1; // reset round back to 1
    //if (/* if the * key is pressed*/) {
      // clear SIMON phrase
      // display round #
        while(1) {
          // 
          // 
        }
    //} 
  }
  
  
       // if else to see if pattern and user arrays are the same
  int checkingOrder() { // function called checkingOrder
    for(arrayIndex = 0; arrayIndex<round+1; arrayIndex++){
      if (patternArray[arrayIndex] == userArray[arrayIndex]){ // if arrays equal
        userArray[arrayIndex] = 0;
        round++;
        // prompt playing another round
      } else { // if arrays not equal
        buzzer = on; // sound buzzer
        // display 'Game Over Hit '0' to Restart' on screen
        buzzer = off; 
        playingTheGame(); // call playingTheGame function
      }
    }
  }
  
  
}