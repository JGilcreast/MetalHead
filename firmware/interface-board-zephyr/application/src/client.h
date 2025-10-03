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

#ifndef CLIENT_H
#define CLIENT_H

void hmi_client_thread(void)
{
  struct sockaddr_in remote_addr;
  int sock = -1;
  // Bytes to send to the HMI are stored here
  uint8_t buffer[status_indicators_t_size];
  // Connect the stream to the buffer
  pb_ostream_t ostream = pb_ostream_from_buffer(buffer, status_indicators_t_size);

  // Setup remote address
  remote_addr.sin_family = AF_INET;
  remote_addr.sin_port = htons(3682);
  inet_pton(AF_INET, "192.168.1.184", &remote_addr.sin_addr);

  // Create a UDP socket
  sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sock < 0)
    LOG_ERR("Failed to create socket with HMI.");

  while (1) {
    // Get the latest gpio states in realtime
    update_status_indicators(&status_indicators);
    // Encode the status_indicators obj into the buffer to send to the HMI
    if (pb_encode(&ostream, status_indicators_t_fields, &status_indicators)) {
      // Send to HMI
      int bytes_sent = sendto(sock, buffer, ostream.bytes_written, 0,
                             (struct sockaddr *)&remote_addr, sizeof(remote_addr));
      if (bytes_sent < 0) {
        LOG_ERR("Failed to send data: %d", errno);
      }
      // Reinitialize the stream
      ostream = pb_ostream_from_buffer(buffer, status_indicators_t_size);
    } else {
      LOG_ERR("Failed to encode protobuf message: %s", PB_GET_ERROR(&ostream));
    }
    // Send an update every...
    k_sleep(K_MSEC(250));
  }
}

#endif //CLIENT_H
