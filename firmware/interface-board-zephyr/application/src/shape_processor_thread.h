// <one line to give the program's name and a brief idea of what it does.>
// Copyright (C) 2025 <name of author>
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

//
// Created by Connor on 11/30/2025.
//

#ifndef INTERFACE_BOARD_ZEPHYR_SHAPE_PROCESSOR_THREAD_H
#define INTERFACE_BOARD_ZEPHYR_SHAPE_PROCESSOR_THREAD_H

/* ToDo: Continue to implement this thread */
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

void init_shape_processor() {
  /* Start the shape processing thread */
  shape_processor_tid = k_thread_create(&shape_processor_thread_data,
    shape_processor_stack_area, K_THREAD_STACK_SIZEOF(shape_processor_stack_area),
    shape_process_thread, NULL, NULL, NULL, -5, 0, K_NO_WAIT);
  k_thread_name_set(shape_processor_tid, "shape_processor_thread");
}

#endif //INTERFACE_BOARD_ZEPHYR_SHAPE_PROCESSOR_THREAD_H