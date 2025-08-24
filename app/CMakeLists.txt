# app/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)

project(quant_scan_apps LANGUAGES CXX)

option(BUILD_GUI "Build the GUI app" ON)

# Find your header-only lib target by either name or namespaced alias
if(TARGET quant_scan_lib::quant_scan_lib)
    set(OPTSCAN_LIB quant_scan_lib::quant_scan_lib)
elseif(TARGET quant_scan_lib)
    set(OPTSCAN_LIB quant_scan_lib)
else()
    message(FATAL_ERROR
            "Couldn't find target 'quant_scan_lib' (or quant_scan_lib::quant_scan_lib). "
            "Define it in the top-level CMake before add_subdirectory(app).")
endif()

# ---- CLI ----
add_executable(quant-scan-cli
        ${CMAKE_CURRENT_SOURCE_DIR}/cli/main.cpp
)
target_link_libraries(quant-scan-cli PRIVATE ${OPTSCAN_LIB})
target_compile_features(quant-scan-cli PRIVATE cxx_std_20)

# ---- GUI (optional) ----
add_executable(quant-scan-gui
        ${CMAKE_CURRENT_SOURCE_DIR}/gui/main.cpp
)
target_link_libraries(quant-scan-gui PRIVATE ${OPTSCAN_LIB})
target_compile_features(quant-scan-gui PRIVATE cxx_std_20)

# Optional: on Windows, make it a GUI subsystem app (no console)
# set_target_properties(quant-scan-gui PROPERTIES WIN32_EXECUTABLE YES)
