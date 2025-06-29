//
// Created by Connor on 6/23/2025.
//

#ifndef KEYS_H
#define KEYS_H
/* First PCF8575 GPIO I2C Expander - U408 */
#define DISP 1 // DISPLAY is already defined in Arduino.h
#define COMP 2
#define INFEED 4
#define HEAD_POS 8
#define FORM_TOOL_IN 16
#define SHEAR 32
#define PAUSE 64
#define RUN 128
#define UP 256
#define ENTER 512
#define ONE 1024
#define TWO 2048
#define THREE 4096
#define PLUS 8192
#define LEFT 16384
#define MENU 32768
/* Second PCF8575 GPIO I2C Expander - U407 */
#define RIGHT 1
#define FOUR 2
#define FIVE 4
#define SIX 8
#define MINUS 16
#define MEMORY 32
#define DOWN 64
#define DECIMAL 128
#define SEVEN 256
#define EIGHT 512
#define NINE 1024
#define ZERO 2048

volatile bool stateDisplay = false;
volatile bool stateComp = false;
volatile bool stateInfeed = false;
volatile bool stateHeadPos = false;
volatile bool stateFormToolIn = false;
volatile bool stateShear = false;
volatile bool statePause = false;
volatile bool stateRun = false;
volatile bool stateUp = false;
volatile bool stateEnter = false;
volatile bool stateOne = false;
volatile bool stateTwo = false;
volatile bool stateThree = false;
volatile bool statePlus = false;
volatile bool stateLeft = false;
volatile bool stateMenu = false;
volatile bool stateRight = false;
volatile bool stateFour = false;
volatile bool stateFive = false;
volatile bool stateSix = false;
volatile bool stateMinus = false;
volatile bool stateMemory = false;
volatile bool stateDown = false;
volatile bool stateDecimal = false;
volatile bool stateSeven = false;
volatile bool stateEight = false;
volatile bool stateNine = false;
volatile bool stateZero = false;

inline void resetPCF1Sates() {
  stateDisplay = false;
  stateComp = false;
  stateInfeed = false;
  stateHeadPos = false;
  stateFormToolIn = false;
  stateShear = false;
  statePause = false;
  stateRun = false;
  stateUp = false;
  stateEnter = false;
  stateOne = false;
  stateTwo = false;
  stateThree = false;
  statePlus = false;
  stateLeft = false;
  stateMenu = false;
}

inline void resetPCF2Sates() {
  stateRight = false;
  stateFour = false;
  stateFive = false;
  stateSix = false;
  stateMinus = false;
  stateMemory = false;
  stateDown = false;
  stateDecimal = false;
  stateSeven = false;
  stateEight = false;
  stateNine = false;
  stateZero = false;
}

inline void updatePCFStates(uint16_t pcf1Bits, uint16_t pcf2Bits) {
  stateDisplay = bool(pcf1Bits & DISP);
  stateComp = bool(pcf1Bits & COMP);
  stateInfeed = bool(pcf1Bits & INFEED);
  stateHeadPos = bool(pcf1Bits & HEAD_POS);
  stateFormToolIn = bool(pcf1Bits & FORM_TOOL_IN);
  stateShear = bool(pcf1Bits & SHEAR);
  statePause = bool(pcf1Bits & PAUSE);
  stateRun = bool(pcf1Bits & RUN);
  stateUp = bool(pcf1Bits & UP);
  stateEnter = bool(pcf1Bits & ENTER);
  stateOne = bool(pcf1Bits & ONE);
  stateTwo = bool(pcf1Bits & TWO);
  stateThree = bool(pcf1Bits & THREE);
  statePlus = bool(pcf1Bits & PLUS);
  stateLeft = bool(pcf1Bits & LEFT);
  stateMenu = bool(pcf1Bits & MENU);

  stateRight = bool(pcf2Bits & RIGHT);
  stateFour = bool(pcf2Bits & FOUR);
  stateFive = bool(pcf2Bits & FIVE);
  stateSix = bool(pcf2Bits & SIX);
  stateMinus = bool(pcf2Bits & MINUS);
  stateMemory = bool(pcf2Bits & MEMORY);
  stateDown = bool(pcf2Bits & DOWN);
  stateDecimal = bool(pcf2Bits & DECIMAL);
  stateSeven = bool(pcf2Bits & SEVEN);
  stateEight = bool(pcf2Bits & EIGHT);
  stateNine = bool(pcf2Bits & NINE);
  stateZero = bool(pcf2Bits & ZERO);
}

#endif //KEYS_H
