/*
 * Filename: SNES_Keyboard.cpp
 * Author: James McCullough
 * Description: This program encapsulates an interface for controlling SNES
 *    controllers with arduino.
 * !! WARNING !!  This code requires a Leonardo or Micro.  Using a Due may
 * brick your board due its 3.3v requirement.
 *
 * Copyright (c) 2014 James P. McCullough. All rights reserved.
 */

#include "SNES_Keyboard.h"

/* Stores 1 or 0 indicating whether a key is pressed */
byte isPressed[] = {0,0,0,0,0,0,0,0,0,0,0,0};                          
char keys[] = "abcdefghijkl"; /* keys to be pressed */

/*
 * SNES_Keyboard::SNES_Keyboard(void);
 *
 * This class handles the serial communication between the arduino and the
 * SNES controller.  This code sets the default pins and starts the interaction
 * with the keyboard.
 */
SNES_Keyboard::SNES_Keyboard(void) {
  pulse = PULSE;
  latch = LATCH;
  data = DATA;

  pinMode(latch, OUTPUT);
  pinMode(pulse, OUTPUT);
  pinMode(data, INPUT);

  /* set a clean low signal */
  digitalWrite(latch, LOW); 
  digitalWrite(pulse, LOW);

  Keyboard.begin();
}

/*
 * SNES_Keyboard::SNES_Keyboard(byte l, byte p, byte d);
 *
 * An overloaded constructor to allow users to choose which pins to use.
 */
SNES_Keyboard::SNES_Keyboard(byte l, byte p, byte d) {
  pulse = p;
  latch = l;
  data = d;

  pinMode(latch, OUTPUT);
  pinMode(pulse, OUTPUT);
  pinMode(data, INPUT);

  /* set a clean low signal */
  digitalWrite(latch, LOW); 
  digitalWrite(pulse, LOW);

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
void SNES_Keyboard::latchData(void) {
  digitalWrite(latch, HIGH);
  delayMicroseconds(LATCH_PULSE);

  digitalWrite(latch, LOW);
  delayMicroseconds(LATCH_DELAY);
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
void SNES_Keyboard::pulseClock(void) {
  digitalWrite(pulse, HIGH);
  delayMicroseconds(PULSE_DELAY);
    
  digitalWrite(pulse, LOW);
  delayMicroseconds(PULSE_DELAY);
}

/*
 * void NES_Keyboard::storeData(void);
 *
 * Stores the high and low signals from the data line while pulsing the
 * clock line to obtain button states.
 *
 * No return value.
 */
void SNES_Keyboard::storeData(void) {
  data_store = 0;
  for (int i = 0; i < NUM_OF_BUTTONS; i++) {
    data_store |= (digitalRead(data) << i);
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
void SNES_Keyboard::readData(void) {
  mask = 0x01;
  for (int i = 0; i < 12; i++) {
    mask = mask << i;
    if (i < EXTRA) pulseClock();

    currentbit = data_store & mask;

    if (currentbit == 0 && isPressed[i] == 0) { 
      isPressed[i] = 1;
      Keyboard.press(keys[i]);
    }
    else if (currentbit == 1 && isPressed[i] == 1) {
      isPressed[i] = 0;
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
