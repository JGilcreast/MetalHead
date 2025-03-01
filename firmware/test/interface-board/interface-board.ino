#include "MetalHeadPins.h"
#include "InterruptEnums.h"
#include <at24c256.h> // AT24C by Stefan
#include <cppQueue.h> // Queue by SMFSW

// Global objects and variables that ISRs and loop can access
// Interface interface;
AT24C256 eprom(AT24C_ADDRESS_0);
cppQueue q(sizeof(Interrupt), 512, FIFO, true);
int interruptCount = 1;


struct Person{
  char firstName[16];
  char lastName[16];
  int id;
};

void setup() {
  // Setup serial to print to the console
  Serial.begin(115200);

  // EEPROM setup
  Wire.begin();

  // Let's test the EEPROM
  Person john = {"John", "Gilcreast", 1234};
  Person connor = {"Connor", "McMillan", 4321};
  Person personOne;
  Person personTwo;
  // Bytes = 36 (firstName + lastName + id = 16 + 16 + 4)
  // Members of the class/structure need to be fixed.
  // So name, desc, & note from Receipe class should be fixed to say 256 bytes maximum.
  // This is something we can also enforce in the HMI.
  // We are working with a 256Kb EEPROM. That is we have 32,768 bytes to work with.
  // You will need to keep track of how many recipes are saved in the EEPROM.
  // Maybe the first byte will have the number of recipes so that you can calculate the read address for get()
  // The 0 and 36 passed to put() are the addresses in EEPROM memory where the class/structure is saved into.
  // Structure the EEPROM layout so that you can save more recipes but not over write other data such as settings.
  // So: Byte 0 = Number of recipes saved (0-255)
  //     Byte 1 - 32,000 = Recipes
  //     Byte 32,001 - 32,767 = Settings
  eprom.put(0, john);
  eprom.put(36, connor);

  eprom.get(0, personOne);

  if (eprom.getLastError() != 0) {
    Serial.print("Error reading from eeprom!!");
  } else {
    Serial.println("Person #1:");
    Serial.print("    First Name: ");
    Serial.println(personOne.firstName);
    Serial.print("    Last Name: ");
    Serial.println(personOne.lastName);
    Serial.print("    ID: ");
    Serial.println(personOne.id);
  }

  eprom.get(36, personTwo);

  if (eprom.getLastError() != 0) {
    Serial.print("Error reading from eeprom!!");
  } else {
    Serial.println("Person #2:");
    Serial.print("    First Name: ");
    Serial.println(personTwo.firstName);
    Serial.print("    Last Name: ");
    Serial.println(personTwo.lastName);
    Serial.print("    ID: ");
    Serial.println(personTwo.id);
  }

  // Define the mode of each pin
  // Ouputs
  pinMode(SHEAR_CUT, OUTPUT);
  pinMode(SHEAR_HOME, OUTPUT);
  pinMode(TOOL_OUT, OUTPUT);
  pinMode(TOOL_IN, OUTPUT);
  pinMode(FEED_FORWARD, OUTPUT);
  pinMode(FEED_REVERSE, OUTPUT);
  pinMode(HEAD_CW, OUTPUT);
  pinMode(HEAD_CCW, OUTPUT);
  pinMode(HEAD_OUT, OUTPUT);
  pinMode(HEAD_IN, OUTPUT);
  // Inputs
  pinMode(ENCODER_FEED_SET, INPUT);
  pinMode(ENCODER_FEED_RESET, INPUT);
  pinMode(ENCODER_BEND_SET, INPUT);
  pinMode(ENCODER_BEND_RESET, INPUT);
  pinMode(PROXIMITY_HEAD_OUT, INPUT);
  pinMode(PROXIMITY_HEAD_IN, INPUT);
  pinMode(PROXIMITY_SHEAR_HOME, INPUT);
  pinMode(PROXIMITY_SHEAR_CUT, INPUT);
  pinMode(PROXIMITY_TOOL_IN, INPUT);
  pinMode(PROXIMITY_TOOL_OUT, INPUT);
  pinMode(SHEAR_BUTTON, INPUT);
  pinMode(PROXIMITY_HEAD_LIMIT, INPUT);
  pinMode(PROXIMITY_HEAD_CW, INPUT);
  pinMode(PROXIMITY_HEAD_CCW, INPUT);
  pinMode(AUTO_BUTTON, INPUT);
  pinMode(ESTOP, INPUT);
  pinMode(FUSE, INPUT);

  // Turn off all outputs by default
  digitalWrite(SHEAR_CUT, LOW);
  digitalWrite(SHEAR_HOME, LOW);
  digitalWrite(TOOL_OUT, LOW);
  digitalWrite(TOOL_IN, LOW);
  digitalWrite(FEED_FORWARD, LOW);
  digitalWrite(FEED_REVERSE, LOW);
  digitalWrite(HEAD_CW, LOW);
  digitalWrite(HEAD_CCW, LOW);
  digitalWrite(HEAD_OUT, LOW);
  digitalWrite(HEAD_IN, LOW);

  // Setup interrupts for inputs at the rising edge
  attachInterrupt(digitalPinToInterrupt(ENCODER_FEED_SET), interruptEncoderFeedSetRising, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_FEED_RESET), interruptEncoderFeedResetRising, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_BEND_SET), interruptEncoderBendSetRising, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_BEND_RESET), interruptEncoderBendResetRising, RISING);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_HEAD_OUT), interruptProximityHeadOutRising, RISING);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_HEAD_IN), interruptProximityHeadInRising, RISING);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_SHEAR_HOME), interruptProximityShearHomeRising, RISING);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_SHEAR_CUT), interruptProximityShearCutRising, RISING);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_TOOL_IN), interruptProximityToolInRising, RISING);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_TOOL_OUT), interruptProximityToolOutRising, RISING);
  attachInterrupt(digitalPinToInterrupt(SHEAR_BUTTON), interruptShearButtonRising, RISING);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_HEAD_LIMIT), interruptProximityHeadLimitRising, RISING);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_HEAD_CW), interruptProximityHeadCwRising, RISING);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_HEAD_CCW), interruptProximityHeadCcwRising, RISING);
  attachInterrupt(digitalPinToInterrupt(AUTO_BUTTON), interruptAutoButtonRising, RISING);

  // Setup interrupts for inputs on the falling edge.
  // Sometimes we need to know when a sensor deactivates, i.e. to confirm if the tool head actually travelled in the opposite direction
  
  // When ESTOP is HIGH, ESTOP button is in the out most position (normal operation).
  // When ESTOP is LOW, ESTOP button is depressed (emergency stop)
  // When FUSE is HIGH, FUSE is not blown (normal operation)
  // When FUSE is LOW, FUSE is blown (alert HMI so operator can diagnose)
  attachInterrupt(digitalPinToInterrupt(FUSE), interruptFuseFalling, FALLING);
  attachInterrupt(digitalPinToInterrupt(ESTOP), interruptEstopChange, CHANGE);

  // Let's check to see if the machine is homed correctly.
  // Someone may have moved the head or tool manually in between startups that we were not aware of.
  // Think of this as homing a 3D printer. We might consider using this inside interface.feed() before making recipes in the main loop
  // interface.home(); // Check each sensor, if it's high, trigger the solenoid to home it
}

void loop() {
  // Here we feed rebar almost indefinetly. Of course that's not what we will actually do.
  // We will only act upon when we receive commands from the HMI.
  // For the sake of simplicity, the main loop will have about three methods doing the heavy work.
  
  // interface.checkFuse(); // Check if the fuse has blown every second or two.
                            // Send a StopEvent to the HMI when needed.
                            // if(digitalRead(FUSE) == LOW){Serial.println("Fuse has blown!")}
  // interface.checkInbox(); // Check to see if we have StopEvents, recipes to be made, etc. from the HMI.
  // interface.feed(); // Feed, bend, cut, stop this solenoid, stop that solenoid, stop everything when interface.eStop is true, etc
  // interface.updateHMI(); // Send new solenoid/sensor status to HMI. This may include recipes from EEPROM, settings from EEPROM, etc

  // // Test the solenoid outputs
  // // Turn on SHEAR_CUT solenoid
  // digitalWrite(SHEAR_CUT, HIGH);
  // // Pause for 2 seconds
  // delay(2000);
  // // Turn off SHEAR_CUT solenoid
  // digitalWrite(SHEAR_CUT, LOW);  

  // // Turn on SHEAR_HOME solenoid
  // digitalWrite(SHEAR_HOME, HIGH);
  // // Pause for 2 seconds
  // delay(2000);
  // // Turn off SHEAR_HOME solenoid
  // digitalWrite(SHEAR_HOME, LOW);  

  // // Turn on TOOL_OUT solenoid
  // digitalWrite(TOOL_OUT, HIGH);
  // // Pause for 2 seconds
  // delay(2000);
  // // Turn off TOOL_OUT solenoid
  // digitalWrite(TOOL_OUT, LOW);  

  // // Turn on TOOL_IN solenoid
  // digitalWrite(TOOL_IN, HIGH);
  // // Pause for 2 seconds
  // delay(2000);
  // // Turn off TOOL_IN solenoid
  // digitalWrite(TOOL_IN, LOW);

  // // Turn on FEED_FORWARD solenoid
  // digitalWrite(FEED_FORWARD, HIGH);
  // // Pause for 2 seconds
  // delay(2000);
  // // Turn off FEED_FORWARD solenoid
  // digitalWrite(FEED_FORWARD, LOW);  

  // // Turn on FEED_REVERSE solenoid
  // digitalWrite(FEED_REVERSE, HIGH);
  // // Pause for 2 seconds
  // delay(2000);
  // // Turn off FEED_REVERSE solenoid
  // digitalWrite(FEED_REVERSE, LOW);  

  // // Turn on HEAD_CW solenoid
  // digitalWrite(HEAD_CW, HIGH);
  // // Pause for 2 seconds
  // delay(2000);
  // // Turn off HEAD_CW solenoid
  // digitalWrite(HEAD_CW, LOW);  

  // // Turn on HEAD_CCW solenoid
  // digitalWrite(HEAD_CCW, HIGH);
  // // Pause for 2 seconds
  // delay(2000);
  // // Turn off HEAD_CCW solenoid
  // digitalWrite(HEAD_CCW, LOW);  

  // // Turn on HEAD_OUT solenoid
  // digitalWrite(HEAD_OUT, HIGH);
  // // Pause for 2 seconds
  // delay(2000);
  // // Turn off HEAD_OUT solenoid
  // digitalWrite(HEAD_OUT, LOW);

  // // Turn on HEAD_IN solenoid
  // digitalWrite(HEAD_IN, HIGH);
  // // Pause for 2 seconds
  // delay(2000);
  // // Turn off HEAD_IN solenoid
  // digitalWrite(HEAD_IN, LOW);

  // Process debug interrupt queue to print to serial
  if(!q.isEmpty()){
    Interrupt interrupt;
    q.pop(&interrupt);
    Serial.print("Interrupt #");
    Serial.print(interruptCount);
    Serial.print(": ");
    if (interrupt == Interrupt::ENCODER_FEED_SET_INT)
      Serial.println("ENCODER_FEED_SET");
    if (interrupt == Interrupt::ENCODER_FEED_RESET_INT)
      Serial.println("ENCODER_FEED_RESET");
    if (interrupt == Interrupt::ENCODER_BEND_SET_INT)
      Serial.println("ENCODER_BEND_SET");
    if (interrupt == Interrupt::ENCODER_BEND_RESET_INT)
      Serial.println("ENCODER_BEND_RESET");
    if (interrupt == Interrupt::PROXIMITY_HEAD_OUT_INT)
      Serial.println("PROXIMITY_HEAD_OUT");
    if (interrupt == Interrupt::PROXIMITY_HEAD_IN_INT)
      Serial.println("PROXIMITY_HEAD_IN");
    if (interrupt == Interrupt::PROXIMITY_SHEAR_HOME_INT)
      Serial.println("PROXIMITY_SHEAR_HOME");
    if (interrupt == Interrupt::PROXIMITY_SHEAR_CUT_INT)
      Serial.println("PROXIMITY_SHEAR_CUT");
    if (interrupt == Interrupt::PROXIMITY_TOOL_IN_INT)
      Serial.println("PROXIMITY_TOOL_IN");
    if (interrupt == Interrupt::PROXIMITY_TOOL_OUT_INT)
      Serial.println("PROXIMITY_TOOL_OUT");
    if (interrupt == Interrupt::SHEAR_BUTTON_INT)
      Serial.println("SHEAR_BUTTON");
    if (interrupt == Interrupt::PROXIMITY_HEAD_LIMIT_INT)
      Serial.println("PROXIMITY_HEAD_LIMIT");
    if (interrupt == Interrupt::PROXIMITY_HEAD_CW_INT)
      Serial.println("PROXIMITY_HEAD_CW");
    if (interrupt == Interrupt::PROXIMITY_HEAD_CCW_INT)
      Serial.println("PROXIMITY_HEAD_CCW");
    if (interrupt == Interrupt::AUTO_BUTTON_INT)
      Serial.println("AUTO_BUTTON");
    if (interrupt == Interrupt::ESTOP_INT)
      Serial.println("ESTOP");
    if (interrupt == Interrupt::NORMAL_OPERATION_INT)
      Serial.println("NORMAL_OPERATION");
    if (interrupt == Interrupt::FUSE_INT)
      Serial.println("FUSE");
    interruptCount++;
  }

}

// These are the ISRs (Interrupt Service Routines) for the rising edges as soon as the sensors trigger.
// We never want to execute code that blocks normal execution of loop here. That includes calls to the Serial class.
// Instead set some sort of flag (i.e. myInterface.someFlag = true;) that loop can access and act upon.

void interruptEncoderFeedSetRising(){
  // Keep track of feed ticks. Stop feed when needed (inside of loop).
  // i.e. interface.encoderFeedCount++;
  q.push(&encoderFeedSetInterrupt); // Send to queue for serial debugging
}

void interruptEncoderFeedResetRising(){
  // Keep track of feed ticks. Stop feed when needed (inside of loop).
  // i.e. interface.encoderFeedCount++;
  q.push(&encoderFeedResetInterrupt); // Send to queue for serial debugging
}

void interruptEncoderBendSetRising(){
  // Keep track of bend ticks. Stop bending when needed.
  // i.e. interface.encoderBendCount++;
  q.push(&encoderBendSetInterrupt); // Send to queue for serial debugging
}

void interruptEncoderBendResetRising(){
  // Keep track of bend ticks. Stop bending when needed.
  // i.e. interface.encoderBendCount++;
  q.push(&encoderBendResetInterrupt); // Send to queue for serial debugging
}

void interruptProximityHeadOutRising(){
  // Turn off HEAD_OUT solenoid
  // interface.proximityHeadOut = true;
  q.push(&proximityHeadOutInterrupt); // Send to queue for serial debugging
}

void interruptProximityHeadInRising(){
  // Turn off HEAD_IN solenoid
  // interface.proximityHeadIn = true;
  q.push(&proximityHeadInInterrupt); // Send to queue for serial debugging
}

void interruptProximityShearHomeRising(){
  // Turn off SHEAR_HOME solenoid
  // interface.proximityShearHome = true;
  q.push(&proximityShearHomeInterrupt); // Send to queue for serial debugging
}

void interruptProximityShearCutRising(){
  // Turn off SHEAR_CUT solenoid
  // interface.proximityShearCut = true;
  q.push(&proximityShearCutInterrupt); // Send to queue for serial debugging
}

void interruptProximityToolInRising(){
  // Turn off TOOL_IN solenoid
  // interface.proximityToolIn = true;
  q.push(&proximityToolInInterrupt); // Send to queue for serial debugging
}

void interruptProximityToolOutRising(){
  // Turn off TOOL_OUT solenoid
  // interface.proximityToolOut = true;
  q.push(&proximityToolOutInterrupt); // Send to queue for serial debugging
}

void interruptShearButtonRising(){
  // interface.shearButton = true;
  q.push(&shearButtonInterrupt); // Send to queue for serial debugging
}

void interruptProximityHeadLimitRising(){
  // I don't know what this proximity sensor stops.
  // The head has it's own respective set of CW, CCW, IN, and OUT proximity sensors with solenoids
  // interface.proximityHeadLimit = true;
  q.push(&proximityHeadLimitInterrupt); // Send to queue for serial debugging
}

void interruptProximityHeadCwRising(){
  // Turn off HEAD_CW solenoid
  // interface.proximityHeadCw = true;
  q.push(&proximityHeadCwInterrupt); // Send to queue for serial debugging
}

void interruptProximityHeadCcwRising(){
  // Turn off HEAD_CCW solenoid
  // interface.proximityHeadCcw = true;
  q.push(&proximityHeadCcwInterrupt); // Send to queue for serial debugging
}

void interruptAutoButtonRising(){
  // interface.autoButton = true;
  q.push(&autoButtonInterrupt); // Send to queue for serial debugging
}

void interruptEstopChange(){
  // Stop everything!!
  // interface.eStop = true;
  // The main loop code should send a StopEvent to the HMI
  // There currently is an issue with Rev X1 of the Interface Board where ESTOP is momentarily pulled LOW at power up.
  // CM needs to debug this further or JG implements a mechanism to ignore the first interrupt upon power up.
  if (digitalRead(ESTOP) == LOW)
    q.push(&eStopInterrupt); // Send to queue for serial debugging
  else
    q.push(&normalOperationInterrupt); // Send to queue for serial debugging
}

void interruptFuseFalling(){
  // Stop everything!!
  // The fuse for the solenoids has blown
  // interface.fuseBlown = true;
  // The main loop code should send a StopEvent to the HMI
  // We also need to implement something at startup of the machine to check if the fuse has blown and send a StopEvent to the HMI.
  q.push(&fuseInterrupt); // Send to queue for serial debugging
}