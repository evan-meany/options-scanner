cmake_minimum_required(VERSION 3.16)
project(options-scanner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(ImGui)  # provides ImGui::imgui

add_executable(options-scanner src/main.cpp)
target_link_libraries(options-scanner PRIVATE ImGui::imgui)

