// MetalHead - Opensource Firmware & Software For The 85V Automatic Stirrup Bender
// Copyright (C) 2024-2025 John Gilcreast (johngilcreast@gmail.com)
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

#ifndef PRIMARY_ACTION_T_H
#define PRIMARY_ACTION_T_H
enum primary_action_t {
  PRIMARY_ACTION_SHEAR,
  PRIMARY_ACTION_TOOL_OUT,
  PRIMARY_ACTION_TOOL_IN,
  PRIMARY_ACTION_FEED_FORWARD,
  PRIMARY_ACTION_FEED_REVERSE,
  PRIMARY_ACTION_HEAD_CW,
  PRIMARY_ACTION_HEAD_CCW,
  PRIMARY_ACTION_HEAD_OUT,
  PRIMARY_ACTION_HEAD_IN,
  PRIMARY_ACTION_NONE,
};
#endif //PRIMARY_ACTION_T_H
