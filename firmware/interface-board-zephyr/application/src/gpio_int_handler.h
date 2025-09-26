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

#ifndef GPIO_INT_HANDLER_H
#define GPIO_INT_HANDLER_H


// To visually keep track of the number of interrupts
uint32_t interrupts = 1;

static struct gpio_dt_spec led_builtin = GPIO_DT_SPEC_GET(DT_NODELABEL(yellow_led), gpios);
/**
 * @brief interrupt handler for gpio
 *
 * @param port pointer to gpio
 * @param cb pointer to owner gpio_callback
 * @param pins mask of pins that trigger this interrupt
 * @return gpio_callback_handler_t
 */
void gpio_interrupt_handler(struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins)
{
  // Get pin from pin bit array
  gpio_pin_t pin_num = __builtin_ctz(pins);
  // Get label from gpio_pin_t
  struct gpio_pin_t *pin = CONTAINER_OF(cb, struct gpio_pin_t, cb);
  // Output to serial console
  if (gpio_pin_get(port, pin_num)) {
    LOG_INF("Interrupt #%d: %s HIGH", interrupts, pin->label);
    // Dereference to assign high/low state
    *(pin->status_indicator_pin) = true;
  } else {
    LOG_INF("Interrupt #%d: %s LOW", interrupts, pin->label);
    // Dereference to assign high/low state
    *(pin->status_indicator_pin) = false;
  }

  // Wake up thread(s)
  // Maybe wake up the recipe processor thread?
  // This is if we implement it in a manner that will require it to be awakened to continue processing the recipe

  // Increment the counter
  interrupts++;

  // Toggle the LED for visual confirmation
  gpio_pin_toggle_dt(&led_builtin);
}

#endif //GPIO_INT_HANDLER_H
