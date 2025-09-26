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

#ifndef GPIO_DT_SPECS_H
#define GPIO_DT_SPECS_H

// Solenoids
static const struct gpio_dt_spec shear_cut_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(shear_cut), gpios, {0});
static const struct gpio_dt_spec shear_home_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(shear_home), gpios, {0});
static const struct gpio_dt_spec tool_out_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(tool_out), gpios, {0});
static const struct gpio_dt_spec tool_in_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(tool_in), gpios, {0});
static const struct gpio_dt_spec feed_forward_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(feed_forward), gpios, {0});
static const struct gpio_dt_spec feed_reverse_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(feed_reverse), gpios, {0});
static const struct gpio_dt_spec head_cw_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(head_cw), gpios, {0});
static const struct gpio_dt_spec head_ccw_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(head_ccw), gpios, {0});
static const struct gpio_dt_spec head_out_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(head_out), gpios, {0});
static const struct gpio_dt_spec head_in_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(head_in), gpios, {0});


// Encoders
static const struct gpio_dt_spec encoder_feed_set_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(encoder_feed_set), gpios, {0});
static const struct gpio_dt_spec encoder_feed_reset_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(encoder_feed_reset), gpios, {0});
static const struct gpio_dt_spec encoder_bend_set_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(encoder_bend_set), gpios, {0});
static const struct gpio_dt_spec encoder_bend_reset_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(encoder_bend_reset), gpios, {0});


// Proximity Sensors
static const struct gpio_dt_spec proximity_head_out_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(proximity_head_out), gpios, {0});
static const struct gpio_dt_spec proximity_head_in_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(proximity_head_in), gpios, {0});
static const struct gpio_dt_spec proximity_shear_home_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(proximity_shear_home), gpios, {0});
static const struct gpio_dt_spec proximity_shear_cut_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(proximity_shear_cut), gpios, {0});
static const struct gpio_dt_spec proximity_tool_in_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(proximity_tool_in), gpios, {0});
static const struct gpio_dt_spec proximity_tool_out_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(proximity_tool_out), gpios, {0});
static const struct gpio_dt_spec proximity_head_limit_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(proximity_head_limit), gpios, {0});
static const struct gpio_dt_spec proximity_head_cw_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(proximity_head_cw), gpios, {0});
static const struct gpio_dt_spec proximity_head_ccw_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(proximity_head_ccw), gpios, {0});

// Buttons
static const struct gpio_dt_spec shear_button_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(shear_button), gpios, {0});
static const struct gpio_dt_spec auto_button_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(auto_button), gpios, {0});

// Auxillary
static const struct gpio_dt_spec estop_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(estop), gpios, {0});
static const struct gpio_dt_spec fuse_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(fuse), gpios, {0});

// Power
static const struct gpio_dt_spec vraw24_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(vraw24), gpios, {0});
static const struct gpio_dt_spec aux24v_spec =
  GPIO_DT_SPEC_GET_OR(DT_NODELABEL(aux24v), gpios, {0});

#endif //GPIO_DT_SPECS_H
