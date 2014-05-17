/*
  NES_Keyboard.h - A library to control a keyboard with an NES controller.

  *WARNING* This code requires a Leonardo or Micro (NOT DUE!!!)
  (The Due runs on 3.3v and would likely break if you try to run this code)

  Copyright (c) 2014 James P. McCullough. All rights reserved.
*/
#include "SNES_Keyboard.h"
#include <Arduino.h>

byte count[] = {0,0,0,0,0,0,0,0,0,0,0,0}; //Stores 1 or 0 indicating whether a key is pressed                         
char keys[] = "abcdefghijkl"; //String of keyboard characters to be pressed

//Default contsructor
SNES_Keyboard::SNES_Keyboard(void) {
  pulse = 5;
  latch = 7;
  data = 9;

  pinMode(latch, OUTPUT);
  pinMode(pulse, OUTPUT);
  pinMode(data, INPUT);
  digitalWrite(latch, LOW); 
  digitalWrite(pulse, LOW);
}

//Takes pins as arguments
SNES_Keyboard::SNES_Keyboard(byte l, byte p, byte d) {
  pulse = p;
  latch = l;
  data = d;

  pinMode(latch, OUTPUT);
  pinMode(pulse, OUTPUT);
  pinMode(data, INPUT);
  digitalWrite(latch, LOW); 
  digitalWrite(pulse, LOW);
}

//Toggle pin
void SNES_Keyboard::toggle(void) {
  digitalWrite(pulse, HIGH);
  delayMicroseconds(5);
    
  digitalWrite(pulse, LOW);
  delayMicroseconds(5);
}

//Tells controller to latch data
void SNES_Keyboard::latchData(void) {
  digitalWrite(latch, HIGH);
  delayMicroseconds(12);

  digitalWrite(latch, LOW);
  delayMicroseconds(6);
}

//Stores data in data_store
void SNES_Keyboard::storeData(void) {
  data_store = 0;
  for (int i = 0; i < 12; i++) {
    data_store |= (digitalRead(data) << i);
    toggle();
  }
}

//Iterates over data_store and presses/releases keys
void SNES_Keyboard::readData(void) {
  for (int i = 0; i < 12; i++) {
    //Since the SNES sends out 16 bits of data when reading 
    //store_data we toggle 4 more times to clear the latched data
    if (i < 4) {
      toggle();
    }
    tempbit = bitRead(data_store, i);
    if (tempbit == 0 && count[i] == 0) { 
      count[i] = 1;
      Keyboard.press(keys[i]);
    }
    else if (tempbit == 1 && count[i] == 1) {
      count[i] = 0;
      Keyboard.release(keys[i]);
    }
  }
  delay(16);
}

//Change which keys are pressed
void SNES_Keyboard::setKeys(char new_keys[]) {
  for (int i = 0; i < 12; i++) {
    keys[i] = new_keys[i];
  }
}
