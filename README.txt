SNES_Keyboard - A library for controlling keyboard output with an Arduino Leonardo or Micro and a SNES controller.

See examples for implementation.
*****************************************************************************************
*WARNING*  You need a Leonardo or Micro board to use this library.  DO NOT USE A DUE, the DUE runs on 3.3v and will likely be damaged by the 5v interface.
*****************************************************************************************
SNES Connector layout:

	 1234 567
	——————————
	|OOOO|OOO|
	——————————

1: +5V
2: Clock
3: Latch
4: Data
5: Nothing
6: Nothing
7: Ground
*****************************************************************************************
Copyright (c) 2014 James P. McCullough. All rights reserved.
*****************************************************************************************