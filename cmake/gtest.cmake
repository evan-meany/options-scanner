if (TARGET GTest::gtest_main OR TARGET gtest_main)
    return()
endif()

set(GTEST_SRC "${CMAKE_SOURCE_DIR}/dep/googletest")
if (EXISTS "${GTEST_SRC}/CMakeLists.txt")
    add_subdirectory("${GTEST_SRC}" EXCLUDE_FROM_ALL)
else()
    message(FATAL_ERROR "googletest submodule missing at ${GTEST_SRC}. "
        "Run: git submodule update --init --recursive")
endif()
