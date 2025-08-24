include_guard()

# Build GLAD (OpenGL loader)
# The repo includes a CMake build that creates target 'glad'
set(GLAD_PROFILE  "core" CACHE STRING "")
set(GLAD_API      "gl=3.3" CACHE STRING "")  # tweak if you need different GL
set(GLAD_GENERATOR "c" CACHE STRING "")

add_subdirectory(${CMAKE_SOURCE_DIR}/dep/glad EXCLUDE_FROM_ALL)

if(NOT TARGET GLAD::glad)
    add_library(GLAD::glad ALIAS glad)
endif
