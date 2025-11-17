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

#ifndef EEPROM_DATA_MAP_T_H
#define EEPROM_DATA_MAP_T_H

struct __packed eeprom_data_map_t { // __packed tells the compiler not to add padding
  // Warning: Do not reorder the following variables, insert new variables, delete them, or change their data type!
  // You may only add as instructed below.
  uint32_t magic_header; // A magic header will tell us if the eeprom has been initiated/valid content
  uint32_t boot_count;
  uint8_t serial_number[14];
  uint8_t ip_address[4];
  uint8_t subnet_mask[4];
  uint8_t mac_address[6];
  uint16_t port;
  uint8_t hmi_ip_address[4];
  uint16_t hmi_port;
  // Place new variables to store into EEPROM below.
  // Once our product has been rolled out into the public, our data structure must respect them or bad things happen!
  // If a variable becomes obsolete, DO NOT DELETE OR CHANGE ITS DATA TYPE, you may rename it.
};

#endif //EEPROM_DATA_MAP_T_H
