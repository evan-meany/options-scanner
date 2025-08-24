include_guard()

option(IMGUI_BACKENDS "Build ImGui GLFW + OpenGL3 backends" OFF)

set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/dep/imgui")
if(NOT EXISTS "${IMGUI_DIR}/imgui.h")
    message(FATAL_ERROR "ImGui submodule not found at ${IMGUI_DIR}. Run: git submodule update --init --recursive")
endif()

set(IMGUI_CORE_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
)

add_library(imgui STATIC ${IMGUI_CORE_SOURCES})
target_include_directories(imgui PUBLIC ${IMGUI_DIR})
add_library(ImGui::imgui ALIAS imgui)

if(IMGUI_BACKENDS)
    include(GLFW) # defines GLFW::GLFW
    include(GLAD) # defines GLAD::glad
    find_package(OpenGL REQUIRED)

    target_sources(imgui PRIVATE
            ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
            ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
    )
    target_include_directories(imgui PUBLIC ${IMGUI_DIR}/backends)

    # Tell ImGui to use GLAD loader
    target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

    target_link_libraries(imgui PUBLIC
            GLFW::GLFW
            OpenGL::GL
            GLAD::glad
    )

    if(WIN32)
        # On Windows/MinGW, OpenGL is typically 'opengl32' via OpenGL::GL,
        # GLFW pulls in needed system libs. Nothing extra usually required.
    elseif(APPLE)
        find_library(COCOA_FRAMEWORK Cocoa)
        find_library(IOKIT_FRAMEWORK IOKit)
        find_library(COREVIDEO_FRAMEWORK CoreVideo)
        target_link_libraries(imgui PUBLIC ${COCOA_FRAMEWORK} ${IOKIT_FRAMEWORK} ${COREVIDEO_FRAMEWORK})
    else()
        find_package(Threads REQUIRED)
        target_link_libraries(imgui PUBLIC Threads::Threads dl)
    endif()
endif()
