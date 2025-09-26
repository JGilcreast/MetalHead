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

#ifndef SECONDARY_ACTION_T_H
#define SECONDARY_ACTION_T_H
enum secondary_action_t {
  SECONDARY_ACTION_SHEAR_RETRACT,
  SECONDARY_ACTION_TOOL_RETRACT,
  SECONDARY_ACTION_HEAD_RETRACT,
  SECONDARY_ACTION_NONE,
};
#endif //SECONDARY_ACTION_T_H
