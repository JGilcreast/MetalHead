#include <Arduino.h>
#include <Wire.h>
#include <PCF8575.h>
#include <pins.h>
#include <keys.h>

uint8_t pi02wI2cAddr = 100;
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

void send(const char key[]) {
  Serial.println(key);
  Wire.beginTransmission(pi02wI2cAddr);
  Wire.write(key);
  Wire.endTransmission();
}

void setup() {
  // while(!Serial);
  Serial.begin(115200);

  // Let's establish ourselves as
  Wire.begin();

  // Let's initiate the conversation on the i2c bus
  PCF1.begin();
  PCF2.begin();

  // Set the mode for the interrupt pins
  pinMode(PCF8575_INT, INPUT);
  pinMode(REPEATER_INT, INPUT);

  // Tell the uC which function to execute when interrupted
  attachInterrupt(digitalPinToInterrupt(PCF8575_INT), pcf_irq, RISING);
  attachInterrupt(digitalPinToInterrupt(REPEATER_INT), repeat_irq, RISING);
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
        send("DISPLAY");
      }
      if (pcf1 & COMP && !stateComp) {
        stateComp = true;
        send("COMP");
      }
      if (pcf1 & INFEED && !stateInfeed) {
        stateInfeed = true;
        send("INFEED");
      }
      if (pcf1 & HEAD_POS && !stateHeadPos) {
        stateHeadPos = true;
        send("HEAD_POS");
      }
      if (pcf1 & FORM_TOOL_IN && !stateFormToolIn) {
        stateFormToolIn = true;
        send("FORM_TOOL_IN");
      }
      if (pcf1 & SHEAR && !stateShear) {
        stateShear = true;
        send("SHEAR");
      }
      if (pcf1 & PAUSE && !statePause) {
        statePause = true;
        send("PAUSE");
      }
      if (pcf1 & RUN && !stateRun) {
        stateRun = true;
        send("RUN");
      }
      if (pcf1 & UP && (!stateUp || repeatFlag)) {
        stateUp = true;
        send("UP");
      }
      if (pcf1 & ENTER && !stateEnter) {
        stateEnter = true;
        send("ENTER");
      }
      if (pcf1 & ONE && (!stateOne || repeatFlag)) {
        stateOne = true;
        send("ONE");
      }
      if (pcf1 & TWO && (!stateTwo || repeatFlag)) {
        stateTwo = true;
        send("TWO");
      }
      if (pcf1 & THREE && (!stateThree || repeatFlag)) {
        stateThree = true;
        send("THREE");
      }
      if (pcf1 & PLUS && (!statePlus || repeatFlag)) {
        statePlus = true;
        send("PLUS");
      }
      if (pcf1 & LEFT && (!stateLeft || repeatFlag)){
        stateLeft = true;
        send("LEFT");
      }
      if (pcf1 & MENU && !stateMenu) {
        stateMenu = true;
        send("MENU");
      }
      // PCF2
      if (pcf2 & RIGHT && (!stateRight || repeatFlag)) {
        stateRight = true;
        send("RIGHT");
      }
      if (pcf2 & FOUR && (!stateFour || repeatFlag)) {
        stateFour = true;
        send("FOUR");
      }
      if (pcf2 & FIVE && (!stateFive || repeatFlag)) {
        stateFive = true;
        send("FIVE");
      }
      if (pcf2 & SIX && (!stateSix || repeatFlag)) {
        stateSix = true;
        send("SIX");
      }
      if (pcf2 & MINUS && (!stateMinus || repeatFlag)) {
        stateMinus = true;
        send("MINUS");
      }
      if (pcf2 & MEMORY && (!stateMemory || repeatFlag)) {
        stateMemory = true;
        send("MEMORY");
      }
      if (pcf2 & DOWN && (!stateDown || repeatFlag)) {
        stateDown = true;
        send("DOWN");
      }
      if (pcf2 & DECIMAL && !stateDecimal) {
        stateDecimal = true;
        send("DECIMAL");
      }
      if (pcf2 & SEVEN && (!stateSeven || repeatFlag)) {
        stateSeven = true;
        send("SEVEN");
      }
      if (pcf2 & EIGHT && (!stateEight || repeatFlag)) {
        stateEight = true;
        send("EIGHT");
      }
      if (pcf2 & NINE && (!stateNine || repeatFlag)) {
        stateNine = true;
        send("NINE");
      }
      if (pcf2 & ZERO && (!stateZero || repeatFlag)) {
        stateZero = true;
        send("ZERO");
      }
    }

    // Update flags and bits
    updatePCFStates(pcf1, pcf2);
    repeatFlag = false;
  }
}

