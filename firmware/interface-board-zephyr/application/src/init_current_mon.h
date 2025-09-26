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

#ifndef INIT_CURRENT_MON_H
#define INIT_CURRENT_MON_H
#include <zephyr/drivers/sensor.h>

const struct device *fused_gnd_curr_mon = DEVICE_DT_GET(DT_NODELABEL(ina226_0));

struct sensor_value fused_gnd_current, fused_gnd_voltage, fused_gnd_power;

void init_current_monitors() {
  int err = 0;
  if (!device_is_ready(fused_gnd_curr_mon))
    LOG_ERR("FUSED_GND INA226 is not ready!");
  else {
    err = sensor_channel_get(fused_gnd_curr_mon, SENSOR_CHAN_VOLTAGE, &fused_gnd_voltage);
    err = sensor_channel_get(fused_gnd_curr_mon, SENSOR_CHAN_CURRENT, &fused_gnd_current);
    err = sensor_channel_get(fused_gnd_curr_mon, SENSOR_CHAN_POWER, &fused_gnd_power);
    if (err)
      LOG_ERR("FUSED_GND current monitor fetch error (%d)", err);
    else {
      LOG_INF("FUSED_GND Current: %.2f V", sensor_value_to_double(&fused_gnd_voltage));
      LOG_INF("FUSED_GND Voltage: %.3f A", sensor_value_to_double(&fused_gnd_current));
      LOG_INF("FUSED_GND Power: %.3f W", sensor_value_to_double(&fused_gnd_power));
    }
  }


}

#endif //INIT_CURRENT_MON_H
