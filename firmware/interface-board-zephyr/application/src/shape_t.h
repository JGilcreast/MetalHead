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

#ifndef SHAPE_T_H
#define SHAPE_T_H
#include "angle_t.h"
#include "bar_size_t.h"

struct shape_t {
  // A shape can have one or more angles
  struct angle_t *angle;
  // Quantity if the same shape
  uint8_t quantity;
  // System-wide modifier, programmed from settings
  uint8_t feed_scale;
  // System adjustment for different sizes of rebar (4/8” vs 5/8”, etc)
  enum bar_size_t bar_size_modifier;
  // Bend compensation for different center pin sizes
  uint8_t center_pin_modifier; // Do we need more than a representation from 0 - 255 (uint8_t)
  // Bend compensation for different sizes of rebar
  uint8_t bar_bend_modifier; // Do we need more than a representation from 0 - 255 (uint8_t)
};

#endif //SHAPE_T_H
