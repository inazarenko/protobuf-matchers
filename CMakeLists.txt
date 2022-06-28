cmake_minimum_required(VERSION 3.9)
project(protobuf-matchers)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

find_package(Protobuf REQUIRED)
find_package(GTest REQUIRED)

add_library(protobuf-matchers protobuf-matchers/protocol-buffer-matchers.cc)
target_include_directories(protobuf-matchers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(protobuf-matchers PUBLIC
    protobuf::libprotobuf
    GTest::gmock)

include(CTest)
include(GoogleTest)
if(BUILD_TESTING)
    protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS protobuf-matchers/test.proto)
    add_executable(protobuf-matchers-test
      protobuf-matchers/protocol-buffer-matchers-test.cc
      ${PROTO_SRCS} ${PROTO_HDRS})
    target_include_directories(protobuf-matchers-test PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    target_link_libraries(protobuf-matchers-test
      protobuf-matchers
      GTest::gmock_main)
    gtest_discover_tests(protobuf-matchers-test)
endif()
