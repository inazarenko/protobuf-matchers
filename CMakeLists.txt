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
    set(PROTO_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
    add_library(protobuf-matchers-proto OBJECT "${CMAKE_CURRENT_LIST_DIR}/protobuf-matchers/test.proto")
    target_link_libraries(protobuf-matchers-proto PUBLIC protobuf::libprotobuf)
    target_include_directories(protobuf-matchers-proto PUBLIC "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>")
    protobuf_generate(
        TARGET protobuf-matchers-proto
        PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")
    add_executable(protobuf-matchers-test
      protobuf-matchers/protocol-buffer-matchers-test.cc)
    target_link_libraries(protobuf-matchers-test
      protobuf-matchers
      protobuf-matchers-proto
      GTest::gmock_main)
    gtest_discover_tests(protobuf-matchers-test)
endif()
