/*
 * Filename: SNES_Keyboard.h
 * Author: James McCullough
 * Description: This program encapsulates an interface for controlling SNES
 * 				controllers with arduino.
 *
 * !! WARNING !!  This code requires a Leonardo or Micro.  Using a Due may
 * brick your board due its 3.3v requirement.
 *
 * Copyright (c) 2014 James P. McCullough. All rights reserved.
 */
 
#ifndef SNES_Keyboard_h
#define SNES_Keyboard_h

#include <Arduino.h>
#include <Keyboard.h>

#define NUM_OF_BUTTONS 12

#define LONG_DELAY  12        // Duration to set latch high
#define SHORT_DELAY 3         // Delay after setting latch high 
#define CLOCK_DELAY 6         // 50% of the clock duty cycle
#define READ_DELAY  16        // Delay between button state sampling
#define EXTRA       4         // Extra void data pulses

#define MASK 0x1

#define CLCK  5
#define LATCH 7
#define DATA  9

class SNES_Keyboard {
	public:

		SNES_Keyboard();

		SNES_Keyboard(byte l, byte c, byte d);

		void latchData();

		void storeData();

		void readData();

		void setKeys(char new_keys[]);

	private:

		int state;

		byte clck, latch, data;

		void pulseClock();
};

#endif
