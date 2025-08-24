cmake_minimum_required(VERSION 3.16)
project(quant-scan VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_CLI "Build the CLI app" ON)
option(BUILD_GUI "Build the GUI app (ImGui)" ON)

add_library(quant_scan_lib STATIC src/quant_scan.cpp )
target_include_directories(quant_scan_lib PUBLIC ${CMAKE_SOURCE_DIR}/include )
target_compile_features(quant_scan_lib PUBLIC cxx_std_20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(ImGui)

add_subdirectory(app)
