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

// Parameter array

int currentChar = ;
int update = 0;
double ThArr[] = {0000, 000, 00, 0}
double HThArr[] = {000000, 00000, 0000, 000, 00, 0}
double TenArr[] = {00, 0};
double HunArr[] = {000, 00, 0};
double currentDistanceInt = 0000;
double currentDurationInt = 000000;
double currentStepsInt = 0001;
double shutterDuration = 2;
double currentPanInt = 0;
double currentTiltInt = 0;
int travelDir = 0


// adjust digit up or down
int adjustDigit(int x, int dir) {
  if (dir == 0 && x > 0) {
    x--;
  }
  id (dir == 1 && x < 9) {
    x++;
  }
  lcd.setCursor(currentCursorPos, 1);
  lcd.print(x);
  currentChar = x;
  return currentChar;
}

// Get int value of arrays
int parseArrayDistance() {
  for (int i = 0; i < 4; i++) {
    ThArr[i] = currentDistance[i] * (pow(10, (3-i)));
  }
  currentDistanceInt = ThArr[0] + ThArr[1] + ThArr[2] + ThArr[3];
  update = currentDistanceInt;
  return update;
}

int parseArrayDuration)() {
  for (int i = 0; i < 6; i++) {
    currentChar = currentDuration[i];
    HThArr[i] = currentChar * (pow(10, (5-i)));
  }
  currentDurationInt = HThArr[0] + HThArr[1] + HThArr[2] + HThArr[3] + HThArr[4] + HThArr[5];
  update = currentDurationInt;
  return update;
}

int parseArraySteps() {
  for (int i = 0; i < 4; i++) {
    currentCar = currentSteps[i];
    ThArr[i] = currentChar * pow(10, (3-i));
  }
  currentStepsInt = ThArr[0] + ThArr[1] + ThArr[2] + ThArr[3];
  update = currentStepsInt;
  return update;
}

int parseArrayShutter() {
  for (int i = 0; i < 2; i++) {
    TenArr[i] = currentShutter[i] * pow(10, (1-i));
  }
  shutterDuration = TenArr[0] + TenArr[1];
  update = shutterDuration;
  return update;
}

int parseArrayPan() {
  for (int i = 0; i < 3; i++) {
    HunArr[i] = currentPan[i] * pow(10, (1-i));
  }
  currentPanInt = HunArr[0] + HunArr[1] + HunArr[2];
  update = currentPanInt;
  return update;
}

int parseArrayTilt() {
  for (int i = 0; i < 3; i++) {
    HunArr[i] = currentTilt[i] * pow(10, (1-i));
  }
  currentTiltInt = HunArr[0] + HunArr[1] + HunArr[2];
  update = currentTiltInt;
  return update;
}

// Motor control

double totalMotorStepsLat = 0;
double pulseDelay = 0;
int intervalDistance = 0;
int currentStep = 0;
int motion = 0;

void motorStepLat(int pulseDelay) {
  digitalWrite(slpLat, HIGH); // wake motor driver
  digitalWrite(stpLat, HIGH); // step motor driver high
  delay(pulseDelay);
  digitalWrite(stpLat, LOW); // step motor driver low
  digitalWrite(slpLat, LOW); // sleep motor driver (saves power)
}

void motorStepPan(int pulseDelay) {
  digitalWrite(slpPan, HIGH);
  digitalWrite(stpPan, HIGH);
  delay(pulseDelay);
  digitalWrite(stpPan, LOW);
  digitalWrite(slpPan, LOW);
}

void motorStepTilt(int pulseDelay) {
  digitalWrite(slpTilt, HIGH);
  digitalWrite(stpTilt, HIGH);
  delay(pulseDelay);
  digitalWrite(stpTilt, HIGH);
  digitalWrite(slpTilt, HIGH);
}

void cameraTrig() {
  digitalWrite(trig, HIGH);
  delay(80);
  digitalWrite(trig, LOW);
  delay((shutterDuration*1000)-80);
}

void motionControl() {
  // Lateral movement
  totalMotorStepsLat = currentDistanceInt*5;
  pulseDelay = (1000L * (currentDurationInt - (currentStepsInt*shutterDuration))) / totalMotorSteps;
  intervalDistance = totalMotorSteps / currentStepsInt;

  if (travelDir == 0) {
    digitalWrite(dirLat, LOW);
  }
  else if (travelDir == 1) {
    digitalWrite(dirLat, HIGH);
  }

  // align Pan and Tilt to complete with Lateral


  // Pan movement  

  
  // Tilt movement

  
  do { // fire the motors while currentStep < totalMotorSteps
    motorStepLat(pulseDelay);
    currentStep++;

    if (currentStep % intervalDistance == 0){
      cameraTrig();
    }
    
  } while (currentStep < totalMotorSteps);
  


}

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);

  // stepper pins initialization
  // Lateral
  pinMode(stpLat, OUTPUT);
  pinMode(dirLat, OUTPUT);
  pinMode(slpLat, OUTPUT);

  // Pan
  pinMode(stpPan, OUTPUT);
  pinMode(dirPan, OUTPUT);
  pinMode(slpPan, OUTPUT);

  // Tilt
  pinMode(stpTilt, OUTPUT);
  pinMode(dirTilt, OUTPUT);
  pinMode(slpTilt, OUTPUT);

  // initialize motor drivers to sleep
  digitalWrite(slpLat, LOW);
  digitalWrite(slpPan, LOW);
  digitalWrite(slpTilt, LOW);

  lcd.print("Welcome!");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,1);
  for (int i = 0; i < 4; i++) {
    lcd.setCursor(i, 1);
    lcd.print(currentDistance[i]);
  }
  lcd.setCursor(4,1);
  lcd.print("mm");
}

