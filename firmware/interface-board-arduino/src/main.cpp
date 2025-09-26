#include "MetalHeadPins.h"
#include "InterruptEnums.h"
#include <at24c256.h>
#include <cppQueue.h>
#include <SPI.h>
#include <Ethernet.h>
#include <INA226.h>
#include "Interface.h"
#include <pb_arduino.h>
#include "Settings.h"
#include "Counters.h"

// Global objects and variables that ISRs and loop can access
cppQueue q(sizeof(Interrupt), 512, FIFO, true);
Interface interface(&q);
// Networking
// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(10, 1, 1, 1);
EthernetServer server(ethernetServerPort);

// Peripherals
AT24C256 eprom(AT24C_ADDRESS_0);
//INA226 FGND(0x40); // I'm having trouble with this! (at the hardware level?!?)

// In the event that we are sent data through the second I2C, we will be interrupted and the following ISR
// will execute. Be brief and quick in here.
void hmiI2cReceive(int howMany) {
  Serial.print("hmiI2cReceive: howMany = ");
  Serial.println(howMany);
}

void setup() {
  // Setup serial to print to the console
  Serial.begin(115200);

  // HMI serial channels - These may become obsolete at the hardware level in future revisions to the interface board
  Serial1.begin(115200);
  Serial2.begin(115200);

  // EEPROM setup
  Wire.begin();

  // Start communication with the power monitors
  // It's not working at the moment :( (see above)
  // if (!FGND.begin()) {Serial.println("FGND.begin() failed!");}

  // HMI I2C channel - This may become obsolete at the hardware level in future revisions to the interface board
  Wire1.begin();
  Wire1.onReceive(hmiI2cReceive); // Hook the ISR

  // Define the mode of each pin
  // Ouputs
  pinMode(SHEAR_CUT_PIN, OUTPUT);
  pinMode(SHEAR_HOME_PIN, OUTPUT);
  pinMode(TOOL_OUT_PIN, OUTPUT);
  pinMode(TOOL_IN_PIN, OUTPUT);
  pinMode(FEED_FORWARD_PIN, OUTPUT);
  pinMode(FEED_REVERSE_PIN, OUTPUT);
  pinMode(HEAD_CW_PIN, OUTPUT);
  pinMode(HEAD_CCW_PIN, OUTPUT);
  pinMode(HEAD_OUT_PIN, OUTPUT);
  pinMode(HEAD_IN_PIN, OUTPUT);
  // Inputs
  pinMode(ENCODER_FEED_SET_PIN, INPUT);
  pinMode(ENCODER_FEED_RESET_PIN, INPUT);
  pinMode(ENCODER_BEND_SET_PIN, INPUT);
  pinMode(ENCODER_BEND_RESET_PIN, INPUT);
  pinMode(PROXIMITY_HEAD_OUT_PIN, INPUT);
  pinMode(PROXIMITY_HEAD_IN_PIN, INPUT);
  pinMode(PROXIMITY_SHEAR_HOME_PIN, INPUT);
  pinMode(PROXIMITY_SHEAR_CUT_PIN, INPUT);
  pinMode(PROXIMITY_TOOL_IN_PIN, INPUT);
  pinMode(PROXIMITY_TOOL_OUT_PIN, INPUT);
  pinMode(SHEAR_BUTTON_PIN, INPUT);
  pinMode(PROXIMITY_HEAD_LIMIT_PIN, INPUT);
  pinMode(PROXIMITY_HEAD_CW_PIN, INPUT);
  pinMode(PROXIMITY_HEAD_CCW_PIN, INPUT);
  pinMode(AUTO_BUTTON_PIN, INPUT);
  pinMode(ESTOP_PIN, INPUT);
  pinMode(FUSE_PIN, INPUT);

  // Turn off all outputs by default
  digitalWrite(SHEAR_CUT_PIN, LOW);
  digitalWrite(SHEAR_HOME_PIN, LOW);
  digitalWrite(TOOL_OUT_PIN, LOW);
  digitalWrite(TOOL_IN_PIN, LOW);
  digitalWrite(FEED_FORWARD_PIN, LOW);
  digitalWrite(FEED_REVERSE_PIN, LOW);
  digitalWrite(HEAD_CW_PIN, LOW);
  digitalWrite(HEAD_CCW_PIN, LOW);
  digitalWrite(HEAD_OUT_PIN, LOW);
  digitalWrite(HEAD_IN_PIN, LOW);

  // Setup interrupts for inputs at the rising edge
  attachInterrupt(digitalPinToInterrupt(ENCODER_FEED_SET_PIN), []() { interface.interruptEncoderFeedSet(); }, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_FEED_RESET_PIN), [](){ interface.interruptEncoderFeedReset(); }, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_BEND_SET_PIN), [](){ interface.interruptEncoderBendSet(); }, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_BEND_RESET_PIN), [](){ interface.interruptEncoderBendReset(); }, RISING);

  // We need to know when the state of these sensors at all times as they go from LOW <--> HIGH. Monitor for changes to their state.
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_HEAD_OUT_PIN), [](){ interface.interruptProximityHeadOut(); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_HEAD_IN_PIN), [](){ interface.interruptProximityHeadIn(); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_SHEAR_HOME_PIN), [](){ interface.interruptProximityShearHome(); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_SHEAR_CUT_PIN), [](){ interface.interruptProximityShearCut(); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_TOOL_IN_PIN), [](){ interface.interruptProximityToolIn(); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_TOOL_OUT_PIN), [](){ interface.interruptProximityToolOut(); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SHEAR_BUTTON_PIN), [](){ interface.interruptShearButton(); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_HEAD_LIMIT_PIN), [](){ interface.interruptProximityHeadLimit(); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_HEAD_CW_PIN), [](){ interface.interruptProximityHeadCw(); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PROXIMITY_HEAD_CCW_PIN), [](){ interface.interruptProximityHeadCcw(); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(AUTO_BUTTON_PIN), [](){ interface.interruptAutoButton(); }, CHANGE);

  // When ESTOP is HIGH, ESTOP button is in the out most position (normal operation).
  // When ESTOP is LOW, ESTOP button is depressed (emergency stop)
  // When FUSE is HIGH, FUSE is not blown (normal operation)
  // When FUSE is LOW, FUSE is blown (alert HMI so operator can diagnose)
  // I might change the above logic by adding additional inverters at the hardware level on future revisions.
  attachInterrupt(digitalPinToInterrupt(FUSE_PIN), [](){ interface.interruptFuse(); }, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ESTOP_PIN), [](){ interface.interruptEstop(); }, CHANGE);

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to configure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  } else {
    Serial.print("DHCP assigned IP: ");
    Serial.println(Ethernet.localIP());
  }
  server.begin();
}

void loop() {
  // Process recipes, sensor inputs, output solenoids
  // interface.loop();

  interface.updateStatusIndicators(); // Usually we don't have to call this, but we are in the development phase.

  // Communications Sections
  // The communications stack is still very much in the experimental stage. We will have to come up with a nifty way
  // of sending all types of data structures to the HMI and have it be able to deserialize it accordingly while also
  // being able to receive and process data structures from the HMI (EthernetUDP class???)
  // The second half of the code below is mostly boilerplate code.
  // Protocol buffers
  uint8_t buffer[StatusIndicators_size]; // Somewhere to store our ANSI-C style data structures encoded in bytes
  // Constructs an output stream for writing into a memory buffer.
  pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
  // Convert our StatusIndicators into an ANSI-C style data structure storing into our byte array buffer
  pb_encode(&stream, StatusIndicators_fields, &interface.statusIndicators);
  // Mostly boilerplate code from examples
  EthernetClient client = server.available(); // returns first client which has data to read or a 'false' client
  if (client) {
    // client is true only if it is connected and has data to read
    String s = client.readStringUntil('\n'); // read the message incoming from one of the clients
    s.trim(); // trim eventual \r
    receivedMsgs++;
    Serial.print("Message #");
    Serial.print(receivedMsgs);
    Serial.print(" Received: ");
    Serial.println(s);
    // Send interface.statusIndicators in a one-shot method to the HMI
    client.write(buffer, sizeof(buffer));
    // Close the connection to the HMI
    client.stop();
    }

  // Debugging Section
  // Process debug interrupt queue and print to serial
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
    if (interrupt == Interrupt::FUSE_INT)
      Serial.println("FUSE");
    interruptCount++;
  }

}

