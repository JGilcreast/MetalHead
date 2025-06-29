//
// Created by Connor on 6/23/2025.
//

#ifndef KEYS_H
#define KEYS_H
/* First PCF8575 GPIO I2C Expander - U408 */
#define DISP          0b0000000000000001 // DISPLAY is already defined in Arduino.h
#define COMP          0b0000000000000010
#define INFEED        0b0000000000000100
#define HEAD_POS      0b0000000000001000
#define FORM_TOOL_IN  0b0000000000010000
#define SHEAR         0b0000000000100000
#define PAUSE         0b0000000001000000
#define RUN           0b0000000010000000
#define UP            0b0000000100000000
#define ENTER         0b0000001000000000
#define ONE           0b0000010000000000
#define TWO           0b0000100000000000
#define THREE         0b0001000000000000
#define PLUS          0b0010000000000000
#define LEFT          0b0100000000000000
#define MENU          0b1000000000000000
/* Second PCF8575 GPIO I2C Expander - U407 */
#define RIGHT         0b0000000000000001
#define FOUR          0b0000000000000010
#define FIVE          0b0000000000000100
#define SIX           0b0000000000001000
#define MINUS         0b0000000000010000
#define MEMORY        0b0000000000100000
#define DOWN          0b0000000001000000
#define DECIMAL       0b0000000010000000
#define SEVEN         0b0000000100000000
#define EIGHT         0b0000001000000000
#define NINE          0b0000010000000000
#define ZERO          0b0000100000000000

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
