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

#ifndef INIT_GPIO_H
#define INIT_GPIO_H

// Callbacks
static struct gpio_pin_t shear_cut_gpio;
static struct gpio_pin_t shear_home_gpio;
static struct gpio_pin_t tool_out_gpio;
static struct gpio_pin_t tool_in_gpio;
static struct gpio_pin_t feed_forward_gpio;
static struct gpio_pin_t feed_reverse_gpio;
static struct gpio_pin_t head_cw_gpio;
static struct gpio_pin_t head_ccw_gpio;
static struct gpio_pin_t head_out_gpio;
static struct gpio_pin_t head_in_gpio;
static struct gpio_pin_t encoder_feed_set_gpio;
static struct gpio_pin_t encoder_feed_reset_gpio;
static struct gpio_pin_t encoder_bend_set_gpio;
static struct gpio_pin_t encoder_bend_reset_gpio;
static struct gpio_pin_t proximity_head_out_gpio;
static struct gpio_pin_t proximity_head_in_gpio;
static struct gpio_pin_t proximity_shear_home_gpio;
static struct gpio_pin_t proximity_shear_cut_gpio;
static struct gpio_pin_t proximity_tool_in_gpio;
static struct gpio_pin_t proximity_tool_out_gpio;
static struct gpio_pin_t proximity_head_limit_gpio;
static struct gpio_pin_t proximity_head_cw_gpio;
static struct gpio_pin_t proximity_head_ccw_gpio;
static struct gpio_pin_t shear_button_gpio;
static struct gpio_pin_t auto_button_gpio;
static struct gpio_pin_t estop_gpio;
static struct gpio_pin_t fuse_gpio;
static struct gpio_pin_t vraw24_gpio;
static struct gpio_pin_t aux24v_gpio;


static void init_gpio(void) {
  int err;

  LOG_INF("Initializing GPIO pins...");

  // Outputs
  // Solenoid

  // SHEAR_CUT
  // Set the pin label from the devicetree
  shear_cut_gpio.label = DT_PROP(DT_NODELABEL(shear_cut), label);
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  shear_cut_gpio.status_indicator_pin = &status_indicators.shear_cut;
  // Check if the gpio is ready
  if (!device_is_ready(shear_cut_spec.port)) LOG_ERR("%s pin %d is not ready!",
    shear_cut_gpio.label, shear_cut_spec.pin);
  // Configure gpio as an output
  err = gpio_pin_configure_dt(&shear_cut_spec, GPIO_OUTPUT_INACTIVE);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, shear_cut_gpio.label, shear_cut_spec.pin);

  // SHEAR_HOME
  // Set the pin label from the devicetree
  shear_home_gpio.label = DT_PROP(DT_NODELABEL(shear_home), label);
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  shear_home_gpio.status_indicator_pin = &status_indicators.shear_home;
  // Check if the gpio is ready
  if (!device_is_ready(shear_home_spec.port)) LOG_ERR("%s pin %d is not ready!",
    shear_home_gpio.label, shear_home_spec.pin);
  // Configure gpio as an output
  err = gpio_pin_configure_dt(&shear_home_spec, GPIO_OUTPUT_INACTIVE);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, shear_home_gpio.label, shear_home_spec.pin);

  // TOOL_OUT
  // Set the pin label from the devicetree
  tool_out_gpio.label = DT_PROP(DT_NODELABEL(tool_out), label);
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  tool_out_gpio.status_indicator_pin = &status_indicators.tool_out;
  // Check if the gpio is ready
  if (!device_is_ready(tool_out_spec.port)) LOG_ERR("%s pin %d is not ready!",
    tool_out_gpio.label, tool_out_spec.pin);
  // Configure gpio as an output
  err = gpio_pin_configure_dt(&tool_out_spec, GPIO_OUTPUT_INACTIVE);
  if (err != 0) LOG_ERR("Error%d: failed to configure %s pin %d",
    err, tool_out_gpio.label, tool_out_spec.pin);

  // TOOL_IN
  // Set the pin label from the devicetree
  tool_in_gpio.label = DT_PROP(DT_NODELABEL(tool_in), label);
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  tool_in_gpio.status_indicator_pin = &status_indicators.tool_in;
  // Check if the gpio is ready
  if (!device_is_ready(tool_in_spec.port)) LOG_ERR("%s pin %d is not ready!",
    tool_in_gpio.label, tool_in_spec.pin);
  // Configure gpio as an output
  err = gpio_pin_configure_dt(&tool_in_spec, GPIO_OUTPUT_INACTIVE);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, tool_in_gpio.label, tool_in_spec.pin);

  // FEED_FORWARD
  // Set the pin label from the devicetree
  feed_forward_gpio.label = DT_PROP(DT_NODELABEL(feed_forward), label);
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  feed_forward_gpio.status_indicator_pin = &status_indicators.feed_forward;
  // Check if the gpio is ready
  if (!device_is_ready(feed_forward_spec.port)) LOG_ERR("%s pin %d is not ready!",
    feed_forward_gpio.label, feed_forward_spec.pin);
  // Configure gpio as an output
  err = gpio_pin_configure_dt(&feed_forward_spec, GPIO_OUTPUT_INACTIVE);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, feed_forward_gpio.label, feed_forward_spec.pin);

  // FEED_REVERSE
  // Set the pin label from the devicetree
  feed_reverse_gpio.label = DT_PROP(DT_NODELABEL(feed_reverse), label);
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  feed_reverse_gpio.status_indicator_pin = &status_indicators.feed_reverse;
  // Check if the gpio is ready
  if (!device_is_ready(feed_reverse_spec.port)) LOG_ERR("%s pin %d is not ready!",
    feed_reverse_gpio.label, feed_reverse_spec.pin);
  // Configure gpio as an output
  err = gpio_pin_configure_dt(&feed_reverse_spec, GPIO_OUTPUT_INACTIVE);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, feed_reverse_gpio.label, feed_reverse_spec.pin);

  // HEAD_CW
  // Set the pin label from the devicetree
  head_cw_gpio.label = DT_PROP(DT_NODELABEL(head_cw), label);
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  head_cw_gpio.status_indicator_pin = &status_indicators.head_cw;
  // Check if the gpio is ready
  if (!device_is_ready(head_cw_spec.port)) LOG_ERR("%s pin %d is not ready!",
    head_cw_gpio.label, head_cw_spec.pin);
  // Configure gpio as an output
  err = gpio_pin_configure_dt(&head_cw_spec, GPIO_OUTPUT_INACTIVE);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, head_cw_gpio.label, head_cw_spec.pin);

  // HEAD_CCW
  // Set the pin label from the devicetree
  head_ccw_gpio.label = DT_PROP(DT_NODELABEL(head_ccw), label);
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  head_ccw_gpio.status_indicator_pin = &status_indicators.head_ccw;
  // Check if the gpio is ready
  if (!device_is_ready(head_ccw_spec.port)) LOG_ERR("%s pin %d is not ready!",
    head_ccw_gpio.label, head_ccw_spec.pin);
  // Configure gpio as an output
  err = gpio_pin_configure_dt(&head_ccw_spec, GPIO_OUTPUT_INACTIVE);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, head_ccw_gpio.label, head_ccw_spec.pin);

  // HEAD_OUT
  // Set the pin label from the devicetree
  head_out_gpio.label = DT_PROP(DT_NODELABEL(head_out), label);
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  head_out_gpio.status_indicator_pin = &status_indicators.head_out;
  // Check if the gpio is ready
  if (!device_is_ready(head_out_spec.port)) LOG_ERR("%s pin %d is not ready!",
    head_out_gpio.label, head_out_spec.pin);
  // Configure gpio as an output
  err = gpio_pin_configure_dt(&head_out_spec, GPIO_OUTPUT_INACTIVE);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, head_out_gpio.label, head_out_spec.pin);

  // HEAD_IN
  // Set the pin label from the devicetree
  head_in_gpio.label = DT_PROP(DT_NODELABEL(head_in), label);
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  head_in_gpio.status_indicator_pin = &status_indicators.head_in;
  // Check if the gpio is ready
  if (!device_is_ready(head_in_spec.port)) LOG_ERR("%s pin %d is not ready!",
    head_in_gpio.label, head_in_spec.pin);
  // Configure gpio as an output
  err = gpio_pin_configure_dt(&head_in_spec, GPIO_OUTPUT_INACTIVE);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, head_in_gpio.label, head_in_spec.pin);

  // Inputs
  // ENCODER_FEED_SET
  // Set the pin label from the devicetree
  encoder_feed_set_gpio.label = DT_PROP(DT_NODELABEL(encoder_feed_set), label);
  encoder_feed_set_gpio.label_enum = ENCODER_FEED_SET;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  encoder_feed_set_gpio.status_indicator_pin = &status_indicators.encoder_feed_set;
  // Check if the gpio is ready
  if (!device_is_ready(encoder_feed_set_spec.port)) LOG_ERR("%s pin %d is not ready!",
    encoder_feed_set_gpio.label, encoder_feed_set_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&encoder_feed_set_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, encoder_feed_set_gpio.label, encoder_feed_set_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&encoder_feed_set_spec, GPIO_INT_EDGE_RISING);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, encoder_feed_set_gpio.label, encoder_feed_set_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&encoder_feed_set_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(encoder_feed_set_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(encoder_feed_set_spec.port, &encoder_feed_set_gpio.cb);

  // ENCODER_FEED_RESET
  // Set the pin label from the devicetree
  encoder_feed_reset_gpio.label = DT_PROP(DT_NODELABEL(encoder_feed_reset), label);
  encoder_feed_reset_gpio.label_enum = ENCODER_FEED_RESET;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  encoder_feed_reset_gpio.status_indicator_pin = &status_indicators.encoder_feed_reset;
  // Check if the gpio is ready
  if (!device_is_ready(encoder_feed_reset_spec.port)) LOG_ERR("%s pin %d is not ready!",
    encoder_feed_reset_gpio.label, encoder_feed_reset_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&encoder_feed_reset_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, encoder_feed_reset_gpio.label, encoder_feed_reset_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&encoder_feed_reset_spec, GPIO_INT_EDGE_RISING);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, encoder_feed_reset_gpio.label, encoder_feed_reset_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&encoder_feed_reset_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(encoder_feed_reset_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(encoder_feed_reset_spec.port, &encoder_feed_reset_gpio.cb);

  // ENCODER_BEND_SET
  // Set the pin label from the devicetree
  encoder_bend_set_gpio.label = DT_PROP(DT_NODELABEL(encoder_bend_set), label);
  encoder_bend_set_gpio.label_enum = ENCODER_BEND_SET;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  encoder_bend_set_gpio.status_indicator_pin = &status_indicators.encoder_bend_set;
  // Check if the gpio is ready
  if (!device_is_ready(encoder_bend_set_spec.port)) LOG_ERR("%s pin %d is not ready!",
    encoder_bend_set_gpio.label, encoder_bend_set_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&encoder_bend_set_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, encoder_bend_set_gpio.label, encoder_bend_set_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&encoder_bend_set_spec, GPIO_INT_EDGE_RISING);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, encoder_bend_set_gpio.label, encoder_bend_set_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&encoder_bend_set_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(encoder_bend_set_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(encoder_bend_set_spec.port, &encoder_bend_set_gpio.cb);

  // ENCODER_BEND_RESET
  // Set the pin label from the devicetree
  encoder_bend_reset_gpio.label = DT_PROP(DT_NODELABEL(encoder_bend_reset), label);
  encoder_bend_reset_gpio.label_enum = ENCODER_BEND_RESET;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  encoder_bend_reset_gpio.status_indicator_pin = &status_indicators.encoder_bend_reset;
  // Check if the gpio is ready
  if (!device_is_ready(encoder_bend_reset_spec.port)) LOG_ERR("%s pin %d is not ready!",
    encoder_bend_reset_gpio.label, encoder_bend_reset_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&encoder_bend_reset_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, encoder_bend_reset_gpio.label, encoder_bend_reset_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&encoder_bend_reset_spec, GPIO_INT_EDGE_RISING);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, encoder_bend_reset_gpio.label, encoder_bend_reset_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&encoder_bend_reset_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(encoder_bend_reset_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(encoder_bend_reset_spec.port, &encoder_bend_reset_gpio.cb);

  // PROXIMITY_HEAD_OUT
  // Set the pin label from the devicetree
  proximity_head_out_gpio.label = DT_PROP(DT_NODELABEL(proximity_head_out), label);
  proximity_head_out_gpio.label_enum = PROXIMITY_HEAD_OUT;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  proximity_head_out_gpio.status_indicator_pin = &status_indicators.proximity_head_out;
  // Check if the gpio is ready
  if (!device_is_ready(proximity_head_out_spec.port)) LOG_ERR("%s pin %d is not ready!",
    proximity_head_out_gpio.label, proximity_head_out_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&proximity_head_out_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, proximity_head_out_gpio.label, proximity_head_out_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&proximity_head_out_spec, GPIO_INT_EDGE_BOTH);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, proximity_head_out_gpio.label, proximity_head_out_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&proximity_head_out_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(proximity_head_out_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(proximity_head_out_spec.port, &proximity_head_out_gpio.cb);

  // PROXIMITY_HEAD_IN
  // Set the pin label from the devicetree
  proximity_head_in_gpio.label = DT_PROP(DT_NODELABEL(proximity_head_in), label);
  proximity_head_in_gpio.label_enum = PROXIMITY_HEAD_IN;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  proximity_head_in_gpio.status_indicator_pin = &status_indicators.proximity_head_in;
  // Check if the gpio is ready
  if (!device_is_ready(proximity_head_in_spec.port)) LOG_ERR("%s pin %d is not ready!",
    proximity_head_in_gpio.label, proximity_head_in_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&proximity_head_in_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, proximity_head_in_gpio.label, proximity_head_in_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&proximity_head_in_spec, GPIO_INT_EDGE_BOTH);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, proximity_head_in_gpio.label, proximity_head_in_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&proximity_head_in_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(proximity_head_in_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(proximity_head_in_spec.port, &proximity_head_in_gpio.cb);

  // PROXIMITY_SHEAR_HOME
  // Set the pin label from the devicetree
  proximity_shear_home_gpio.label = DT_PROP(DT_NODELABEL(proximity_shear_home), label);
  proximity_shear_home_gpio.label_enum = PROXIMITY_SHEAR_HOME;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  proximity_shear_home_gpio.status_indicator_pin = &status_indicators.proximity_shear_home;
  // Check if the gpio is ready
  if (!device_is_ready(proximity_shear_home_spec.port)) LOG_ERR("%s pin %d is not ready!",
    proximity_shear_home_gpio.label, proximity_shear_home_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&proximity_shear_home_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, proximity_shear_home_gpio.label, proximity_shear_home_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&proximity_shear_home_spec, GPIO_INT_EDGE_BOTH);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, proximity_shear_home_gpio.label, proximity_shear_home_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&proximity_shear_home_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(proximity_shear_home_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(proximity_shear_home_spec.port, &proximity_shear_home_gpio.cb);

  // PROXIMITY_SHEAR_CUT
  // Set the pin label from the devicetree
  proximity_shear_cut_gpio.label = DT_PROP(DT_NODELABEL(proximity_shear_cut), label);
  proximity_shear_cut_gpio.label_enum = PROXIMITY_SHEAR_CUT;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  proximity_shear_cut_gpio.status_indicator_pin = &status_indicators.proximity_shear_cut;
  // Check if the gpio is ready
  if (!device_is_ready(proximity_shear_cut_spec.port)) LOG_ERR("%s pin %d is not ready!",
    proximity_shear_cut_gpio.label, proximity_shear_cut_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&proximity_shear_cut_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, proximity_shear_cut_gpio.label, proximity_shear_cut_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&proximity_shear_cut_spec, GPIO_INT_EDGE_BOTH);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, proximity_shear_cut_gpio.label, proximity_shear_cut_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&proximity_shear_cut_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(proximity_shear_cut_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(proximity_shear_cut_spec.port, &proximity_shear_cut_gpio.cb);

  // PROXIMITY_TOOL_IN
  // Set the pin label from the devicetree
  proximity_tool_in_gpio.label = DT_PROP(DT_NODELABEL(proximity_tool_in), label);
  proximity_tool_in_gpio.label_enum = PROXIMITY_TOOL_IN;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  proximity_tool_in_gpio.status_indicator_pin = &status_indicators.proximity_tool_in;
  // Check if the gpio is ready
  if (!device_is_ready(proximity_tool_in_spec.port)) LOG_ERR("%s pin %d is not ready!",
    proximity_tool_in_gpio.label, proximity_tool_in_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&proximity_tool_in_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, proximity_tool_in_gpio.label, proximity_tool_in_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&proximity_tool_in_spec, GPIO_INT_EDGE_BOTH);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, proximity_tool_in_gpio.label, proximity_tool_in_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&proximity_tool_in_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(proximity_tool_in_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(proximity_tool_in_spec.port, &proximity_tool_in_gpio.cb);

  // PROXIMITY_TOOL_OUT
  // Set the pin label from the devicetree
  proximity_tool_out_gpio.label = DT_PROP(DT_NODELABEL(proximity_tool_out), label);
  proximity_tool_out_gpio.label_enum = PROXIMITY_TOOL_OUT;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  proximity_tool_out_gpio.status_indicator_pin = &status_indicators.proximity_tool_out;
  // Check if the gpio is ready
  if (!device_is_ready(proximity_tool_out_spec.port)) LOG_ERR("%s pin %d is not ready!",
    proximity_tool_out_gpio.label, proximity_tool_out_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&proximity_tool_out_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, proximity_tool_out_gpio.label, proximity_tool_out_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&proximity_tool_out_spec, GPIO_INT_EDGE_BOTH);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, proximity_tool_out_gpio.label, proximity_tool_out_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&proximity_tool_out_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(proximity_tool_out_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(proximity_tool_out_spec.port, &proximity_tool_out_gpio.cb);

  // PROXIMITY_HEAD_LIMIT
  // Set the pin label from the devicetree
  proximity_head_limit_gpio.label = DT_PROP(DT_NODELABEL(proximity_head_limit), label);
  proximity_head_limit_gpio.label_enum = PROXIMITY_HEAD_LIMIT;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  proximity_head_limit_gpio.status_indicator_pin = &status_indicators.proximity_head_limit;
  // Check if the gpio is ready
  if (!device_is_ready(proximity_head_limit_spec.port)) LOG_ERR("%s pin %d is not ready!",
    proximity_head_limit_gpio.label, proximity_head_limit_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&proximity_head_limit_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, proximity_head_limit_gpio.label, proximity_head_limit_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&proximity_head_limit_spec, GPIO_INT_EDGE_BOTH);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, proximity_head_limit_gpio.label, proximity_head_limit_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&proximity_head_limit_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(proximity_head_limit_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(proximity_head_limit_spec.port, &proximity_head_limit_gpio.cb);

  // PROXIMITY_HEAD_CW
  // Set the pin label from the devicetree
  proximity_head_cw_gpio.label = DT_PROP(DT_NODELABEL(proximity_head_cw), label);
  proximity_head_cw_gpio.label_enum = PROXIMITY_HEAD_CW;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  proximity_head_cw_gpio.status_indicator_pin = &status_indicators.proximity_head_cw;
  // Check if the gpio is ready
  if (!device_is_ready(proximity_head_cw_spec.port)) LOG_ERR("%s pin %d is not ready!",
    proximity_head_cw_gpio.label, proximity_head_cw_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&proximity_head_cw_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, proximity_head_cw_gpio.label, proximity_head_cw_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&proximity_head_cw_spec, GPIO_INT_EDGE_BOTH);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, proximity_head_cw_gpio.label, proximity_head_cw_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&proximity_head_cw_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(proximity_head_cw_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(proximity_head_cw_spec.port, &proximity_head_cw_gpio.cb);

  // PROXIMITY_HEAD_CCW
  // Set the pin label from the devicetree
  proximity_head_ccw_gpio.label = DT_PROP(DT_NODELABEL(proximity_head_ccw), label);
  proximity_head_ccw_gpio.label_enum = PROXIMITY_HEAD_CCW;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  proximity_head_ccw_gpio.status_indicator_pin = &status_indicators.proximity_head_ccw;
  // Check if the gpio is ready
  if (!device_is_ready(proximity_head_ccw_spec.port)) LOG_ERR("%s pin %d is not ready!",
    proximity_head_ccw_gpio.label, proximity_head_ccw_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&proximity_head_ccw_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, proximity_head_ccw_gpio.label, proximity_head_ccw_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&proximity_head_ccw_spec, GPIO_INT_EDGE_BOTH);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, proximity_head_ccw_gpio.label, proximity_head_ccw_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&proximity_head_ccw_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(proximity_head_ccw_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(proximity_head_ccw_spec.port, &proximity_head_ccw_gpio.cb);

  // Buttons
  // SHEAR_BUTTON
  // Set the pin label from the devicetree
  shear_button_gpio.label = DT_PROP(DT_NODELABEL(shear_button), label);
  shear_button_gpio.label_enum = SHEAR_BUTTON;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  shear_button_gpio.status_indicator_pin = &status_indicators.shear_button;
  // Check if the gpio is ready
  if (!device_is_ready(shear_button_spec.port)) LOG_ERR("%s pin %d is not ready!",
    shear_button_gpio.label, shear_button_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&shear_button_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, shear_button_gpio.label, shear_button_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&shear_button_spec, GPIO_INT_EDGE_BOTH);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, shear_button_gpio.label, shear_button_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&shear_button_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(shear_button_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(shear_button_spec.port, &shear_button_gpio.cb);

  // AUTO_BUTTON
  // Set the pin label from the devicetree
  auto_button_gpio.label = DT_PROP(DT_NODELABEL(auto_button), label);
  auto_button_gpio.label_enum = AUTO_BUTTON;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  auto_button_gpio.status_indicator_pin = &status_indicators.auto_button;
  // Check if the gpio is ready
  if (!device_is_ready(auto_button_spec.port)) LOG_ERR("%s pin %d is not ready!",
    auto_button_gpio.label, auto_button_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&auto_button_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, auto_button_gpio.label, auto_button_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&auto_button_spec, GPIO_INT_EDGE_BOTH);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, auto_button_gpio.label, auto_button_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&auto_button_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(auto_button_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(auto_button_spec.port, &auto_button_gpio.cb);

  // Auxillary
  // ESTOP
  // Set the pin label from the devicetree
  estop_gpio.label = DT_PROP(DT_NODELABEL(estop), label);
  estop_gpio.label_enum = ESTOP;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  estop_gpio.status_indicator_pin = &status_indicators.e_stop;
  // Check if the gpio is ready
  if (!device_is_ready(estop_spec.port)) LOG_ERR("%s pin %d is not ready!",
    estop_gpio.label, estop_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&estop_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, estop_gpio.label, estop_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&estop_spec, GPIO_INT_EDGE_BOTH);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, estop_gpio.label, estop_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&estop_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(estop_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(estop_spec.port, &estop_gpio.cb);

  // FUSE
  // Set the pin label from the devicetree
  fuse_gpio.label = DT_PROP(DT_NODELABEL(fuse), label);
  fuse_gpio.label_enum = FUSE;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  fuse_gpio.status_indicator_pin = &status_indicators.fuse;
  // Check if the gpio is ready
  if (!device_is_ready(fuse_spec.port)) LOG_ERR("%s pin %d is not ready!",
    fuse_gpio.label, fuse_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&fuse_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, fuse_gpio.label, fuse_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&fuse_spec, GPIO_INT_EDGE_BOTH);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, fuse_gpio.label, fuse_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&fuse_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(fuse_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(fuse_spec.port, &fuse_gpio.cb);

  // Power
  // 24VRAW
  // Set the pin label from the devicetree
  vraw24_gpio.label = DT_PROP(DT_NODELABEL(vraw24), label);
  vraw24_gpio.label_enum = RAW24V;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  vraw24_gpio.status_indicator_pin = &status_indicators.vraw24;
  // Check if the gpio is ready
  if (!device_is_ready(vraw24_spec.port)) LOG_ERR("%s pin %d is not ready!",
    vraw24_gpio.label, vraw24_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&vraw24_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, vraw24_gpio.label, vraw24_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&vraw24_spec, GPIO_INT_EDGE_BOTH);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, vraw24_gpio.label, vraw24_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&vraw24_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(vraw24_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(vraw24_spec.port, &vraw24_gpio.cb);

  // AUX24V
  // Set the pin label from the devicetree
  aux24v_gpio.label = DT_PROP(DT_NODELABEL(aux24v), label);
  aux24v_gpio.label_enum = AUX24V;
  // This allows gpio_interrupt_handler to directly manipulate the interface structure
  aux24v_gpio.status_indicator_pin = &status_indicators.aux24v;
  // Check if the gpio is ready
  if (!device_is_ready(aux24v_spec.port)) LOG_ERR("%s pin %d is not ready!",
    aux24v_gpio.label, aux24v_spec.pin);
  // Configure gpio as an input
  err = gpio_pin_configure_dt(&aux24v_spec, GPIO_INPUT);
  if (err != 0) LOG_ERR("Error %d: failed to configure %s pin %d",
    err, aux24v_gpio.label, aux24v_spec.pin);
  // Enable interrupt for rising edges
  err = gpio_pin_interrupt_configure_dt(&aux24v_spec, GPIO_INT_EDGE_BOTH);
  if (err != 0) LOG_ERR("Error %d: failed to configure interrupt on %s pin %d",
    err, aux24v_gpio.label, aux24v_spec.pin);
  // Initialize callback structure for interrupt
  gpio_init_callback(&aux24v_gpio.cb, (gpio_callback_handler_t)gpio_interrupt_handler,
    BIT(aux24v_spec.pin));
  // Attach callback function to interrupt
  gpio_add_callback(aux24v_spec.port, &aux24v_gpio.cb);

  LOG_INF("Done initalizing GPIO pins");
}

#endif //INIT_GPIO_H
