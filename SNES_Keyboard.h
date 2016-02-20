/*
  SNES_Keyboard.h - A library to control a keyboard with a SNES controller.

  *WARNING* This code requires a Leonardo or Micro (NOT DUE!!!)
  (The Due runs on 3.3v and would likely break if you try to run this code)

  Copyright (c) 2014 James P. McCullough. All rights reserved.
*/
#ifndef SNES_Keyboard_h
#define SNES_Keyboard_h

#include <Arduino.h>
#include <Keyboard.h>

#define NUM_OF_BUTTONS 12

#define LATCH_PULSE 12
#define LATCH_DELAY 6
#define PULSE_DELAY 6
#define READ_DELAY 16
#define EXTRA 4

#define PULSE 5
#define LATCH 7
#define DATA 9

class SNES_Keyboard {
	public:
		SNES_Keyboard(void);
		SNES_Keyboard(byte l, byte p, byte d);
		void latchData(void);
		void storeData(void);
		void readData(void);
		void setKeys(char new_keys[]);
	private:
		void pulseClock(void);
		int data_store;
		byte latch, pulse, data, currentbit, mask;
};

#endif
