#include <stdio.h>
#include <stdlib.h>
int main()
{
  // defining intial variables
  char D1; 
  char D2;
  char D3;
  char D4;
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
        D1 = on;
        D2 = D3 = D4 = off;
        buzzer = on; buzzer = off;// beep buzzer once
        // display 1 on the screen
      } else if (randNum == 2){
        D2 = on;
        D1 = D3 = D4 = off;
        buzzer = on; buzzer = off;// beep buzzer once
        // display 2 on the screen
      } else if (randNum == 3){
        D3 = on;
        D2 = D1 = D4 = off;
        buzzer = on; buzzer = off;// beep buzzer once
        // display 3 on the screen
      } else if (randNum == 4){
        D4 = on;
        D2 = D3 = D1 = off;
        buzzer = on; buzzer = off;// beep buzzer once
        // display 4 on the screen
      }
    }
  }
  
    
  // random defining LED characters to their decimal values
  int randomLEDSeq () {
      for (int i = 0; i<sequenceMax; i++){
          randNum = (rand() % 4) + 1 ;
          printf("%d \n", randNum);
          //patternArray[i] = randNum;
          lightingButtons(randNum);
      }
  } 
  
  // collecting user data
  collectingPress () {
     //
  }



       // if else to see if pattern and user arrays are the same
  int checkingOrder() { // function called checkingOrder
    for(arrayIndex = 0; arrayIndex<round+1; arrayIndex++){
      if (patternArray[arrayIndex] == userArray[arrayIndex]){ // if arrays equal
        // for loop to set userArray[arrayIndex] = 0;
        // increment capacity size of pattern array pattern shown 
        round++;
        // play another round
      } else { // if arrays not equal
        buzzer = on; // sound buzzer
        // display 'Game Over Hit '0' to Restart' on screen
        round = 1;
        buzzer = off; 
        if (/* 0 button is hit */) {
           // go to default screen with Simon * to begin
        }
      }
    }
  }
  
      // start up screen, while game is playing, master function
  int playingTheGame() {
    // display 'SIMON hit * to Begin' on the screen
    //if (/* if the * key is pressed*/) {
      // clear SIMON phrase
      // display round # top of screen
      // count down 3 2 1 middle screen then clear 
        while(1) {
          randomLEDSeq(); // display pattern to user 
          collectingPress(); // collect user data 
          checkingOrder(); // call equals or not
        }
    } 
  }



}
