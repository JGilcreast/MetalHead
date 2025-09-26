// MetalHead - Opensource Firmware & Software For The 85V Automatic Stirrup Bender
// Copyright (C) 2025 Connor McMillan (connor@mcmillan.website)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef INT_LABEL_T_H
#define INT_LABEL_T_H
enum interrupt_label_t {
  ENCODER_FEED_SET,
  ENCODER_FEED_RESET,
  ENCODER_BEND_SET,
  ENCODER_BEND_RESET,
  PROXIMITY_HEAD_OUT,
  PROXIMITY_HEAD_IN,
  PROXIMITY_SHEAR_HOME,
  PROXIMITY_SHEAR_CUT,
  PROXIMITY_TOOL_IN,
  PROXIMITY_TOOL_OUT,
  SHEAR_BUTTON,
  PROXIMITY_HEAD_LIMIT,
  PROXIMITY_HEAD_CW,
  PROXIMITY_HEAD_CCW,
  AUTO_BUTTON,
  ESTOP,
  FUSE,
  RAW24V,
  AUX24V,
};
#endif //INT_LABEL_T_H
