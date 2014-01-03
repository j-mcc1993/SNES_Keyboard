#include <SNES_Keyboard.h>
//Clock, Latch, Data
SNES_Keyboard snes(5,6,7);

void setup() {
  //B-Y-Sel-Strt-Up-Down-Left-Right-A-X-L-R
  snes.setKeys("abcdefghijkl");
}

void loop() {
  snes.latchData();
  snes.storeData();
  snes.readData();
}
