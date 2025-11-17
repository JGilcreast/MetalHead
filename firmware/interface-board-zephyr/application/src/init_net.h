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

#ifndef INIT_NET_H
#define INIT_NET_H
#include "threads.h"

void init_net(){
  int err = 0;
  struct net_if *iface;
  struct ethernet_req_params params;
  struct in_addr netmask;
  struct in_addr ip_addr;
  iface = net_if_get_default();

  // Grab EEPROM settings to pass on
  memcpy(&ip_addr.s_addr, eeprom_data.ip_address, sizeof(ip_addr.s_addr));
  memcpy(&netmask.s_addr, eeprom_data.subnet_mask, sizeof(eeprom_data.subnet_mask));
  memcpy(&params.mac_address.addr, eeprom_data.mac_address, sizeof(eeprom_data.mac_address));

  // Make sure that the interface is down
  net_if_down(iface);

  if (net_if_ipv4_addr_add(iface, &ip_addr, NET_ADDR_MANUAL, 0) == NULL)
    LOG_ERR("Failed to set IP address (%d)", err);

  err = net_if_ipv4_set_netmask_by_addr(iface, &ip_addr, &netmask);
  if (!err)
    LOG_ERR("Failed to set subnet mask (%d)", err);

  err = net_mgmt(NET_REQUEST_ETHERNET_SET_MAC_ADDRESS, iface, &params, sizeof(params));
  if (err)
    LOG_ERR("Failed to set MAC address (%d)", err);

  if (!err) {
    // Bring up the interface
    net_if_up(iface);
    // // Start the UDP server thread
    // hmi_server_tid = k_thread_create(&hmi_server_thread_data,
    //   hmi_server_stack_area, K_THREAD_STACK_SIZEOF(hmi_server_stack_area),
    //   (k_thread_entry_t)hmi_server_thread, NULL, NULL, NULL,
    //   K_PRIO_PREEMPT(5),0, K_NO_WAIT);
    // k_thread_name_set(hmi_server_tid, "hmi_server_thread");

    // Start the UDP client thread
    // hmi_client_tid = k_thread_create(&hmi_client_thread_data,
    //   hmi_client_stack_area, K_THREAD_STACK_SIZEOF(hmi_client_stack_area),
    //   (k_thread_entry_t)hmi_client_thread, NULL, NULL, NULL,
    //   K_PRIO_PREEMPT(5),0, K_NO_WAIT);
    // k_thread_name_set(hmi_client_tid, "hmi_client_thread");

    // Start the async TCP server thread
    async_tcp_server_tid = k_thread_create(&async_tcp_server_thread_data,
      async_tcp_server_stack_area, K_THREAD_STACK_SIZEOF(async_tcp_server_stack_area),
      (k_thread_entry_t)async_tcp_server_thread, NULL, NULL, NULL,
      K_PRIO_PREEMPT(5),0, K_NO_WAIT);
    k_thread_name_set(async_tcp_server_tid, "async_tcp_server_thread");
  }
}

#endif //INIT_NET_H
