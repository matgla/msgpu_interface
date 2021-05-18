add_executable(msgpu_interface_tests)

target_sources(msgpu_interface_tests
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/DataBufferTests.cpp 
)

target_link_libraries(msgpu_interface_tests
    PRIVATE 
        gtest
        gtest_main
)
