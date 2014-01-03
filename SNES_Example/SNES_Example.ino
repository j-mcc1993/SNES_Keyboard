#include <SNES_Keyboard.h>
SNES_Keyboard snes;

// Pins 5, 7, 9 are set to Clock, Latch, Data by default
void setup() {
}

//B-Y-Sel-Strt-Up-Down-Left-Right-A-X-L-R
//a-b-c-d-e-f-g-h-i-j-k-l <-- pressed by default
void loop() {
  snes.latchData();
  snes.storeData();
  snes.readData();
}
