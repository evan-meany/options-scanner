include_guard()

# Don’t build glfw extras
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/dep/glfw EXCLUDE_FROM_ALL)

# Provide a consistent alias
if(NOT TARGET GLFW::GLFW)
    add_library(GLFW::GLFW ALIAS glfw)
endif
