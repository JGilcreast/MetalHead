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

#ifndef ASYNC_TCP_SERVER_H
#define ASYNC_TCP_SERVER_H
#include "init_eeprom.h"
#include "version.h"
#include "src/hmi_client_msg.pb.h"
#include "src/hmi_server_msg_t.pb.h"


hmi_server_message hmi_server_msg = hmi_server_message_init_zero;
hmi_server_message hmi_server_resp = hmi_server_message_init_zero;


/* For Zephyr, keep max number of fd's in sync with max poll() capacity */
#define NUM_FDS 5

/* Number of simultaneous client connections will be NUM_FDS be minus 2 */
struct pollfd pollfds[NUM_FDS];
int pollnum;

hmi_client_message hmi_client_msg;
hmi_server_message hmi_server_response;

#define fatal(msg, ...) { \
LOG_ERR("Error: %s %s", msg, ##__VA_ARGS__); \
}

void error_no(char str[], int error) {
	if (error == EAGAIN)
		LOG_ERR("%s: EAGAIN/EWOULDBLOCK", str);
	else if (error == EBADF)
		LOG_ERR("%s: EBADF", str);
	else if (error == ECONNRESET)
			LOG_ERR("%s: ECONNRESET", str);
	else if (error == EINTR)
			LOG_ERR("%s: EINTR", str);
	else if (error == EINVAL)
			LOG_ERR("%s: EINVAL", str);
	else if (error == ENOTCONN)
			LOG_ERR("%s: ENOTCONN", str);
	else if (error == ENOTSOCK)
			LOG_ERR("%s: ENOTSOCK", str);
	else if (error == EOPNOTSUPP)
			LOG_ERR("%s: EOPNOTSUPP", str);
	else if (error == ETIMEDOUT)
			LOG_ERR("%s: ETIMEDOUT", str);
	else if (error == EIO)
			LOG_ERR("%s: EIO", str);
	else if (error == ENOBUFS)
			LOG_ERR("%s: ENOBUFS", str);
	else if (error == ENOMEM)
			LOG_ERR("%s: ENOMEM", str);
}

static void setblocking(int fd, bool val)
{
  int fl, res;

  fl = fcntl(fd, F_GETFL, 0);
  if (fl == -1) {
    LOG_ERR("fcntl(F_GETFL): %d", errno);
  }

  if (val) {
    fl &= ~O_NONBLOCK;
  } else {
    fl |= O_NONBLOCK;
  }

  res = fcntl(fd, F_SETFL, fl);
  if (fl == -1) {
    LOG_ERR("fcntl(F_SETFL): %d", errno);
  }
}

int pollfds_add(int fd)
{
  int i;
  if (pollnum < NUM_FDS) {
    i = pollnum++;
  } else {
    for (i = 0; i < NUM_FDS; i++) {
      if (pollfds[i].fd < 0) {
        goto found;
      }
    }

    return -1;
  }

  found:
    pollfds[i].fd = fd;
  pollfds[i].events = POLLIN;

  return 0;
}

void pollfds_del(int fd)
{
  for (int i = 0; i < pollnum; i++) {
    if (pollfds[i].fd == fd) {
      pollfds[i].fd = -1;
      break;
    }
  }
}

void async_tcp_server_thread() {
	int res;
	static int counter;
	int num_servs = 0;
	int sock;
	struct sockaddr_in server_addr = {
		.sin_family = AF_INET,
		.sin_port = htons(3682),
		.sin_addr = {
			.s_addr = htonl(INADDR_ANY),
		},
	};

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) {
		error_no("socket", errno);
		exit(1);
	}

	res = bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (res == -1) {
		error_no("bind", errno);
	}
	num_servs++;

	setblocking(sock, false);
	listen(sock, 5);
	pollfds_add(sock);

	// Bytes to send to the HMI are stored here
	uint8_t buffer[hmi_server_message_size];
	// Connect the stream to the buffer
	pb_ostream_t ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));

	// Static members of hmi_server_msg that only to be set once on each start
	hmi_server_msg.which_payload = hmi_server_message_hmi_client_msg_tag;
	hmi_server_msg.payload.hmi_client_msg.boot_count = eeprom_data.boot_count;
	hmi_server_msg.payload.hmi_client_msg.serial_number.size = sizeof(eeprom_data.serial_number);
	memcpy(&hmi_server_msg.payload.hmi_client_msg.serial_number.bytes, &eeprom_data.serial_number,
		sizeof(hmi_server_msg.payload.hmi_client_msg.serial_number.bytes));
	hmi_server_msg.payload.hmi_client_msg.mac_address.size = sizeof(eeprom_data.mac_address);
	memcpy(&hmi_server_msg.payload.hmi_client_msg.mac_address.bytes, &eeprom_data.mac_address,
		sizeof(hmi_server_msg.payload.hmi_client_msg.mac_address.bytes));
	hmi_server_msg.payload.hmi_client_msg.port = eeprom_data.port;
	hmi_server_msg.payload.hmi_client_msg.ip_address.size = sizeof(eeprom_data.ip_address);
	memcpy(&hmi_server_msg.payload.hmi_client_msg.ip_address.bytes, &eeprom_data.ip_address,
		sizeof(hmi_server_msg.payload.hmi_client_msg.ip_address.bytes));
	hmi_server_msg.payload.hmi_client_msg.subnet_mask.size = sizeof(eeprom_data.subnet_mask);
	memcpy(&hmi_server_msg.payload.hmi_client_msg.subnet_mask.bytes, &eeprom_data.subnet_mask,
		sizeof(hmi_server_msg.payload.hmi_client_msg.subnet_mask.bytes));
	hmi_server_msg.payload.hmi_client_msg.hmi_ip_address.size = sizeof(eeprom_data.hmi_ip_address);
	memcpy(&hmi_server_msg.payload.hmi_client_msg.hmi_ip_address.bytes, &eeprom_data.hmi_ip_address,
		sizeof(hmi_server_msg.payload.hmi_client_msg.hmi_ip_address.bytes));
	hmi_server_msg.payload.hmi_client_msg.hmi_port = eeprom_data.hmi_port;
	hmi_server_msg.payload.hmi_client_msg.action = action_t_ACTION_NONE;
	hmi_server_msg.payload.hmi_client_msg.state = state_t_STATE_IDLE;
	hmi_server_msg.payload.hmi_client_msg.major_version = MAJOR_VERSION;
	hmi_server_msg.payload.hmi_client_msg.minor_version = MINOR_VERSION;
	hmi_server_msg.payload.hmi_client_msg.patch_version = PATCH_VERSION;
	// If any of these two change during operation, GPIO interrupt handler will take care of updating these.
	hmi_server_msg.payload.hmi_client_msg.vraw24 = gpio_pin_get_dt(&vraw24_spec);
	hmi_server_msg.payload.hmi_client_msg.aux24v = gpio_pin_get_dt(&aux24v_spec);

	// Set the response message
	hmi_server_response.which_payload = hmi_server_message_hmi_server_response_tag;
	hmi_server_response.payload.hmi_server_response = hmi_server_response_t_RESPONSE_UNKNOWN;

	LOG_INF("Starting async server on port %d", eeprom_data.port);

	// Out local copy of the server message to the HMI
	hmi_server_message hmi_server_msg_cpy;

	while (1) {
		struct sockaddr_storage client_addr;
		socklen_t client_addr_len = sizeof(client_addr);
		char addr_str[32];

		res = poll(pollfds, pollnum, 50);
		if (res == -1) {
			error_no("poll", errno);
			continue;
		}

		// Copy the global message to the local stack, otherwise we can have issues with pb_encode
		// when the GPIO interrupt handler updates the status indicators.
		memcpy(&hmi_server_msg_cpy, &hmi_server_msg, sizeof(hmi_server_message));

		// Send a hmi_server_message to each client
		for (int i = 0; i < pollnum; i++) {
			int fd = pollfds[i].fd;
			// Some of these aren't actually connected clients
			if (pollfds[i].fd != -1) {
				// Encode the hmi_server_message obj into the buffer to send to the HMI
				if (pb_encode(&ostream, hmi_server_message_fields, &hmi_server_msg_cpy)) {
					// Send to HMI
					send(pollfds[i].fd, buffer, ostream.bytes_written, 0);
					// Reinitialize the stream
					ostream = pb_ostream_from_buffer(buffer, hmi_server_message_size);
				} else {
					LOG_ERR("Failed to encode protobuf message: %s", PB_GET_ERROR(&ostream));
				}
			}

			// Continue only on incoming events
			if (!(pollfds[i].revents & POLLIN)) {
				continue;
			}

			if (i < num_servs) {
				/* If server socket */
				int client = accept(fd, (struct sockaddr *)&client_addr, &client_addr_len);
				void *addr = &((struct sockaddr_in *)&client_addr)->sin_addr;

				if (client < 0) {
					error_no("accept", errno);
					continue;
				}
				inet_ntop(client_addr.ss_family, addr, addr_str, sizeof(addr_str));
				LOG_INF("Connection #%d from %s:%d fd=%d", counter++, addr_str,
					((struct sockaddr_in *)&client_addr)->sin_port, client);
				if (pollfds_add(client) < 0) {
					LOG_WRN("Too many connections!");
					static char msg[] = "Too many connections!\n";

					res = send(client, msg, sizeof(msg) - 1, 0);
					if (res < 0) {
						error_no("send", errno);
					}
					close(client);
				} else {
					setblocking(client, false);
				}
			} else {
				char buf[128];
				int len = recv(fd, buf, sizeof(buf), 0);
				if (len <= 0) {
					if (len < 0) {
						error_no("recv", errno);
					}
error:
					pollfds_del(fd);
					close(fd);
					LOG_INF("Connection fd=%d closed", fd);
				} else {
					// When we are in here, we received something from the HMI client
					// Figure out what they sent us and put into a processing queue (shape, actions, etc.)
					int out_len;
					const char *p;
					/*
					 * We implement semi-async server, where reads are async, but writes
					 * *can* be sync (blocking). Note that in majority of cases they expected
					 * to not block, but to be robust, we handle all possibilities.
					 */
					setblocking(fd, true);
					// This for loop echos back what came in from the client
					// I will remove this very soon
					LOG_DBG("Received %d bytes from fd=%d", len, fd);
					hmi_server_response.payload.hmi_server_response = hmi_server_response_t_RESPONSE_SUCCESS;
					// Encode the hmi_server_message obj into the buffer to send to the HMI
					if (pb_encode(&ostream, hmi_server_message_fields, &hmi_server_response)) {
						// Send to HMI
						out_len = send(fd, buffer, ostream.bytes_written, 0);

						if (out_len < 0) {
							error_no("send", errno);
							goto error;
						}

						// Reinitialize the stream
						ostream = pb_ostream_from_buffer(buffer, hmi_server_message_size);
					} else {
						LOG_ERR("Failed to encode protobuf message: %s", PB_GET_ERROR(&ostream));
					}

					// for (p = buf; len; len -= out_len) {
					//
					//	out_len = send(fd, p, len, 0);
					// 	if (out_len < 0) {
					// 		error_no("send", errno);
					// 		goto error;
					// 	}
					// 	p += out_len;
					// }
					setblocking(fd, false);
				}
			}
		}
	}
}

#endif //ASYNC_TCP_SERVER_H
