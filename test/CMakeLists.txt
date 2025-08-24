cmake_minimum_required(VERSION 3.20)

add_executable(quant-scan-tests
    ${CMAKE_SOURCE_DIR}/test/core/test_date.cpp
)

target_link_libraries(quant-scan-tests
    PRIVATE
    quant_scan_lib
    GTest::gtest_main
)

target_compile_features(quant-scan-tests PRIVATE cxx_std_20)

include(GoogleTest)
gtest_discover_tests(quant-scan-tests)
