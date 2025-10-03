cmake_minimum_required(VERSION 3.13.1)
set(DTC_OVERLAY_FILE "MetalHead.dts")
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(interface-board-zephyr)

list(APPEND CMAKE_MODULE_PATH ${ZEPHYR_BASE}/modules/nanopb)
include(nanopb)

FILE(GLOB proto_sources src/*.proto)
zephyr_nanopb_sources(app ${proto_sources})
add_dependencies(app nanopb_generated_headers)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
