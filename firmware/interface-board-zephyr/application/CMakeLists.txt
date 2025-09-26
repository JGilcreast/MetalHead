cmake_minimum_required(VERSION 3.13.1)
set(DTC_OVERLAY_FILE "MetalHead.dts")
find_package(Zephyr)
project(interface-board-zephyr)

FILE(GLOB app_sources src/*.c*)
target_sources(app PRIVATE ${app_sources})
