cmake_minimum_required(VERSION 3.9)
project(protobuf-matchers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

set(PROTOBUF_MATCHERS_PROTOBUF_DEFAULT_FETCH_TAG
  "v22.5"
)
set(PROTOBUF_MATCHERS_GTEST_DEFAULT_FETCH_TAG
  "release-1.12.1"
)

# -----------------------------------------------------------------------------
# Options
# -----------------------------------------------------------------------------

option(PROTOBUF_MATCHERS_USE_SYSTEM_PROTOBUF "Use system Protobuf via find_package" ON)
option(PROTOBUF_MATCHERS_FETCH_PROTOBUF "Download Protobuf via FetchContent if not found" ON)
set(PROTOBUF_MATCHERS_PROTOBUF_FETCH_TAG ${PROTOBUF_MATCHERS_PROTOBUF_DEFAULT_FETCH_TAG}
    CACHE STRING "Git tag or commit to use for Protobuf FetchContent")

option(PROTOBUF_MATCHERS_USE_SYSTEM_GTEST "Use system GTest via find_package" ON)
option(PROTOBUF_MATCHERS_FETCH_GTEST "Download GTest via FetchContent if not found" ON)
set(PROTOBUF_MATCHERS_GTEST_FETCH_TAG ${PROTOBUF_MATCHERS_GTEST_DEFAULT_FETCH_TAG}
    CACHE STRING "Git tag or commit to use for GTest FetchContent")

option(PROTOBUF_MATCHERS_BUILD_TESTING "Build the protobuf-matchers tests" ON)

# -----------------------------------------------------------------------------
# Protobuf Dependency
# -----------------------------------------------------------------------------
if(PROTOBUF_MATCHERS_USE_SYSTEM_PROTOBUF)
    find_package(Protobuf)
endif()

if(NOT Protobuf_FOUND AND PROTOBUF_MATCHERS_FETCH_PROTOBUF)
    message(STATUS "Fetching Protobuf version ${PROTOBUF_MATCHERS_PROTOBUF_FETCH_TAG}")
    include(FetchContent)
    set(protobuf_BUILD_TESTS OFF CACHE BOOL "Disable Protobuf tests" FORCE)
    FetchContent_Declare(
        protobuf
        GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
        GIT_TAG        ${PROTOBUF_MATCHERS_PROTOBUF_FETCH_TAG}
    )
    FetchContent_MakeAvailable(protobuf)
    FetchContent_GetProperties(Protobuf SOURCE_DIR Protobuf_SOURCE_DIR)
    # This exists from Protobuf version 22.0 and up.
    include(${Protobuf_SOURCE_DIR}/cmake/protobuf-generate.cmake)
    if(TARGET libprotobuf AND NOT TARGET protobuf::libprotobuf)
        add_library(protobuf::libprotobuf ALIAS libprotobuf)
    endif()
    if(TARGET protoc AND NOT TARGET protobuf::protoc)
        add_executable(protobuf::protoc ALIAS protoc)
    endif()
endif()

if(NOT TARGET protobuf::libprotobuf)
    message(FATAL_ERROR "Protobuf is required but was not found or fetched.")
endif()

# -----------------------------------------------------------------------------
# GTest Dependency
# -----------------------------------------------------------------------------
if(PROTOBUF_MATCHERS_USE_SYSTEM_GTEST)
    find_package(GTest)
endif()

if(NOT GTest_FOUND AND PROTOBUF_MATCHERS_FETCH_GTEST)
    message(STATUS "Fetching googletest version ${PROTOBUF_MATCHERS_GTEST_FETCH_TAG}")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        ${PROTOBUF_MATCHERS_GTEST_FETCH_TAG}
    )
    FetchContent_MakeAvailable(googletest)
    if(TARGET gmock AND NOT TARGET GTest::gmock)
        add_library(GTest::gmock ALIAS gmock)
    endif()
    if(TARGET gmock_main AND NOT TARGET GTest::gmock_main)
        add_library(GTest::gmock_main ALIAS gmock_main)
    endif()
endif()

if(NOT TARGET GTest::gmock)
    message(FATAL_ERROR "GTest is required but was not found or fetched.")
endif()

# -----------------------------------------------------------------------------
# Set up targets
# -----------------------------------------------------------------------------
add_library(protobuf-matchers protobuf-matchers/protocol-buffer-matchers.cc)
target_include_directories(protobuf-matchers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(protobuf-matchers PUBLIC
    protobuf::libprotobuf
    GTest::gmock)

if(PROTOBUF_MATCHERS_BUILD_TESTING)
    include(CTest)
    include(GoogleTest)
    set(PROTO_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
    file(MAKE_DIRECTORY ${PROTO_BINARY_DIR})
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
