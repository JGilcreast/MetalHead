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

#define SENSOR_ATTR_INA3221_SELECTED_CHANNEL (SENSOR_ATTR_PRIV_START+1)
#include "async_tcp_server.h"

const struct device *fused_gnd_curr_mon = DEVICE_DT_GET(DT_NODELABEL(ina226_0));
const struct device *tri_vbus_curr_mon = DEVICE_DT_GET(DT_NODELABEL(ina3221_0));

struct sensor_value fused_gnd_current, fused_gnd_voltage, fused_gnd_power;
struct sensor_value twelve_v_current, twelve_v_voltage,
                    five_v_current, five_v_voltage,
                    three_v_three_current, three_v_three_voltage;

void update_3v3() {
  int err = 0;
  struct sensor_value val;

  // Switch to channel 1/3.3V
  val.val1 = 1;
  err = sensor_attr_set(tri_vbus_curr_mon, SENSOR_CHAN_ALL, SENSOR_ATTR_INA3221_SELECTED_CHANNEL, &val);
  if (err < 0)
    LOG_ERR("INA3221 3.3V sensor_attr_set error: %d", err);
  // INA3221 to fetch and average all channels
  err = sensor_sample_fetch_chan(tri_vbus_curr_mon, SENSOR_CHAN_ALL);
  if (err < 0)
    LOG_ERR("INA3221 3.3V sensor_sample_fetch error: %d", err);
  // Get voltage
  err = sensor_channel_get(tri_vbus_curr_mon, SENSOR_CHAN_VOLTAGE, &three_v_three_voltage);
  if (err < 0)
    LOG_ERR("INA3221 3.3V SENSOR_CHAN_VOLTAGE error: %d", err);
  else
    hmi_server_msg.payload.hmi_client_msg.three_v_three_v_bus_voltage = sensor_value_to_float(&three_v_three_voltage);
  // Get current
  err = sensor_channel_get(tri_vbus_curr_mon, SENSOR_CHAN_CURRENT, &three_v_three_current);
  if (err < 0)
    LOG_ERR("INA3221 3.3V SENSOR_CHAN_CURRENT error: %d", err);
  else
    hmi_server_msg.payload.hmi_client_msg.three_v_three_v_bus_current = sensor_value_to_float(&three_v_three_current);
}

void update_5v() {
  int err = 0;
  struct sensor_value val;

  // Switch to channel 2/5V
  val.val1 = 2;
  err = sensor_attr_set(tri_vbus_curr_mon, SENSOR_CHAN_ALL, SENSOR_ATTR_INA3221_SELECTED_CHANNEL, &val);
  if (err < 0)
    LOG_ERR("INA3221 5V sensor_attr_set error: %d", err);
  // INA3221 to fetch and average all channels
  err = sensor_sample_fetch_chan(tri_vbus_curr_mon, SENSOR_CHAN_ALL);
  if (err < 0)
    LOG_ERR("INA3221 5V sensor_sample_fetch error: %d", err);
  // Get voltage
  err = sensor_channel_get(tri_vbus_curr_mon, SENSOR_CHAN_VOLTAGE, &five_v_voltage);
  if (err < 0)
    LOG_ERR("INA3221 5V SENSOR_CHAN_VOLTAGE error: %d", err);
  else
    hmi_server_msg.payload.hmi_client_msg.five_v_bus_voltage = sensor_value_to_float(&five_v_voltage);
  // Get current
  err = sensor_channel_get(tri_vbus_curr_mon, SENSOR_CHAN_CURRENT, &five_v_current);
  if (err < 0)
    LOG_ERR("INA3221 5V SENSOR_CHAN_CURRENT error: %d", err);
  else
    hmi_server_msg.payload.hmi_client_msg.five_v_bus_current = sensor_value_to_float(&five_v_current);
}

void update_12v() {
  int err = 0;
  struct sensor_value val;

  // Switch to channel 3/12V
  val.val1 = 3;
  err = sensor_attr_set(tri_vbus_curr_mon, SENSOR_CHAN_ALL, SENSOR_ATTR_INA3221_SELECTED_CHANNEL, &val);
  if (err < 0)
    LOG_ERR("INA3221 12V sensor_attr_set error: %d", err);
  // INA3221 to fetch and average all channels
  err = sensor_sample_fetch_chan(tri_vbus_curr_mon, SENSOR_CHAN_ALL);
  if (err < 0)
    LOG_ERR("INA3221 12V sensor_sample_fetch error: %d", err);
  // Get voltage
  err = sensor_channel_get(tri_vbus_curr_mon, SENSOR_CHAN_VOLTAGE, &twelve_v_voltage);
  if (err < 0)
    LOG_ERR("INA3221 12V SENSOR_CHAN_VOLTAGE error: %d", err);
  else
    hmi_server_msg.payload.hmi_client_msg.twelve_v_bus_voltage = sensor_value_to_float(&twelve_v_voltage);
  // Get current
  err = sensor_channel_get(tri_vbus_curr_mon, SENSOR_CHAN_CURRENT, &twelve_v_current);
  if (err < 0)
    LOG_ERR("INA3221 12V SENSOR_CHAN_CURRENT error: %d", err);
  else
    hmi_server_msg.payload.hmi_client_msg.twelve_v_bus_current = sensor_value_to_float(&twelve_v_current);
}

void update_fgnd() {
  int err = 0;

  err = sensor_sample_fetch_chan(fused_gnd_curr_mon, SENSOR_CHAN_ALL);
  if (err < 0)
    LOG_ERR("INA226 FUSED_GND sensor_sample_fetch error: %d", err);
  err = sensor_channel_get(fused_gnd_curr_mon, SENSOR_CHAN_VOLTAGE, &fused_gnd_voltage);
  if (err < 0)
    LOG_ERR("INA226 FUSED_GND SENSOR_CHAN_VOLTAGE error: %d", err);
  else
    hmi_server_msg.payload.hmi_client_msg.f_gnd_bus_voltage = sensor_value_to_float(&fused_gnd_voltage);
  err = sensor_channel_get(fused_gnd_curr_mon, SENSOR_CHAN_CURRENT, &fused_gnd_current);
  if (err < 0)
    LOG_ERR("INA226 FUSED_GND SENSOR_CHAN_CURRENT error: %d", err);
  else
    hmi_server_msg.payload.hmi_client_msg.f_gnd_bus_current = sensor_value_to_float(&fused_gnd_current);
}

void current_monitor_thread() {
  while (1) {
    update_3v3();
    update_5v();
    update_12v();
    update_fgnd();
    k_sleep(K_MSEC(500));
  }
}

void init_current_monitors() {
  int err = 0;
  struct sensor_value val;

  if (!device_is_ready(fused_gnd_curr_mon))
    LOG_ERR("FUSED_GND INA226 is not ready!");
  else {
    update_fgnd();
    LOG_INF("FUSED_GND Volts: %.3f V", sensor_value_to_double(&fused_gnd_voltage));
    LOG_INF("FUSED_GND Current: %.3f A", sensor_value_to_double(&fused_gnd_current));
    LOG_INF("FUSED_GND Power: %.3f W", sensor_value_to_double(&fused_gnd_power));
  }
  if (!device_is_ready(tri_vbus_curr_mon))
    LOG_ERR("INA3221 is not ready!");
  else {
    update_3v3();
    update_5v();
    update_12v();
    LOG_INF("3.3V Volts: %.3f V", sensor_value_to_double(&three_v_three_voltage));
    LOG_INF("3.3V Current: %.3f A", sensor_value_to_double(&three_v_three_current));
    LOG_INF("5V Volts: %.3f V", sensor_value_to_double(&five_v_voltage));
    LOG_INF("5V Current: %.3f A", sensor_value_to_double(&five_v_current));
    LOG_INF("12V Volts: %.3f V", sensor_value_to_double(&twelve_v_voltage));
    LOG_INF("12V Current: %.3f A", sensor_value_to_double(&twelve_v_current));
  }

  // Start the current monitoring thread
  current_monitor_tid = k_thread_create(&current_monitor_thread_data,
    current_monitor_stack_area, K_THREAD_STACK_SIZEOF(current_monitor_stack_area),
    (k_thread_entry_t)current_monitor_thread, NULL, NULL, NULL,
    K_PRIO_PREEMPT(5),0, K_NO_WAIT);
  k_thread_name_set(current_monitor_tid, "current_monitoring_thread");
}
#endif //INIT_CURRENT_MON_H
