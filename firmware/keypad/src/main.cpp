#include <Arduino.h>
#include <Wire.h>
#include <PCF8575.h>
#include <pins.h>
#include <keys.h>

PCF8575 PCF1(0x20);
PCF8575 PCF2(0x21);
uint16_t pcf1;
uint16_t pcf2;

/*
 *
 * INTERRUPT ROUTINE + FLAG
 *
 */
volatile bool flag = false;
volatile bool repeatFlag = false;

void pcf_irq(){
  flag = true;
}

void repeat_irq() {
  repeatFlag = true;
}

void setup() {
  // while(!Serial);
  Serial.begin(115200);

  // Let's establish ourselves as a
  Wire.begin();

  // Let's initiate the conversation on the i2c bus
  PCF1.begin();
  PCF2.begin();

  // Set the mode for the interrupt pins
  pinMode(PCF8575_INT, INPUT);
  pinMode(REPEATER_INT, INPUT);

  // Tell the uC which function to execute when interrupted
  attachInterrupt(digitalPinToInterrupt(PCF8575_INT), pcf_irq, RISING);
  attachInterrupt(digitalPinToInterrupt(REPEATER_INT), pcf_irq, RISING);
}

void loop() {
  // Something happened. Let's find out.
  if (flag || repeatFlag) {
    // Reset the flag
    flag = false;
    // Read the status of which keys were (de)pressed from both GPIO expanders
    pcf1 = PCF1.read16();
    pcf2 = PCF2.read16();

    // Someone (de)pressed a key.
    if (pcf1 != 0 || pcf2 != 0) {
      if (pcf1 & DISP && !stateDisplay) {
        stateDisplay = true;
        Serial.println("DISPLAY");
      }
      if (pcf1 & COMP && !stateComp) {
        stateComp = true;
        Serial.println("COMP");
      }
      if (pcf1 & INFEED && !stateInfeed) {
        stateInfeed = true;
        Serial.println("INFEED");
      }
      if (pcf1 & HEAD_POS && !stateHeadPos) {
        stateHeadPos = true;
        Serial.println("HEAD_POS");
      }
      if (pcf1 & FORM_TOOL_IN && !stateFormToolIn) {
        stateFormToolIn = true;
        Serial.println("FORM_TOOL_IN");
      }
      if (pcf1 & SHEAR && !stateShear) {
        stateShear = true;
        Serial.println("SHEAR");
      }
      if (pcf1 & PAUSE && !statePause) {
        statePause = true;
        Serial.println("PAUSE");
      }
      if (pcf1 & RUN && !stateRun) {
        stateRun = true;
        Serial.println("RUN");
      }
      if (pcf1 & UP && (!stateUp || repeatFlag)) {
        stateUp = true;
        Serial.println("UP");
      }
      if (pcf1 & ENTER && !stateEnter) {
        stateEnter = true;
        Serial.println("ENTER");
      }
      if (pcf1 & ONE && (!stateOne || repeatFlag)) {
        stateOne = true;
        Serial.println("ONE");
      }
      if (pcf1 & TWO && (!stateTwo || repeatFlag)) {
        stateTwo = true;
        Serial.println("TWO");
      }
      if (pcf1 & THREE && (!stateThree || repeatFlag)) {
        stateThree = true;
        Serial.println("THREE");
      }
      if (pcf1 & PLUS && (!statePlus || repeatFlag)) {
        statePlus = true;
        Serial.println("PLUS");
      }
      if (pcf1 & LEFT && (!stateLeft || repeatFlag)){
        stateLeft = true;
        Serial.println("LEFT");
      }
      if (pcf1 & MENU && !stateMenu) {
        stateMenu = true;
        Serial.println("MENU");
      }
      // PCF2
      if (pcf2 & RIGHT && (!stateRight || repeatFlag)) {
        stateRight = true;
        Serial.println("RIGHT");
      }
      if (pcf2 & FOUR && (!stateFour || repeatFlag)) {
        stateFour = true;
        Serial.println("FOUR");
      }
      if (pcf2 & FIVE && (!stateFive || repeatFlag)) {
        stateFive = true;
        Serial.println("FIVE");
      }
      if (pcf2 & SIX && (!stateSix || repeatFlag)) {
        stateSix = true;
        Serial.println("SIX");
      }
      if (pcf2 & MINUS && (!stateMinus || repeatFlag)) {
        stateMinus = true;
        Serial.println("MINUS");
      }
      if (pcf2 & MEMORY && (!stateMemory || repeatFlag)) {
        stateMemory = true;
        Serial.println("MEMORY");
      }
      if (pcf2 & DOWN && (!stateDown || repeatFlag)) {
        stateDown = true;
        Serial.println("DOWN");
      }
      if (pcf2 & DECIMAL && !stateDecimal) {
        stateDecimal = true;
        Serial.println("DECIMAL");
      }
      if (pcf2 & SEVEN && (!stateSeven || repeatFlag)) {
        stateSeven = true;
        Serial.println("SEVEN");
      }
      if (pcf2 & EIGHT && (!stateEight || repeatFlag)) {
        stateEight = true;
        Serial.println("EIGHT");
      }
      if (pcf2 & NINE && (!stateNine || repeatFlag)) {
        stateNine = true;
        Serial.println("NINE");
      }
      if (pcf2 & ZERO && (!stateZero || repeatFlag)) {
        stateZero = true;
        Serial.println("ZERO");
      }
    }

    // Update flags and bits
    updatePCFStates(pcf1, pcf2);
    repeatFlag = false;
  }
}

