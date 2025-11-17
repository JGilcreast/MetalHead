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

#ifndef THREAD_DEFINES_H
#define THREAD_DEFINES_H

k_tid_t shape_processor_tid;
k_tid_t hmi_server_tid;
k_tid_t hmi_client_tid;
k_tid_t current_monitor_tid;
k_tid_t async_tcp_server_tid;

K_THREAD_STACK_DEFINE(shape_processor_stack_area, 1024)
struct k_thread shape_processor_thread_data;

K_THREAD_STACK_DEFINE(hmi_server_stack_area, 2048)
struct k_thread hmi_server_thread_data;

K_THREAD_STACK_DEFINE(hmi_client_stack_area, 2048)
struct k_thread hmi_client_thread_data;

K_THREAD_STACK_DEFINE(current_monitor_stack_area, 1024)
struct k_thread current_monitor_thread_data;

K_THREAD_STACK_DEFINE(async_tcp_server_stack_area, 2048)
struct k_thread async_tcp_server_thread_data;

#endif //THREAD_DEFINES_H
