// MetalHead - Opensource Firmware & Software For The 85V Automatic Stirrup Bender
// Copyright (C) 2024-2025 John Gilcreast (johngilcreast@gmail.com)
// Copyright (C) 2025 Connor McMillan (connor@mcmillan.website)
//
// interface program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// interface program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with interface program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef INTERFACE_H
#define INTERFACE_H
#include "state_t.h"
#include "primary_action_t.h"
#include "secondary_action_t.h"
#include "shape_t.h"
#include "src/status_indicators_t.pb.h"
#include "interface_t.h"
#include "queues.h"

struct interface_t interface;
struct _status_indicators_t status_indicators = status_indicators_t_init_default;

void init_interface() {
  interface.state = STATE_HOME; // Default state at startup
  interface.primary_action = PRIMARY_ACTION_NONE; // Shear
  interface.secondary_action = SECONDARY_ACTION_NONE; // But before we can shear, retract the shear
}

// Turn on or off
static void turn_on_shear_cut() {
  gpio_pin_set_dt(&shear_cut_spec, 1);
}
static void turn_off_shear_cut() {
  gpio_pin_set_dt(&shear_cut_spec, 0);
}
static bool get_shear_cut_status() {
  return gpio_pin_get_dt(&shear_cut_spec);
}
static void turn_on_shear_home() {
  gpio_pin_set_dt(&shear_home_spec, 1);
}
static void turn_off_shear_home() {
  gpio_pin_set_dt(&shear_home_spec, 0);
}
static bool get_shear_home_status() {
  return gpio_pin_get_dt(&shear_home_spec);
}
static void turn_on_tool_out() {
  gpio_pin_set_dt(&tool_out_spec, 1);
}
static void turn_off_tool_out() {
  gpio_pin_set_dt(&tool_out_spec, 0);
}
static bool get_tool_out_status() {
  return gpio_pin_get_dt(&tool_out_spec);
}
static void turn_on_tool_in() {
  gpio_pin_set_dt(&tool_in_spec, 1);
}
static void turn_off_tool_in() {
  gpio_pin_set_dt(&tool_in_spec, 0);
}
static bool get_tool_in_status() {
  return gpio_pin_get_dt(&tool_in_spec);
}
static void turn_on_feed_forward() {
  gpio_pin_set_dt(&feed_forward_spec, 1);
}
static void turn_off_feed_forward() {
  gpio_pin_set_dt(&feed_forward_spec, 0);
}
static bool get_feed_forward_status() {
  return gpio_pin_get_dt(&feed_forward_spec);
}
static void turn_on_feed_reverse() {
  gpio_pin_set_dt(&feed_reverse_spec, 1);
}
static void turn_off_feed_reverse() {
  gpio_pin_set_dt(&feed_reverse_spec, 0);
}
static bool get_feed_reverse_status() {
  return gpio_pin_get_dt(&feed_reverse_spec);
}
static void turn_on_head_cw() {
  gpio_pin_set_dt(&head_cw_spec, 1);
}
static void turn_off_head_cw() {
  gpio_pin_set_dt(&head_cw_spec, 0);
}
static bool get_head_cw_status() {
  return gpio_pin_get_dt(&head_cw_spec);
}
static void turn_on_head_ccw() {
  gpio_pin_set_dt(&head_ccw_spec, 1);
}
static void turn_off_head_ccw() {
  gpio_pin_set_dt(&head_ccw_spec, 0);
}
static bool get_head_ccw_status() {
  return gpio_pin_get_dt(&head_ccw_spec);
}
static void turn_on_head_out() {
  gpio_pin_set_dt(&head_out_spec, 1);
}
static void turn_off_head_out() {
  gpio_pin_set_dt(&head_out_spec, 0);
}
static bool get_head_out_status() {
  return gpio_pin_get_dt(&head_out_spec);
}
static void turn_on_head_in() {
  gpio_pin_set_dt(&head_in_spec, 1);
}
static void turn_off_head_in() {
  gpio_pin_set_dt(&head_in_spec, 0);
}
static bool get_head_in_status() {
  return gpio_pin_get_dt(&head_in_spec);
}

// Will be mostly used by ESTOP
static void turn_off_everything() {
  turn_off_shear_cut();
  turn_off_shear_home();
  turn_off_tool_out();
  turn_off_tool_in();
  turn_off_feed_forward();
  turn_off_feed_reverse();
  turn_off_head_cw();
  turn_off_head_ccw();
  turn_off_head_out();
  turn_off_head_in();
}

// Simple actions
// These utilize turn on and offs to complete a task (e.g. cut the rebar)

void retract_shear() {
  if (interface.secondary_action == SECONDARY_ACTION_SHEAR_RETRACT) { // Are we supposed to retract back?
    if (!status_indicators.proximity_shear_home) { // Are we back home yet?
      turn_on_shear_home(); // Keep going back home
    } else {
      turn_off_shear_home(); // We're home!
      interface.secondary_action = SECONDARY_ACTION_NONE; // We're finished with interface action
    }
  }
}

void cut_rebar() {
  // Keep retracting shear if needed
  if (interface.secondary_action == SECONDARY_ACTION_SHEAR_RETRACT) {
    retract_shear();
    return;
  }

  // Retract shear if shear is in limbo
  if (interface.primary_action == PRIMARY_ACTION_SHEAR) { // If the primary action is to shear
    if (interface.secondary_action == SECONDARY_ACTION_NONE) { // and if there is no secondary action
      if (!status_indicators.proximity_shear_home) { // and if shear is NOT in home position
        if (!get_shear_cut_status()) { // and if shear solenoid is NOT already turned on
          interface.secondary_action = SECONDARY_ACTION_SHEAR_RETRACT;
          retract_shear();
          return;
        }
      }
    }
  }

  // If the shear is in the home position, and its solenoid is off, activate the solenoid to cut it
  if (interface.primary_action == PRIMARY_ACTION_SHEAR) // If the primary action is to shear
    if (!get_shear_cut_status()) // and if the shear solenoid is off
        if (interface.secondary_action == SECONDARY_ACTION_NONE) { // And there are no secondary actions in the queue
          turn_on_shear_cut();
          return;
        }

  // Continue to shear until we reach the limit
  if (interface.primary_action == PRIMARY_ACTION_SHEAR) // If the primary action is to shear
    if (get_shear_cut_status()) // and if the shear solenoid is on
      if (status_indicators.proximity_shear_cut) { // and if the shear reached its limit
        turn_off_shear_cut(); // Turn off the shear
        interface.primary_action = PRIMARY_ACTION_NONE; // We are done shearing
        interface.secondary_action = SECONDARY_ACTION_SHEAR_RETRACT; // Retract the shear
        retract_shear();
      }
}

void bend_rebar_cw(struct angle_t angle, uint8_t center_pin_modifier) {

}

void bend_rebar_ccw(struct angle_t angle, uint8_t center_pin_modifier) {

}

void retract_tool() {

}

void retract_head() {

}

void feed_forward(struct angle_t angle, uint16_t feed_scale) {

}

void feed_reverse(struct angle_t angle, uint16_t feed_scale) {

}

// General machine functions

// Let's check to see if the machine is homed correctly.
// Someone may have moved the head or tool manually in between startups that we were not aware of.
// Think of this as homing a 3D printer at start up and in between print jobs.
void home() {
  retract_shear();
  retract_tool();
  retract_head();
  // We're done with the homing sequence
  interface.state = STATE_IDLE;
};

// Shapes
bool check_shape(struct shape_t shape);

bool add_shape(struct shape_t shape);

void delete_shape(int id);

// INCOMPLETE
// The first most important thread. Process shapes!
void shape_process_thread() {
  struct shape_t shape; // Change this to shape_t data struct
  // The thread runs forever
  LOG_INF("Starting shape processor thread");
  while (1) {
    // Check to see if we have a shape to process in the queue
    if (k_msgq_get(&shape_queue, &shape, K_FOREVER)) {
      // We have a shape to process
      // home();
      // for shape->angle != null
      //   feed_forward(angle->length);
      //   bend_cw(angle) or bend_ccw(angle);
      // cut_rebar();
      // home();
    }
  }
}

// Helper functions
// Ideally we shouldn't have to poll (gpio_pin_get_dt()) each pin but we are in the development phase.
void update_status_indicators(status_indicators_t *status_indicators) {
  status_indicators->shear_cut = gpio_pin_get_dt(&shear_cut_spec);
  status_indicators->shear_home = gpio_pin_get_dt(&shear_home_spec);
  status_indicators->tool_out = gpio_pin_get_dt(&tool_out_spec);
  status_indicators->tool_in = gpio_pin_get_dt(&tool_in_spec);
  status_indicators->feed_forward = gpio_pin_get_dt(&feed_forward_spec);
  status_indicators->feed_reverse = gpio_pin_get_dt(&feed_reverse_spec);
  status_indicators->head_cw = gpio_pin_get_dt(&head_cw_spec);
  status_indicators->head_ccw = gpio_pin_get_dt(&head_ccw_spec);
  status_indicators->head_out = gpio_pin_get_dt(&head_out_spec);
  status_indicators->head_in = gpio_pin_get_dt(&head_in_spec);
  status_indicators->encoder_feed_set = gpio_pin_get_dt(&encoder_feed_set_spec);
  status_indicators->encoder_feed_reset = gpio_pin_get_dt(&encoder_feed_reset_spec);
  status_indicators->encoder_bend_set = gpio_pin_get_dt(&encoder_bend_set_spec);
  status_indicators->encoder_bend_reset = gpio_pin_get_dt(&encoder_bend_reset_spec);
  status_indicators->proximity_head_out = gpio_pin_get_dt(&proximity_head_out_spec);
  status_indicators->proximity_head_in = gpio_pin_get_dt(&proximity_head_in_spec);
  status_indicators->proximity_shear_home = gpio_pin_get_dt(&proximity_shear_home_spec);
  status_indicators->proximity_shear_cut = gpio_pin_get_dt(&proximity_shear_cut_spec);
  status_indicators->proximity_tool_in = gpio_pin_get_dt(&proximity_tool_in_spec);
  status_indicators->proximity_tool_out = gpio_pin_get_dt(&proximity_tool_out_spec);
  status_indicators->shear_button = gpio_pin_get_dt(&shear_button_spec);
  status_indicators->proximity_head_limit = gpio_pin_get_dt(&proximity_head_limit_spec);
  status_indicators->proximity_head_cw = gpio_pin_get_dt(&proximity_head_cw_spec);
  status_indicators->proximity_head_ccw = gpio_pin_get_dt(&proximity_head_ccw_spec);
  status_indicators->auto_button = gpio_pin_get_dt(&auto_button_spec);
  status_indicators->e_stop = gpio_pin_get_dt(&estop_spec);
  status_indicators->fuse = gpio_pin_get_dt(&fuse_spec);
  // Includes state, primary, and secondary actions
  // Also, ESTOP will trip FUSE, so check that
  // Fake values below as these have not been implemented at the hardware level
  status_indicators->twenty_four_vraw_bus_voltage = 23.998899;
  status_indicators->twenty_four_vraw_bus_current = 1.50301;
  status_indicators->aux_twenty_four_v_bus_voltage = 23.998899;
  status_indicators->aux_twenty_four_v_bus_current = 1.50301;
  status_indicators->twelve_v_bus_voltage = 11.998899;
  status_indicators->twelve_v_bus_current = 1.50301;
  status_indicators->five_v_bus_voltage = 4.998899;
  status_indicators->five_v_bus_current = 1.50301;
  status_indicators->three_v_three_v_bus_voltage = 3.298899;
  status_indicators->three_v_three_v_bus_current = 1.50301;
  status_indicators->f_gnd_bus_voltage = 23.998899;
  status_indicators->f_gnd_bus_current = 1.50301;
}
#endif //INTERFACE_H
