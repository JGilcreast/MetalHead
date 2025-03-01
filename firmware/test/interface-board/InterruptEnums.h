enum Interrupt {
  ENCODER_FEED_SET_INT,
  ENCODER_FEED_RESET_INT,
  ENCODER_BEND_SET_INT,
  ENCODER_BEND_RESET_INT,
  PROXIMITY_HEAD_OUT_INT,
  PROXIMITY_HEAD_IN_INT,
  PROXIMITY_SHEAR_HOME_INT,
  PROXIMITY_SHEAR_CUT_INT,
  PROXIMITY_TOOL_IN_INT,
  PROXIMITY_TOOL_OUT_INT,
  SHEAR_BUTTON_INT,
  PROXIMITY_HEAD_LIMIT_INT,
  PROXIMITY_HEAD_CW_INT,
  PROXIMITY_HEAD_CCW_INT,
  AUTO_BUTTON_INT,
  ESTOP_INT,
  NORMAL_OPERATION_INT,
  FUSE_INT
};

Interrupt encoderFeedSetInterrupt = Interrupt::ENCODER_FEED_SET_INT;
Interrupt encoderFeedResetInterrupt = Interrupt::ENCODER_FEED_RESET_INT;
Interrupt encoderBendSetInterrupt = Interrupt::ENCODER_BEND_SET_INT;
Interrupt encoderBendResetInterrupt = Interrupt::ENCODER_BEND_RESET_INT;
Interrupt proximityHeadOutInterrupt = Interrupt::PROXIMITY_HEAD_OUT_INT;
Interrupt proximityHeadInInterrupt = Interrupt::PROXIMITY_HEAD_IN_INT;
Interrupt proximityShearHomeInterrupt = Interrupt::PROXIMITY_SHEAR_HOME_INT;
Interrupt proximityShearCutInterrupt = Interrupt::PROXIMITY_SHEAR_CUT_INT;
Interrupt proximityToolInInterrupt = Interrupt::PROXIMITY_TOOL_IN_INT;
Interrupt proximityToolOutInterrupt = Interrupt::PROXIMITY_TOOL_OUT_INT;
Interrupt shearButtonInterrupt = Interrupt::SHEAR_BUTTON_INT;
Interrupt proximityHeadLimitInterrupt = Interrupt::PROXIMITY_HEAD_LIMIT_INT;
Interrupt proximityHeadCwInterrupt = Interrupt::PROXIMITY_HEAD_CW_INT;
Interrupt proximityHeadCcwInterrupt = Interrupt::PROXIMITY_HEAD_CCW_INT;
Interrupt autoButtonInterrupt = Interrupt::AUTO_BUTTON_INT;
Interrupt eStopInterrupt = Interrupt::ESTOP_INT;
Interrupt normalOperationInterrupt = Interrupt::NORMAL_OPERATION_INT;
Interrupt fuseInterrupt = Interrupt::FUSE_INT;