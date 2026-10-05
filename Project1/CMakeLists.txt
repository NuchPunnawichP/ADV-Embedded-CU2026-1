cmake_minimum_required(VERSION 3.22)

# Every Cucumber R/RS/RI/RIS board in scope uses an ESP32-S2.
set(IDF_TARGET "esp32s2" CACHE STRING "ESP-IDF target")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(cucumber_board)
