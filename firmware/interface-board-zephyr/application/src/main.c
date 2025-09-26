// MetalHead - Opensource Firmware & Software For The 85V Automatic Stirrup Bender
// Copyright (C) 2024-2025 John Gilcreast (johngilcreast@gmail.com)
// Copyright (C) 2024-2025 Connor McMillan (connor@mcmillan.website)
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

#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <stdio.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/hash_map.h>

// Register logging interface
LOG_MODULE_REGISTER(MetalHead, LOG_LEVEL_DBG);

// Custom includes

#include "gpio_dt_specs.h"
#include "queues.h"
#include "gpio_pin_t.h"
#include "gpio_state_t.h"
#include "gpio_int_handler.h"
#include "init_gpio.h"
#include "init_eeprom.h"
#include "init_net.h"
#include "init_current_mon.h"
#include "interface.h"
#include "threads.h"
#include "version.h"


int main(void)
{
  LOG_INF("MetalHead Interface Board Firmware v%d.%d.%d", MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION);
  LOG_INF("Build date: " __DATE__ " " __TIME__);
  LOG_INF("Copyright: Connor McMillan & John Gilcreast");
  LOG_INF("Project homepage: https://github.com/JGilcreast/MetalHead");

  // check if led is ready
  if (!device_is_ready(led_builtin.port))
    return 1;

  // configure led gpio pin as output and set initial value as Logical Active
  if (gpio_pin_configure_dt(&led_builtin, GPIO_OUTPUT_INACTIVE) < 0)
    return 1;

  init_eeprom();
  init_gpio();
  init_net();
  init_current_monitors();

  return 0;
}

