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

#ifndef EEPROM_H
#define EEPROM_H
#include "eeprom_data_map_t.h"

const struct device *eeprom;
struct eeprom_data_map_t eeprom_data;

bool is_valid_private_ip4_address(uint8_t ip[3]) {
  // Class A: 10.0.0.0 through 10.255.255.255 (8)
  // Class B: 172.16.0.0 through 172.31.255.255 (12)
  // Class C: 192.168.0.0 through 192.168.255.255 (16)
  return (ip[0] == 10 ||
    (ip[0] == 172 && ip[1] == 16) ||
    (ip[0] == 192 && ip[1] == 168));
}

bool is_valid_port(uint16_t port) {
  // Only registered user ports
  return (port >= 1024 && port <= 49151);
}

void init_eeprom(){
  int err;
  eeprom = DEVICE_DT_GET(DT_ALIAS(eeprom_0));
  if (!device_is_ready(eeprom))
    LOG_ERR("EEPROM not ready!");

  if (!eeprom)
    LOG_ERR("EEPROM device not found!");

  err = eeprom_read(eeprom, 0, &eeprom_data, sizeof(eeprom_data));

  if (err)
    LOG_ERR("EEPROM read failed!");

  if (eeprom_data.magic_header != 0xDEADBEEF) {
    LOG_WRN("EEPROM magic header not valid!");
    eeprom_data.magic_header = 0xDEADBEEF;
    eeprom_data.boot_count = 0;

    // Serial number format: We need to establish a serial number format + a method to change it
    for (int i = 0; i < sizeof(eeprom_data.serial_number); i++)
      eeprom_data.serial_number[i] = 0; // 0's for now

    eeprom_data.ip_address[0] = 192;
    eeprom_data.ip_address[1] = 168;
    eeprom_data.ip_address[2] = 1;
    eeprom_data.ip_address[3] = 36;

    eeprom_data.subnet_mask[0] = 255;
    eeprom_data.subnet_mask[1] = 255;
    eeprom_data.subnet_mask[2] = 255;
    eeprom_data.subnet_mask[3] = 0;

    // Arduino AG first 3 bytes assigned: A8:61:0A
    eeprom_data.mac_address[0] = 0xA8;
    eeprom_data.mac_address[1] = 0x61;
    eeprom_data.mac_address[2] = 0x0A;
    eeprom_data.mac_address[3] = sys_rand8_get();
    eeprom_data.mac_address[4] = sys_rand8_get();
    eeprom_data.mac_address[5] = sys_rand8_get();

    eeprom_data.port = 9214;

    eeprom_data.hmi_ip_address[0] = 192;
    eeprom_data.hmi_ip_address[1] = 168;
    eeprom_data.hmi_ip_address[2] = 1;
    eeprom_data.hmi_ip_address[3] = 184;

    eeprom_data.hmi_port = 43669;

    // Write default values into eeprom
    err = eeprom_write(eeprom, 0, &eeprom_data, sizeof(eeprom_data));
    if (err)
      LOG_ERR("EEPROM init write failed!");
    else
      LOG_INF("EEPROM initialized!");
  } else {

    // Increase our boot count
    eeprom_data.boot_count++;

    // Commit boot_count increase into eeprom
    eeprom_write(eeprom, 0, &eeprom_data, sizeof(eeprom_data));

    LOG_INF("EEPROM: Boot Counter: %d", eeprom_data.boot_count);
    LOG_INF("EEPROM: Serial Number: %d%d%d%d%d%d%d%d%d%d%d%d%d%d", eeprom_data.serial_number[0],
      eeprom_data.serial_number[1], eeprom_data.serial_number[2], eeprom_data.serial_number[3],
      eeprom_data.serial_number[4], eeprom_data.serial_number[5], eeprom_data.serial_number[6],
      eeprom_data.serial_number[7], eeprom_data.serial_number[8], eeprom_data.serial_number[9],
      eeprom_data.serial_number[10], eeprom_data.serial_number[11], eeprom_data.serial_number[12],
      eeprom_data.serial_number[13]);
    LOG_INF("EEPROM: MAC Address: %02X:%02X:%02X:%02X:%02X:%02X", eeprom_data.mac_address[0],
      eeprom_data.mac_address[1], eeprom_data.mac_address[2],
      eeprom_data.mac_address[3], eeprom_data.mac_address[4],
      eeprom_data.mac_address[5]);
    LOG_INF("EEPROM: IP Address: %d.%d.%d.%d", eeprom_data.ip_address[0], eeprom_data.ip_address[1],
      eeprom_data.ip_address[2], eeprom_data.ip_address[3]);
    LOG_INF("EEPROM: Subnet Mask: %d.%d.%d.%d", eeprom_data.subnet_mask[0], eeprom_data.subnet_mask[1],
      eeprom_data.subnet_mask[2], eeprom_data.subnet_mask[3]);
    LOG_INF("EEPROM: Port: %d", eeprom_data.port);
    LOG_INF("EEPROM: HMI IP Address: %d.%d.%d.%d", eeprom_data.hmi_ip_address[0],
      eeprom_data.hmi_ip_address[1], eeprom_data.hmi_ip_address[2], eeprom_data.hmi_ip_address[3]);
    LOG_INF("EEPROM: HMI Port: %d", eeprom_data.hmi_port);
  }
}
#endif //EEPROM_H
