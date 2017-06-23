/*
 * Filename: SNES_Keyboard.cpp
 * Author: James McCullough
 * Description: This program encapsulates an interface for controlling SNES
 *    controllers with arduino.
 *
 * Copyright (c) 2014 James P. McCullough. All rights reserved.
 */

#include "SNES_Keyboard.h"


/* Stores true or falseindicating whether a key is pressed */
boolean isPressed[] = {false, false, false, false, false, false, false, false,
		       false, false, false, false};

char keys[] = "abcdefghijkl";	/* keys to be pressed */


/*
 * SNES_Keyboard::SNES_Keyboard(void);
 *
 * This class handles the serial communication between the arduino and the
 * SNES controller.  This code sets the default pins and starts the interaction
 * with the keyboard.
 */
SNES_Keyboard::SNES_Keyboard() {
  clck = CLCK;
  latch = LATCH;
  data = DATA;

  pinMode(latch, OUTPUT);
  pinMode(clck, OUTPUT);
  pinMode(data, INPUT);

  /* Set latch and clock to known states */
  digitalWrite(latch, LOW); 
  digitalWrite(clck, HIGH);

  Keyboard.begin();
}


/*
 * SNES_Keyboard::SNES_Keyboard(byte l, byte p, byte d);
 *
 * An overloaded constructor to allow users to choose which pins to use.
 */
SNES_Keyboard::SNES_Keyboard(byte l, byte c, byte d) {
  latch = l;
  clck = c;
  data = d;

  pinMode(latch, OUTPUT);
  pinMode(clck, OUTPUT);
  pinMode(data, INPUT);

  /* Set latch and clock to known states */
  digitalWrite(latch, LOW); 
  digitalWrite(clck, HIGH);

  Keyboard.begin();
}


/*
 * void SNES_Keyboard::latchData(void);
 *
 * Sends a 12uS high pulse to instruct controller to latch or store its
 * button states internally.
 *
 * No return value.
 */
void SNES_Keyboard::latchData() {
  digitalWrite(latch, HIGH);
  delayMicroseconds(LONG_DELAY);

  digitalWrite(latch, LOW);
  delayMicroseconds(SHORT_DELAY);
}

/*
 * void SNES_Keyboard::pulseClock(void);
 *
 * Sends a 12uS high pulse to the clock pin with a 50% duty cycle.
 * Each call to this function instructs the controller to respond
 * with a high or low signal on the data line indicated whether
 * the corresponding button was pressed.
 *
 * No return value.
 */
void SNES_Keyboard::pulseClock() {
  delayMicroseconds(SHORT_DELAY);
  digitalWrite(clck, LOW);
    
  delayMicroseconds(CLOCK_DELAY);
  digitalWrite(clck, HIGH);
}


/*
 * void NES_Keyboard::storeData(void);
 *
 * Stores the high and low signals from the data line while pulsing the
 * clock line to obtain button states.
 *
 * No return value.
 */
void SNES_Keyboard::storeData() {
  state = 0;
  for (int i = 0; i < NUM_OF_BUTTONS + EXTRA; i++) {  
    if (digitalRead(data) == LOW) {
      state |= (MASK << i);
    }
    pulseClock();
  }
}


/*
 * void SNES_Keyboard::readData(void);
 *
 * This function obtains the button states by using a bitmask to obtain
 * the value of each bit in the data_store.  The controller sends a low
 * pulse when the controller is low, and a high pulse when the button
 * is unpressed.  The isPressed array stores a 1 or 0 to indicate whether
 * a button is currently pressed or not, which will determine whether to
 * press or release that button.  The SNES sends 16 bits of data for the
 * 12 buttons, so the line must be pulsed an additional 4 times.
 *
 * No return value.
 */
void SNES_Keyboard::readData() {
  for (int i = 0; i < NUM_OF_BUTTONS; i++) {
    int currentbit = state & (MASK << i);

    if (currentbit && !isPressed[i]) { 
      isPressed[i] = true;
      Keyboard.press(keys[i]);
    }
    else if (!currentbit && isPressed[i]) {
      isPressed[i] = false;
      Keyboard.release(keys[i]);
    }
  }

  delay(READ_DELAY);
}


/*
 * void SNES_Keyboard::setKeys(void);
 *
 * This function initializes the keys array with a user supplied array to allow
 * for custom keyboard setups.
 *
 * No return value.
 */
void SNES_Keyboard::setKeys(char new_keys[]) {
  for (int i = 0; i < NUM_OF_BUTTONS; i++) {
    keys[i] = new_keys[i];
  }
}
