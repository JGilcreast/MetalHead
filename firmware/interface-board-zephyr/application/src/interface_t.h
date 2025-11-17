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

#ifndef INTERFACE_T_H
#define INTERFACE_T_H

struct interface_t {
  enum state_t state; // Default state at startup
  enum primary_action_t primary_action; // Shear
  enum secondary_action_t secondary_action; // But before we can shear, retract the shear
  struct shape_t shape; // Current shape being processed
  // These two are used to hold the count before pausing
  // so we can detect potential operator tampering before continuing
  int previous_encoder_feed_count;
  int previous_encoder_bend_count;
};

#endif //INTERFACE_T_H
