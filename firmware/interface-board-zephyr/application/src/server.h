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
// Created by Connor on 9/26/2025.
//

#ifndef SERVER_H
#define SERVER_H


#define UDP_SERVER_PORT 4242
#define RX_BUF_SIZE 128

void hmi_server_thread() {
  int sock;
  struct sockaddr_in addr;
  char rx_buf[RX_BUF_SIZE];
  int ret;

  // 1. Create a UDP socket
  sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sock < 0) {
    LOG_ERR("Failed to create UDP socket: %d", errno);
    return;
  }

  // 2. Bind the socket to the server address and port
  addr.sin_family = AF_INET;
  addr.sin_port = htons(UDP_SERVER_PORT);
  addr.sin_addr.s_addr = htonl(INADDR_ANY); // Listen on all available interfaces

  ret = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
  if (ret < 0) {
    LOG_ERR("Failed to bind UDP socket: %d", errno);
    close(sock);
    return;
  }

  LOG_INF("HMI UDP server started on port %d", UDP_SERVER_PORT);

  while (1) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // 3. Receive data from a client
    ssize_t bytes_received = recvfrom(sock, rx_buf, sizeof(rx_buf) - 1, 0,
                                     (struct sockaddr *)&client_addr, &client_addr_len);

    if (bytes_received < 0) {
      LOG_ERR("recvfrom failed: %d", errno);
      continue;
    }

    rx_buf[bytes_received] = '\0'; // Null-terminate the received data
    LOG_INF("Received %zd bytes from %s:%d: \"%s\"", bytes_received,
            net_addr_ntop(AF_INET, &client_addr.sin_addr, NULL, 0),
            ntohs(client_addr.sin_port), rx_buf);

    // 4. Optionally, send a reply back to the client
    const char *reply = "ACK from Zephyr UDP server";
    ret = sendto(sock, reply, strlen(reply), 0,
                 (struct sockaddr *)&client_addr, client_addr_len);
    if (ret < 0) {
      LOG_ERR("sendto failed: %d", errno);
    }
  }

  close(sock);
}
#endif //SERVER_H
