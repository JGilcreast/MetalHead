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

#ifndef UPDATE_STATUS_INDICATORS_H
#define UPDATE_STATUS_INDICATORS_H

void update_status_indicators() {
  hmi_server_msg.payload.hmi_client_msg.shear_cut = gpio_pin_get_dt(&shear_cut_spec);
  hmi_server_msg.payload.hmi_client_msg.shear_home = gpio_pin_get_dt(&shear_home_spec);
  hmi_server_msg.payload.hmi_client_msg.tool_out = gpio_pin_get_dt(&tool_out_spec);
  hmi_server_msg.payload.hmi_client_msg.tool_in = gpio_pin_get_dt(&tool_in_spec);
  hmi_server_msg.payload.hmi_client_msg.feed_forward = gpio_pin_get_dt(&feed_forward_spec);
  hmi_server_msg.payload.hmi_client_msg.feed_reverse = gpio_pin_get_dt(&feed_reverse_spec);
  hmi_server_msg.payload.hmi_client_msg.head_cw = gpio_pin_get_dt(&head_cw_spec);
  hmi_server_msg.payload.hmi_client_msg.head_ccw = gpio_pin_get_dt(&head_ccw_spec);
  hmi_server_msg.payload.hmi_client_msg.head_out = gpio_pin_get_dt(&head_out_spec);
  hmi_server_msg.payload.hmi_client_msg.head_in = gpio_pin_get_dt(&head_in_spec);
  hmi_server_msg.payload.hmi_client_msg.encoder_feed_set = gpio_pin_get_dt(&encoder_feed_set_spec);
  hmi_server_msg.payload.hmi_client_msg.encoder_feed_reset = gpio_pin_get_dt(&encoder_feed_reset_spec);
  hmi_server_msg.payload.hmi_client_msg.encoder_bend_set = gpio_pin_get_dt(&encoder_bend_set_spec);
  hmi_server_msg.payload.hmi_client_msg.encoder_bend_reset = gpio_pin_get_dt(&encoder_bend_reset_spec);
  hmi_server_msg.payload.hmi_client_msg.proximity_head_out = gpio_pin_get_dt(&proximity_head_out_spec);
  hmi_server_msg.payload.hmi_client_msg.proximity_head_in = gpio_pin_get_dt(&proximity_head_in_spec);
  hmi_server_msg.payload.hmi_client_msg.proximity_shear_home = gpio_pin_get_dt(&proximity_shear_home_spec);
  hmi_server_msg.payload.hmi_client_msg.proximity_shear_cut = gpio_pin_get_dt(&proximity_shear_cut_spec);
  hmi_server_msg.payload.hmi_client_msg.proximity_tool_in = gpio_pin_get_dt(&proximity_tool_in_spec);
  hmi_server_msg.payload.hmi_client_msg.proximity_tool_out = gpio_pin_get_dt(&proximity_tool_out_spec);
  hmi_server_msg.payload.hmi_client_msg.shear_button = gpio_pin_get_dt(&shear_button_spec);
  hmi_server_msg.payload.hmi_client_msg.proximity_head_limit = gpio_pin_get_dt(&proximity_head_limit_spec);
  hmi_server_msg.payload.hmi_client_msg.proximity_head_cw = gpio_pin_get_dt(&proximity_head_cw_spec);
  hmi_server_msg.payload.hmi_client_msg.proximity_head_ccw = gpio_pin_get_dt(&proximity_head_ccw_spec);
  hmi_server_msg.payload.hmi_client_msg.auto_button = gpio_pin_get_dt(&auto_button_spec);
  hmi_server_msg.payload.hmi_client_msg.e_stop = gpio_pin_get_dt(&estop_spec);
  hmi_server_msg.payload.hmi_client_msg.fuse = gpio_pin_get_dt(&fuse_spec);
}

#endif //UPDATE_STATUS_INDICATORS_H
