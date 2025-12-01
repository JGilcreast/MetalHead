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
#include "interface_t.h"
#include "queues.h"

/* The amount of time to sleep between checking the end travel proximity sensor
 * Look at the while loops in the move functions
 */
#define PROCESSING_SLEEP_MSEC 100

/* The amount of time that must elapse since turning on a solenoid with the
 * proximity sensor where it started not turning off/going LOW.
 * Used in the check functions.
 */
#define NOT_RESPONDING_THRESHOLD_MSEC 500
struct interface_t interface;

void init_interface() {
  interface.state = STATE_HOME; // Default state at startup
  interface.primary_action = PRIMARY_ACTION_NONE; // Shear
  interface.secondary_action = SECONDARY_ACTION_NONE; // But before we can shear, retract the shear
}

// Turn on or off
static void turn_on_shear_cut() {
  gpio_pin_set_dt(&shear_cut_spec, GPIO_STATE_HIGH);
}
static void turn_off_shear_cut() {
  gpio_pin_set_dt(&shear_cut_spec, GPIO_STATE_LOW);
}
static void turn_on_shear_home() {
  gpio_pin_set_dt(&shear_home_spec, GPIO_STATE_HIGH);
}
static void turn_off_shear_home() {
  gpio_pin_set_dt(&shear_home_spec, GPIO_STATE_LOW);
}
static void turn_on_tool_out() {
  gpio_pin_set_dt(&tool_out_spec, GPIO_STATE_HIGH);
}
static void turn_off_tool_out() {
  gpio_pin_set_dt(&tool_out_spec, GPIO_STATE_LOW);
}
static void turn_on_tool_in() {
  gpio_pin_set_dt(&tool_in_spec, GPIO_STATE_HIGH);
}
static void turn_off_tool_in() {
  gpio_pin_set_dt(&tool_in_spec, GPIO_STATE_LOW);
}
static void turn_on_feed_forward() {
  gpio_pin_set_dt(&feed_forward_spec, GPIO_STATE_HIGH);
}
static void turn_off_feed_forward() {
  gpio_pin_set_dt(&feed_forward_spec, GPIO_STATE_LOW);
}
static void turn_on_feed_reverse() {
  gpio_pin_set_dt(&feed_reverse_spec, GPIO_STATE_HIGH);
}
static void turn_off_feed_reverse() {
  gpio_pin_set_dt(&feed_reverse_spec, GPIO_STATE_LOW);
}
static void turn_on_head_cw() {
  gpio_pin_set_dt(&head_cw_spec, GPIO_STATE_HIGH);
}
static void turn_off_head_cw() {
  gpio_pin_set_dt(&head_cw_spec, GPIO_STATE_LOW);
}
static void turn_on_head_ccw() {
  gpio_pin_set_dt(&head_ccw_spec, GPIO_STATE_HIGH);
}
static void turn_off_head_ccw() {
  gpio_pin_set_dt(&head_ccw_spec, GPIO_STATE_LOW);
}
static void turn_on_head_out() {
  gpio_pin_set_dt(&head_out_spec, GPIO_STATE_HIGH);
}
static void turn_off_head_out() {
  gpio_pin_set_dt(&head_out_spec, GPIO_STATE_LOW);
}
static void turn_on_head_in() {
  gpio_pin_set_dt(&head_in_spec, GPIO_STATE_HIGH);
}
static void turn_off_head_in() {
  gpio_pin_set_dt(&head_in_spec, GPIO_STATE_LOW);
}

/* Virtual ESTOP */
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
/* Checks ran while rprocessing a shape/manual action */
/* ToDo: Implement a way to send these specific errors to the HMI */
inline void check_no_inputs_responding() {
  /* These conditions are taken from page 20 of the user manual
   * When the controller turned on, it detected that none of the proximity switches were on.
   * Check the flat ribbon input cable from the terminal board to the controller.
   */
  int inputs = hmi_server_msg.payload.hmi_client_msg.encoder_feed_set +
    hmi_server_msg.payload.hmi_client_msg.encoder_feed_reset +
      hmi_server_msg.payload.hmi_client_msg.encoder_bend_set +
        hmi_server_msg.payload.hmi_client_msg.encoder_bend_reset +
          hmi_server_msg.payload.hmi_client_msg.proximity_head_out +
            hmi_server_msg.payload.hmi_client_msg.proximity_head_in +
              hmi_server_msg.payload.hmi_client_msg.proximity_shear_home +
                hmi_server_msg.payload.hmi_client_msg.proximity_shear_cut +
                  hmi_server_msg.payload.hmi_client_msg.proximity_tool_in +
                    hmi_server_msg.payload.hmi_client_msg.proximity_tool_out +
                      hmi_server_msg.payload.hmi_client_msg.shear_button +
                        hmi_server_msg.payload.hmi_client_msg.proximity_head_limit +
                          hmi_server_msg.payload.hmi_client_msg.proximity_head_cw +
                            hmi_server_msg.payload.hmi_client_msg.proximity_head_ccw;
  if (inputs == 0) {
    LOG_WRN("*** No inputs are responding ***");
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_ERROR;
  }
}

inline void check_neither_inputs() {
  /* These conditions are taken from page 20 of the user manual
   * These 3 messages draw the operator's attention to unusual
   * start-up conditions for the machine.
   */
  if (!hmi_server_msg.payload.hmi_client_msg.proximity_head_in
    && !hmi_server_msg.payload.hmi_client_msg.proximity_head_out) {
    LOG_WRN("*** Neither head inputs are on ***");
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_ERROR;
  }
  if (!hmi_server_msg.payload.hmi_client_msg.proximity_tool_in
    && !hmi_server_msg.payload.hmi_client_msg.proximity_tool_out) {
    LOG_WRN("*** Neither tool inputs are on ***");
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_ERROR;
  }
  if (!hmi_server_msg.payload.hmi_client_msg.proximity_shear_home
    && !hmi_server_msg.payload.hmi_client_msg.proximity_shear_cut) {
    LOG_WRN("*** Neither shear inputs are on ***");
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_ERROR;
  }
}

inline void check_both_inputs() {
  /* These conditions are taken from page 20 of the user manual
   * These messages indicate a proximity switch error.
   * Never should two corresponding proximity switches be on.
   */
  if (hmi_server_msg.payload.hmi_client_msg.proximity_head_in
    && hmi_server_msg.payload.hmi_client_msg.proximity_head_out) {
    LOG_WRN("*** Both head inputs are on ***");
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_ERROR;
  }
  if (hmi_server_msg.payload.hmi_client_msg.proximity_tool_in
    && hmi_server_msg.payload.hmi_client_msg.proximity_tool_out) {
    LOG_WRN("*** Both tool inputs are on ***");
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_ERROR;
  }
  if (hmi_server_msg.payload.hmi_client_msg.proximity_shear_home
    && hmi_server_msg.payload.hmi_client_msg.proximity_shear_cut) {
    LOG_WRN("*** Both shear inputs are on ***");
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_ERROR;
  }
}

inline void check_suspicious_status() {
  /* These conditions are taken from page 20 of the user manual
   * This message will be displayed if the head is in while the tool is out,
   * or if the tool is in while the head is out. It may signal either a
   * jammed head assembly, a failed or incorrectly connected proximity sensor.
   */
  if ((hmi_server_msg.payload.hmi_client_msg.proximity_head_in &&
    hmi_server_msg.payload.hmi_client_msg.proximity_tool_out) ||
    (hmi_server_msg.payload.hmi_client_msg.proximity_tool_in &&
      hmi_server_msg.payload.hmi_client_msg.proximity_head_out)) {
    LOG_WRN("*** Suspicious head/tool status ***");
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_ERROR;
  }
}

/* These conditions are taken from page 20 of the user manual.
 * The following checks display a message if a proximity switch for the
 * starting position of an actuator does not turn off, and the proximity
 * sensor for the end of travel does not turn on when the actuator's solenoid
 * is energized. It may be a mechanical failure, a fault with a proximity sensor,
 * the solenoid, or the interface board.
 */

/* To return true, the elapsed time must be greater than
 * the threshold and PROXIMITY_HEAD_OUT is LOW.
 * This is considered a fault
 */
inline bool check_move_head_out_fault(uint64_t start_time) {
  return !hmi_server_msg.payload.hmi_client_msg.proximity_head_out &&
    k_uptime_get() - start_time > NOT_RESPONDING_THRESHOLD_MSEC;
}

/* Simple actions: These use turn on and off
 * to complete a task (e.g., cut the rebar) */
inline bool move_head_out() {
  /* If the head is out, don't turn on the solenoid to move it out */
  if (hmi_server_msg.payload.hmi_client_msg.proximity_head_out) {
    LOG_WRN("Head is already out!");
  } else {
    bool fault = false;
    /* Record the time that we turn on the solenoid */
    uint32_t start_time = k_uptime_get();
    /* Turn on the solenoid to move the head out */
    turn_on_head_out();
    /* Change the state */
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_PROCESS_ACTION;
    /* Change the action */
    hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_HEAD_OUT;
    /* While the head is still not out... */
    while (!hmi_server_msg.payload.hmi_client_msg.proximity_head_out) {
      /* Keep sleeping for x msecs */
      k_sleep(K_MSEC(PROCESSING_SLEEP_MSEC));
      if (check_move_head_out_fault(start_time)) {
        fault = true;
        /* Exit the while loop */
        break;
      }
    }
    /* Turn the solenoid off */
    turn_off_head_out();
    if (fault) {
      /* Change the state */
      hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_ERROR;
      /* Change the action */
      hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_NONE;
      LOG_ERR("*** Head out Not responding ***");
      return false;
    }
    /* Change the state */
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_IDLE;
    /* Change the action */
    hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_NONE;
    LOG_INF("Head is out!");

    return true;
  }
}
inline void move_head_in() {
  /* If the head is in, don't turn on the solenoid to move it in */
  if (hmi_server_msg.payload.hmi_client_msg.proximity_head_in) {
    LOG_WRN("Head is already in!");
  } else {
    /* Turn on the solenoid to move the head in */
    turn_on_head_in();
    /* Change the state */
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_PROCESS_ACTION;
    /* Change the action */
    hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_HEAD_IN;
    /* While the head is still not in... */
    while (!hmi_server_msg.payload.hmi_client_msg.proximity_head_in)
      k_sleep(K_MSEC(PROCESSING_SLEEP_MSEC)); /* Keep sleeping for x msecs */
    /* The head is in, turn the solenoid off */
    turn_off_head_in();
    /* Change the state */
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_IDLE;
    /* Change the action */
    hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_NONE;
    LOG_INF("Head is in!");
  }
}
inline void move_shear_home() {
  /* If the shear is in, don't turn on the solenoid to move it in */
  if (hmi_server_msg.payload.hmi_client_msg.proximity_shear_home) {
    LOG_WRN("Shear is already in home position!");
  } else {
    /* Turn on the solenoid to move the shear in */
    turn_on_shear_home();
    /* Change the state */
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_PROCESS_ACTION;
    /* Change the action */
    hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_SHEAR_RETRACT;
    /* While the shear is still not home... */
    while (!hmi_server_msg.payload.hmi_client_msg.proximity_shear_home)
      k_sleep(K_MSEC(PROCESSING_SLEEP_MSEC)); /* Keep sleeping for x msecs */
    /* The shear is in, turn the solenoid off */
    turn_off_shear_home();
    /* Change the state */
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_IDLE;
    /* Change the action */
    hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_NONE;
    LOG_INF("Shear is in home position!");
  }
}
inline void move_shear_cut() {
  if (hmi_server_msg.payload.hmi_client_msg.proximity_shear_cut) {
    LOG_WRN("Shear is already in cut position!");
  } else {
    /* Turn on the solenoid to move the shear to the cut position */
    turn_on_shear_cut();
    /* Change the state */
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_PROCESS_ACTION;
    /* Change the action */
    hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_SHEAR;
    /* While the shear is still not cut position... */
    while (!hmi_server_msg.payload.hmi_client_msg.proximity_shear_cut)
      k_sleep(K_MSEC(PROCESSING_SLEEP_MSEC)); /* Keep sleeping for x msecs */
    /* The shear is in the cut position, turn the solenoid off */
    turn_off_shear_cut();
    /* Change the state */
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_IDLE;
    /* Change the action */
    hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_NONE;
    LOG_INF("Shear is in cut position!");
    /* Retract the shear */
  }
}
inline void move_tool_in() {
  /* If the tool is in, don't turn on the solenoid to move it in */
  if (hmi_server_msg.payload.hmi_client_msg.proximity_tool_in) {
    LOG_WRN("Tool is already in!");
  } else {
    /* Turn on the solenoid to move the tool in */
    turn_on_tool_in();
    /* Change the state */
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_PROCESS_ACTION;
    /* Change the action */
    hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_TOOL_IN;
    /* While the tool is still not home... */
    while (!hmi_server_msg.payload.hmi_client_msg.proximity_tool_in)
      k_sleep(K_MSEC(PROCESSING_SLEEP_MSEC)); /* Keep sleeping for x msecs */
    /* The tool is in, turn the solenoid off */
    turn_off_tool_in();
    /* Change the state */
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_IDLE;
    /* Change the action */
    hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_NONE;
    LOG_INF("Tool is in!");
  }
}
inline void move_tool_out() {
  /* If the tool is out, don't turn on the solenoid to move it out */
  if (hmi_server_msg.payload.hmi_client_msg.proximity_tool_out) {
    LOG_WRN("Tool is already out!");
  } else {
    /* Turn on the solenoid to move the tool out */
    turn_on_tool_out();
    /* Change the state */
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_PROCESS_ACTION;
    /* Change the action */
    hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_TOOL_OUT;
    /* While the tool is still not home... */
    while (!hmi_server_msg.payload.hmi_client_msg.proximity_tool_out)
      k_sleep(K_MSEC(PROCESSING_SLEEP_MSEC)); /* Keep sleeping for x msecs */
    /* The tool is out, turn the solenoid off */
    turn_off_tool_out();
    /* Change the state */
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_IDLE;
    /* Change the action */
    hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_NONE;
    LOG_INF("Tool is out!");
  }
}
inline void move_head_cw() {
  if (hmi_server_msg.payload.hmi_client_msg.proximity_head_cw) {
    LOG_WRN("Head is already in CW position!");
  } else {
    /* Turn on the solenoid to move the head CW */
    turn_on_head_cw();
    /* Change the state */
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_PROCESS_ACTION;
    /* Change the action */
    hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_HEAD_CW;
    /* While the head is still not in the CW position... */
    while (!hmi_server_msg.payload.hmi_client_msg.proximity_head_cw)
      k_sleep(K_MSEC(PROCESSING_SLEEP_MSEC)); /* Keep sleeping for x msecs */
    /* The head is in the most CW position, turn the solenoid off */
    turn_off_head_cw();
    /* Change the state */
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_IDLE;
    /* Change the action */
    hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_NONE;
    LOG_INF("Head is at maximum CW position!");
  }
}
inline void move_head_ccw() {
  if (hmi_server_msg.payload.hmi_client_msg.proximity_head_ccw) {
    LOG_WRN("Head is already in CCW position!");
  } else {
    /* Turn on the solenoid to move the head CCW */
    turn_on_head_ccw();
    /* Change the state */
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_PROCESS_ACTION;
    /* Change the action */
    hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_HEAD_CW;
    /* While the head is still not in the most CCW position... */
    while (!hmi_server_msg.payload.hmi_client_msg.proximity_head_ccw)
      k_sleep(K_MSEC(PROCESSING_SLEEP_MSEC)); /* Keep sleeping for x msecs */
    /* The head is in the most CCW position, turn the solenoid off */
    turn_off_head_ccw();
    /* Change the state */
    hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_IDLE;
    /* Change the action */
    hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_NONE;
    LOG_INF("Head is at maximum CCW position!");
  }
}

/* Manual Actions: These use simple actions to demonstrate machine functionality */
inline void manual_action_head_out() {
  /* Move head in */
  move_head_in();
  /* Move head out */
  move_head_out();
}

inline void manual_action_head_in() {
  /* Move head out */
  move_head_out();
  /* Move head in */
  move_head_in();
}

inline void manual_action_shear_home() {
  /* Move shear home */
  move_shear_home();
}

inline void manual_action_shear_cut() {
  /* Move shear home */
  move_shear_home();
  /* Shear */
  move_shear_cut();
  /* Move shear home */
  move_shear_home();
}

inline void manual_action_tool_in() {
  /* Move tool out */
  move_tool_out();
  /* Move tool in */
  move_tool_in();
}

inline void manual_action_tool_out() {
  /* Move tool in */
  move_tool_in();
  /* Move tool out */
  move_tool_out();
}

inline void manual_action_head_cw() {
  /* Go to the CCW position */
  move_head_ccw();
  /* Go to the CW position */
  move_head_cw();
}

inline void manual_action_head_ccw() {
  /* Go to the CW position */
  move_head_cw();
  /* Go to the CCW position */
  move_head_ccw();
}

inline void manual_action_feed_forward() {

}

inline void manual_action_feed_reverse() {

}

inline void action_estop() {
  turn_off_everything();
}

/* General machine functions */

/* Let's check to see if the machine is homed correctly.
 * Someone may have moved the head or tool manually in
 * between startups that we were not aware of.
 * Think of this as homing a 3D printer at start up
 * and in between print jobs.
 */
inline void home() {
  manual_action_shear_home();
  manual_action_tool_in();
  manual_action_head_in();
  // We're done with the homing sequence
  hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_IDLE;
  hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_NONE;
}

// Shapes
bool check_shape(struct shape_t shape);

bool add_shape(struct shape_t shape);

void delete_shape(int id);


#endif //INTERFACE_H
