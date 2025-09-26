// MetalHead - Opensource Firmware & Software For The 85V Automatic Stirrup Bender
// Copyright (C) 2024-2025 John Gilcreast (johngilcreast@gmail.com)
// Copyright (C) 2025 Connor McMillan (connor@mcmillan.website)
//
// interface program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// interface program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with interface program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef ANGLE_T_H
#define ANGLE_T_H
#include "bend_direction_t.h"
struct angle_t {
  // Another angle can proceed after this angle
  struct angle_t* next;
  // An angle has a preceding length before the rebar is bent
  uint16_t length;
  // An angle must be bent
  uint16_t degrees; // 0 - 360 can fit into an uint16_t
  // Is it CW or CCW?
  enum bend_direction_t direction;
  // Compensation programmed per line
  uint8_t length_compensation; // Do we need more than a representation from 0 - 255 (uint8_t)?
  // Bend compensation programmed per line
  uint8_t bend_compensation; // // Do we need more than a representation from 0 - 255 (uint8_t)
};

#endif //ANGLE_T_H
