cmake_minimum_required(VERSION 3.20)
project(quant-scan VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project options
option(BUILD_CLI "Build the CLI app" ON)
option(BUILD_GUI "Build the GUI app (ImGui)" ON)
option(BUILD_TESTS "Build tests" ON)

# Test the cmake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Include cmakes
include(nlohmann_json)
include(im_gui)

# Build library
add_library(quant_scan_lib STATIC src/quant_scan.cpp )
target_include_directories(quant_scan_lib PUBLIC ${CMAKE_SOURCE_DIR}/include )
target_compile_features(quant_scan_lib PUBLIC cxx_std_20)
target_link_libraries(quant_scan_lib PRIVATE nlohmann_json::nlohmann_json)

# Build exes
add_subdirectory(app)

# Build tests
if (BUILD_TESTS)
    enable_testing()
    include(gtest)
    add_subdirectory(test)
endif()
