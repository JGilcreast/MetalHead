// John Gilcreast
// December 15th 2024
// Interface class header file
// For use with Arduino Driver for Automatic Rebar Bender machine

#ifndef INTERFACE_H
#define INTERFACE_H

#include "StatusIndicators.pb.h"
#include "Recipe.h"
#include "PrimaryAction.h"
#include "SecondayAction.h"
#include "State.h"
#include <cppQueue.h>

class Interface{
protected:
  State state = HOME; // Default state at startup
  // Do this, oh wait, do that before doing this
  PrimaryAction primaryAction = NONE; // Cut the rebar
  SecondaryAction secondaryAction = NA; // Sometimes we have to retract
  Recipe recipeToProcess; // Current recipe being processed
  // This queue can hold 32 recipes at a time
  cppQueue recipeQueue = cppQueue(sizeof(Recipe), 32, FIFO, true);
public:
  StatusIndicators statusIndicators = StatusIndicators_init_zero;
  cppQueue* intQueue; // Debug queue that logs to serial to help us debug/understand what is happening in realtime

  // Constructor
  explicit Interface(cppQueue* queue) {
    this->intQueue = queue;
  };

  // Main loop, this runs inside of loop in main()
  void loop() {
    // We do not want to do anything if the machine is in either of these two states
    // ESTOP and FUSE have inverted logic. I might flip this at the hardware level in the next iteration
    // So, if ESTOP == 0/LOW, someone slammed on the estop button to stop the machine
    // if FUSE == 0/LOW, the fuse for the solenoids is blown, and we can't do anything
    if (!this->statusIndicators.eStop || !this->statusIndicators.fuse) {
      // We home when powered on and before processing each recipe
      if (this->state == HOME) {
        home();
      } else if (this->state == PROCESS_RECIPE) {
        processRecipeLine();
      }
    }
  }

  // General machine functions

  // Let's check to see if the machine is homed correctly.
  // Someone may have moved the head or tool manually in between startups that we were not aware of.
  // Think of this as homing a 3D printer at start up and in between print jobs.
  void home() {
    retractShear();
    retractTool();
    retractHead();
    // We're done with the homing sequence
    this->state = IDLE;
  };

  // Turn on or off
  static void turnOnShearCut() {
    digitalWrite(SHEAR_CUT_PIN, HIGH);
  }
  static void turnOffShearCut() {
    digitalWrite(SHEAR_CUT_PIN, LOW);
  }
  static bool getShearCutStatus() {
    return digitalRead(SHEAR_CUT_PIN);
  }
  static void turnOnShearHome() {
    digitalWrite(SHEAR_HOME_PIN, HIGH);
  }
  static void turnOffShearHome() {
    digitalWrite(SHEAR_HOME_PIN, LOW);
  }
  static bool getShearHomeStatus() {
    return digitalRead(SHEAR_HOME_PIN);
  }
  static void turnOnToolOut() {
    digitalWrite(TOOL_OUT_PIN, HIGH);
  }
  static void turnOffToolOut() {
    digitalWrite(TOOL_OUT_PIN, LOW);
  }
  static bool getToolOutStatus() {
    return digitalRead(TOOL_OUT_PIN);
  }
  static void turnOnToolIn() {
    digitalWrite(TOOL_IN_PIN, HIGH);
  }
  static void turnOffToolIn() {
    digitalWrite(TOOL_IN_PIN, LOW);
  }
  static bool getToolInStatus() {
    return digitalRead(TOOL_IN_PIN);
  }
  static void turnOnFeedForward() {
    digitalWrite(FEED_FORWARD_PIN, HIGH);
  }
  static void turnOffFeedForward() {
    digitalWrite(FEED_FORWARD_PIN, LOW);
  }
  static bool getFeedForwardStatus() {
    return digitalRead(FEED_FORWARD_PIN);
  }
  static void turnOnFeedReverse() {
    digitalWrite(FEED_REVERSE_PIN, HIGH);
  }
  static void turnOffFeedReverse() {
    digitalWrite(FEED_REVERSE_PIN, LOW);
  }
  static bool getFeedReverseStatus() {
    return digitalRead(FEED_REVERSE_PIN);
  }
  static void turnOnHeadCw() {
    digitalWrite(HEAD_CW_PIN, HIGH);
  }
  static void turnOffHeadCw() {
    digitalWrite(HEAD_CW_PIN, LOW);
  }
  static bool getHeadCwStatus() {
    return digitalRead(HEAD_CW_PIN);
  }
  static void turnOnHeadCcw() {
    digitalWrite(HEAD_CCW_PIN, HIGH);
  }
  static void turnOffHeadCcw() {
    digitalWrite(HEAD_CCW_PIN, LOW);
  }
  static bool getHeadCcwStatus() {
    return digitalRead(HEAD_CCW_PIN);
  }
  static void turnOnHeadOut() {
    digitalWrite(HEAD_OUT_PIN, HIGH);
  }
  static void turnOffHeadOut() {
    digitalWrite(HEAD_OUT_PIN, LOW);
  }
  static bool getHeadOutStatus() {
    return digitalRead(HEAD_OUT_PIN);
  }
  static void turnOnHeadIn() {
    digitalWrite(HEAD_IN_PIN, HIGH);
  }
  static void turnOffHeadIn() {
    digitalWrite(HEAD_IN_PIN, LOW);
  }
  static bool getHeadInStatus() {
    return digitalRead(HEAD_IN_PIN);
  }

  // Will be mostly used by ESTOP
  static void turnOffEverything() {
    turnOffShearCut();
    turnOffShearHome();
    turnOffToolOut();
    turnOffToolIn();
    turnOffFeedForward();
    turnOffFeedReverse();
    turnOffHeadCw();
    turnOffHeadCcw();
    turnOffHeadOut();
    turnOffHeadIn();
  }

  // Simple actions
  // These utilize turn on and offs to complete a task (e.g. cut the rebar)
  void cutRebar() {
    // Keep retracting shear if needed
    if (this->secondaryAction == SHEAR_RETRACT) {
      retractShear();
      return;
    }

    // Retract shear if shear is in limbo
    if (this->primaryAction == SHEAR) { // If the primary action is to shear
      if (this->secondaryAction == NA) { // and if there is no secondary action
        if (!this->statusIndicators.proximityShearHome) { // and if shear is NOT in home position
          if (!getShearCutStatus()) { // and if shear solenoid is NOT already turned on
            this->secondaryAction = SHEAR_RETRACT;
            retractShear();
            return;
          }
        }
      }
    }

    // If the shear is in the home position, and its solenoid is off, activate the solenoid to cut it
    if (primaryAction == SHEAR) // If the primary action is to shear
      if (!getShearCutStatus()) // and if the shear solenoid is off
          if (this->secondaryAction == NA) { // And there are no secondary actions in the queue
            turnOnShearCut();
            return;
          }

    // Continue to shear until we reach the limit
    if (primaryAction == SHEAR) // If the primary action is to shear
      if (getShearCutStatus()) // and if the shear solenoid is on
        if (this->statusIndicators.proximityShearCut) { // and if the shear reached its limit
          turnOffShearCut(); // Turn off the shear
          this->primaryAction = NONE; // We are done shearing
          this->secondaryAction = SHEAR_RETRACT; // Retract the shear
          retractShear();
        }
  }

  void bendRebarCw() {

  }

  void bendRebarCcw() {

  }

  void retractShear() {
    if (this->secondaryAction == SHEAR_RETRACT) // Are we supposed to retract back?
      if (!this->statusIndicators.proximityShearHome) // Are we back home yet?
        turnOnShearHome(); // Keep going back home
      else {
        turnOffShearHome(); // We're home!
        this->secondaryAction = NA; // We're finished with this action
      }

  }

  void retractTool() {

  }

  void retractHead() {

  }

  // Receipes
  bool checkReceipe(Recipe recipe);

  bool addReceipe(Recipe recipe);

  void deleteReceipe(int id);

  // INCOMPLETE
  void processRecipeLine() {
    // Are we done processing all the lines for the recipe?
    if (this->recipeToProcess.getLinesCompleted() < this->recipeToProcess.getTotalLines())
      // Get the next line to process
      this->recipeToProcess.getline(this->recipeToProcess.getLinesCompleted());

  }

  // Interrupt Service Routines
  // These are the ISRs (Interrupt Service Routines) for the rising edges as soon as the sensors trigger.
  // We never want to execute code that blocks normal execution of loop here. That includes calls to the Serial class.
  // Instead, set some sort of flag (i.e. myInterface.someFlag = true;) that loop can access and act upon.
  void interruptEncoderFeedSet(){
    // Keep track of feed ticks. Stop feed when needed (inside of loop).
    // i.e. interface.encoderFeedCount++;
    this->statusIndicators.encoderFeedCount++;
    this->intQueue->push(&encoderFeedSetInterrupt); // Send to queue for serial debugging
  }

  void interruptEncoderFeedReset(){
    // Keep track of feed ticks. Stop feed when needed (inside of loop).
    // i.e. interface.encoderFeedCount++;
    this->statusIndicators.encoderFeedCount++;
    this->intQueue->push(&encoderFeedResetInterrupt); // Send to queue for serial debugging
  }

  void interruptEncoderBendSet(){
    // Keep track of bend ticks. Stop bending when needed.
    // i.e. interface.encoderBendCount++;
    this->statusIndicators.encoderBendCount++;
    this->intQueue->push(&encoderBendSetInterrupt); // Send to queue for serial debugging
  }

  void interruptEncoderBendReset(){
    // Keep track of bend ticks. Stop bending when needed.
    // i.e. interface.encoderBendCount++;
    this->statusIndicators.encoderBendCount++;
    this->intQueue->push(&encoderBendResetInterrupt); // Send to queue for serial debugging
  }

  void interruptProximityHeadOut(){
    // Turn off HEAD_OUT solenoid
    // interface.proximityHeadOut = true;
    if (digitalRead(PROXIMITY_HEAD_OUT_PIN))
      this->statusIndicators.proximityHeadOut = true;
    else
      this->statusIndicators.proximityHeadOut = false;
    this->intQueue->push(&proximityHeadOutInterrupt); // Send to queue for serial debugging
  }

  void interruptProximityHeadIn(){
    // Turn off HEAD_IN solenoid
    // interface.proximityHeadIn = true;
    if (digitalRead(PROXIMITY_HEAD_IN_PIN))
      this->statusIndicators.proximityHeadIn = true;
    else
      this->statusIndicators.proximityHeadIn = false;
    this->intQueue->push(&proximityHeadInInterrupt); // Send to queue for serial debugging
  }

  void interruptProximityShearHome(){
    // Turn off SHEAR_HOME solenoid
    // interface.proximityShearHome = true;
    if (digitalRead(SHEAR_HOME_PIN))
      this->statusIndicators.proximityShearHome = true;
    else
      this->statusIndicators.proximityShearHome = false;
    this->intQueue->push(&proximityShearHomeInterrupt); // Send to queue for serial debugging
  }

  void interruptProximityShearCut(){
    // Turn off SHEAR_CUT solenoid
    // interface.proximityShearCut = true;
    if (digitalRead(PROXIMITY_SHEAR_CUT_PIN))
      this->statusIndicators.proximityShearCut = true;
    else
      this->statusIndicators.proximityShearCut = false;
    this->intQueue->push(&proximityShearCutInterrupt); // Send to queue for serial debugging
  }

  void interruptProximityToolIn(){
    // Turn off TOOL_IN solenoid
    // interface.proximityToolIn = true;
    if (digitalRead(PROXIMITY_TOOL_IN_PIN))
      this->statusIndicators.proximityToolIn = true;
    else
      this->statusIndicators.proximityToolIn = false;
    this->intQueue->push(&proximityToolInInterrupt); // Send to queue for serial debugging
  }

  void interruptProximityToolOut(){
    // Turn off TOOL_OUT solenoid
    // interface.proximityToolOut = true;
    if (digitalRead(PROXIMITY_TOOL_OUT_PIN))
      this->statusIndicators.proximityToolOut = true;
    else
      this->statusIndicators.proximityToolOut = false;
    this->intQueue->push(&proximityToolOutInterrupt); // Send to queue for serial debugging
  }

  void interruptShearButton(){
    // interface.shearButton = true;
    if (digitalRead(SHEAR_BUTTON_PIN))
      this->statusIndicators.shearButton = true;
    else
      this->statusIndicators.shearButton = false;
    this->intQueue->push(&shearButtonInterrupt); // Send to queue for serial debugging
  }

  void interruptProximityHeadLimit(){
    // I don't know what this proximity sensor stops.
    // The head has its own respective set of CW, CCW, IN, and OUT proximity sensors with solenoids
    // interface.proximityHeadLimit = true;
    if (digitalRead(PROXIMITY_HEAD_LIMIT_PIN))
      this->statusIndicators.proximityHeadLimit = true;
    else
      this->statusIndicators.proximityHeadLimit = false;
    this->intQueue->push(&proximityHeadLimitInterrupt); // Send to queue for serial debugging
  }

  void interruptProximityHeadCw(){
    // Turn off HEAD_CW solenoid
    // interface.proximityHeadCw = true;
    if (digitalRead(PROXIMITY_HEAD_CW_PIN))
      this->statusIndicators.proximityHeadCw = true;
    else
      this->statusIndicators.proximityHeadCw = false;
    this->intQueue->push(&proximityHeadCwInterrupt); // Send to queue for serial debugging
  }

  void interruptProximityHeadCcw(){
    // Turn off HEAD_CCW solenoid
    // interface.proximityHeadCcw = true;
    if (digitalRead(PROXIMITY_HEAD_CCW_PIN))
      this->statusIndicators.proximityHeadCcw = true;
    else
      this->statusIndicators.proximityHeadCcw = false;
    this->intQueue->push(&proximityHeadCcwInterrupt); // Send to queue for serial debugging
  }

  void interruptAutoButton(){
    // interface.autoButton = true;
    if (digitalRead(AUTO_BUTTON_PIN))
      this->statusIndicators.autoButton = true;
    else
      this->statusIndicators.autoButton = false;
    this->intQueue->push(&autoButtonInterrupt); // Send to queue for serial debugging
  }

  void interruptEstop(){
    // Stop everything!!
    // interface.eStop = true;
    // The main loop code should send a StopEvent to the HMI
    // There currently is an issue with Rev X1 of the Interface Board where ESTOP is momentarily pulled LOW at power up.
    // CM needs to debug this further or JG implements a mechanism to ignore the first interrupt upon power up.
    if (digitalRead(ESTOP_PIN)) {
      turnOffEverything();
      this->state = ESTOP;
      this->statusIndicators.eStop = true;
    } else {
      this->statusIndicators.eStop = false;
    }
    this->intQueue->push(&eStopInterrupt); // Send to queue for serial debugging
  }

  void interruptFuse(){
    // Stop everything!!
    // The fuse for the solenoids has blown
    // The main loop code should send a StopEvent to the HMI
    // We also need to implement something at startup of the machine to check if the fuse has blown and send a StopEvent to the HMI.
    if (digitalRead(FUSE_PIN))
      this->statusIndicators.fuse = true;
    else
      this->statusIndicators.fuse = false;
    this->intQueue->push(&fuseInterrupt); // Send to queue for serial debugging
  }

  // Helpers
  // Ideally we shouldn't have to poll (digitalRead()) each pin but we are in the development phase.
  void updateStatusIndicators() {
    this->statusIndicators.shearCut = digitalRead(SHEAR_CUT_PIN);
    this->statusIndicators.shearHome = digitalRead(SHEAR_HOME_PIN);
    this->statusIndicators.toolOut = digitalRead(TOOL_OUT_PIN);
    this->statusIndicators.toolIn = digitalRead(TOOL_IN_PIN);
    this->statusIndicators.feedForward = digitalRead(FEED_FORWARD_PIN);
    this->statusIndicators.feedReverse = digitalRead(FEED_REVERSE_PIN);
    this->statusIndicators.headCw = digitalRead(HEAD_CW_PIN);
    this->statusIndicators.headCcw = digitalRead(HEAD_CCW_PIN);
    this->statusIndicators.headOut = digitalRead(HEAD_OUT_PIN);
    this->statusIndicators.headIn = digitalRead(HEAD_IN_PIN);
    this->statusIndicators.encoderFeedSet = digitalRead(ENCODER_FEED_SET_PIN);
    this->statusIndicators.encoderFeedReset = digitalRead(ENCODER_FEED_RESET_PIN);
    this->statusIndicators.encoderBendSet = digitalRead(ENCODER_BEND_SET_PIN);
    this->statusIndicators.encoderBendRest = digitalRead(ENCODER_BEND_RESET_PIN);
    this->statusIndicators.proximityHeadOut = digitalRead(PROXIMITY_HEAD_OUT_PIN);
    this->statusIndicators.proximityHeadIn = digitalRead(PROXIMITY_HEAD_IN_PIN);
    this->statusIndicators.proximityShearHome = digitalRead(PROXIMITY_SHEAR_HOME_PIN);
    this->statusIndicators.proximityShearCut = digitalRead(PROXIMITY_SHEAR_CUT_PIN);
    this->statusIndicators.proximityToolIn = digitalRead(PROXIMITY_TOOL_IN_PIN);
    this->statusIndicators.proximityToolOut = digitalRead(PROXIMITY_TOOL_OUT_PIN);
    this->statusIndicators.shearButton = digitalRead(SHEAR_BUTTON_PIN);
    this->statusIndicators.proximityHeadLimit = digitalRead(PROXIMITY_HEAD_LIMIT_PIN);
    this->statusIndicators.proximityHeadCw = digitalRead(PROXIMITY_HEAD_CW_PIN);
    this->statusIndicators.proximityHeadCcw = digitalRead(PROXIMITY_HEAD_CCW_PIN);
    this->statusIndicators.autoButton = digitalRead(AUTO_BUTTON_PIN);
    this->statusIndicators.eStop = digitalRead(ESTOP_PIN);
    this->statusIndicators.fuse = digitalRead(FUSE_PIN);
    // Includes state, primary, and secondary actions
    // Also, ESTOP will trip FUSE, so check that
    // Fake values as these have not been implemented at the hardware level
    this->statusIndicators.twentyFourVrawBusVoltage = 23.998899;
    this->statusIndicators.twentyFourVrawBusCurrent = 1.50301;
    this->statusIndicators.auxTwentyFourVBusVoltage = 23.998899;
    this->statusIndicators.auxTwentyFourVBusCurrent = 1.50301;
    this->statusIndicators.twelveVBusVoltage = 11.998899;
    this->statusIndicators.twelveVBusCurrent = 1.50301;
    this->statusIndicators.fiveVBusVoltage = 4.998899;
    this->statusIndicators.fiveVBusCurrent = 1.50301;
    this->statusIndicators.threeVThreeVBusVoltage = 3.298899;
    this->statusIndicators.threeVThreeVBusCurrent = 1.50301;
    this->statusIndicators.fGndBusVoltage = 23.998899;
    this->statusIndicators.fGndBusCurrent = 1.50301;
  }
};


#endif //INTERFACE_H
