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

#ifndef GPIO_PIN_T_H
#define GPIO_PIN_T_H
#include "int_label_t.h"
struct gpio_pin_t {
  struct gpio_callback cb;
  const char *label;
  enum interrupt_label_t label_enum;
  struct gpio_dt_spec spec;
  bool *status_indicator_pin;
};
#endif //GPIO_PIN_T_H
