//
// Created by Connor on 8/25/2025.
//

#ifndef STATUSINDICATORS_H
#define STATUSINDICATORS_H

struct StatusIndicators{
  volatile bool SHEAR_CUT;
  volatile bool SHEAR_HOME;
  volatile bool TOOL_OUT;
  volatile bool TOOL_IN;
  volatile bool FEED_FORWARD;
  volatile bool FEED_REVERSE;
  volatile bool HEAD_CW;
  volatile bool HEAD_CCW;
  volatile bool HEAD_OUT;
  volatile bool HEAD_IN;

  volatile bool ENCODER_FEED_SET;
  volatile bool ENCODER_FEED_RESET;
  volatile bool ENCODER_BEND_SET;
  volatile bool ENCODER_BEND_RESET;
  volatile bool PROXIMITY_HEAD_OUT;
  volatile bool PROXIMITY_HEAD_IN;
  volatile bool PROXIMITY_SHEAR_HOME;
  volatile bool PROXIMITY_SHEAR_CUT;
  volatile bool PROXIMITY_TOOL_IN;
  volatile bool PROXIMITY_TOOL_OUT;
  volatile bool SHEAR_BUTTON;
  volatile bool PROXIMITY_HEAD_LIMIT;
  volatile bool PROXIMITY_HEAD_CW;
  volatile bool PROXIMITY_HEAD_CCW;
  volatile bool AUTO_BUTTON;
  volatile bool ESTOP;
  volatile bool FUSE;

  volatile uint8_t encoderFeedCount;
  volatile uint8_t encoderBendCount;

  volatile float TWENTY_FOUR_VRAW_BUS_VOLTAGE;
  volatile float TWENTY_FOUR_VRAW_BUS_CURRENT;
  volatile float AUX_TWENTY_FOUR_V_BUS_VOLTAGE;
  volatile float AUX_TWENTY_FOUR_V_BUS_CURRENT;
  volatile float TWELVE_V_BUS_VOLTAGE;
  volatile float TWELVE_V_BUS_CURRENT;
  volatile float FIVE_V_BUS_VOLTAGE;
  volatile float FIVE_V_BUS_CURRENT;
  volatile float THREE_V_THREE_V_BUS_VOLTAGE;
  volatile float THREE_V_THREE_V_BUS_CURRENT;
  volatile float FGND_BUS_VOLTAGE;
  volatile float FGND_BUS_CURRENT;

};

#endif //STATUSINDICATORS_H
