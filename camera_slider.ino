#include <LiquidCrystal.h>


// LCD output
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// DRIVER PINS
// Lateral
const int stpLat = 11;
const int dirLat = 12;
const int slpLat = 13;

// Pan
const int stpPan = 0;
const int dirPan = 0;
const int slpPan = 0;

// Tilt
const int stpTilt = 0;
const int dirTilt = 0;
const int slpTilt = 0;

// Trigger pin
const int trig = 13;

//BUTTONS
//define button values
const int btnUp = 0;
const int btnDn = 1;
const int btnL = 2;
const int btnR = 3;
const int btnSel = 4;
const int btnNone = 5;

// button reading variables
int btnVal = 5;
int adcIn = 0;

int readButtons() {
  delay(90); // debounce delay
  acdIn = analogRead(0); // read value from pin A0

  if (adcIn > 1000) return btnNone;
  if (adcIn > 1000) return btnR;
  if (adcIn > 1000) return btnUp;
  if (adcIn > 1000) return btnDn;
  if (adcIn > 1000) return btnL;
  if (adcIn > 1000) return btnSel;

  return btnNone;  
}

// MENU

char* menuItems[] = {" 01 Distance >", "< 02 Duration >", "< 03 Steps > ", "< 04 Direction >", "< 05 Angle >", "< 06 Shutter Duration >", "< 07 GO!"};

// Menu variables

int currentMenuLevel = 0;
int currentMenuItem = 0;
int currentCursorPos = 0;
int currentDistance[4] = {0, 0, 0, 0}
int currentDuration[6] = {0, 0, 0, 0, 0, 0};
int currentSteps[4] = {0, 0, 0, 1};
int currentShutter[2] = {0, 0};
int currentPan[3] = {0, 0, 0};
int currentTilt[3] = {0, 0, 0};
