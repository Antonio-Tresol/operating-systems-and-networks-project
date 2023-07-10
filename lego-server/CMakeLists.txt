cmake_minimum_required(VERSION 3.16)
project(lego-server)
find_package(OpenSSL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

set(MAIN_DIR main)
set(SOURCES_DIR ${MAIN_DIR}/src)
set(INCLUDE_DIR ${MAIN_DIR}/include)

file(GLOB_RECURSE TARGET_SOURCES "${SOURCES_DIR}/*.cpp")

include_directories(${INCLUDE_DIR})
link_libraries(OpenSSL::SSL OpenSSL::Crypto pthread)

set(DEFAULT_TARGET ${PROJECT_NAME})

add_executable(${DEFAULT_TARGET} ${TARGET_SOURCES})

target_link_libraries(${DEFAULT_TARGET} lego-common)