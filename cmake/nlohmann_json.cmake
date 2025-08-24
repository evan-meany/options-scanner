if (TARGET nlohmann_json::nlohmann_json)
    return()
endif()

set(NLOHMANN_JSON_SRC "${CMAKE_SOURCE_DIR}/dep/nlohmann_json")

if (EXISTS "${NLOHMANN_JSON_SRC}/CMakeLists.txt")
    # Header-only, safe to include directly
    add_subdirectory("${NLOHMANN_JSON_SRC}" EXCLUDE_FROM_ALL)
else()
    message(FATAL_ERROR
        "nlohmann_json submodule not found at ${NLOHMANN_JSON_SRC}. "
        "Did you run 'git submodule update --init --recursive'?")
endif()
