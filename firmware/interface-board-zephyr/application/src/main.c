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
#include <zephyr/net/net_if.h>
#include <zephyr/net/net_core.h>
#include <zephyr/net/net_context.h>
#include <zephyr/net/ethernet.h>
#include <zephyr/net/ethernet_mgmt.h>
#include <zephyr/net/net_mgmt.h>
#include <zephyr/net/socket.h>
#include <pb_encode.h>
#include <zephyr/drivers/eeprom.h>
#include <zephyr/random/random.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/posix/fcntl.h>

// Register logging interface
LOG_MODULE_REGISTER(MetalHead, LOG_LEVEL_DBG);

// Custom includes
#include "semaphores.h"
#include "threads.h"
#include "gpio_dt_specs.h"
#include "queues.h"
#include "gpio_pin_t.h"
#include "gpio_state_t.h"
#include "init_current_mon.h"
#include "async_tcp_server.h"
#include "update_status_indicators.h"
#include "gpio_int_handler.h"
#include "interface.h"
#include "init_gpio.h"
#include "init_eeprom.h"
#include "init_net.h"
#include "version.h"


void main(void)
{
  LOG_INF("MetalHead Interface Board Firmware v%d.%d.%d", MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION);
  LOG_INF("Build date: " __DATE__ " " __TIME__);
  LOG_INF("Copyright: Connor McMillan & John Gilcreast");
  LOG_INF("Project homepage: https://github.com/JGilcreast/MetalHead");

  // Check if led is ready
  if (!device_is_ready(led_builtin.port))
    LOG_ERR("Builtin LED is not ready!");

  // configure led gpio pin as output and set initial value as Logical Active
  if (gpio_pin_configure_dt(&led_builtin, GPIO_OUTPUT_INACTIVE) < 0)
    LOG_ERR("Failed to configure LED as GPIO_OUTPUT_INACTIVE!");

  init_eeprom();
  init_gpio();
  init_net();
  init_current_monitors();

  // Start the shape processing thread
  shape_processor_tid = k_thread_create(&shape_processor_thread_data,
    shape_processor_stack_area, K_THREAD_STACK_SIZEOF(shape_processor_stack_area),
    shape_process_thread, NULL, NULL, NULL, -5, 0, K_NO_WAIT);
  k_thread_name_set(shape_processor_tid, "shape_processor_thread");
}

