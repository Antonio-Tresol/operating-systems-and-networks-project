cmake_minimum_required(VERSION 3.16)
project(pi-redes-sistemas-operativos)
find_package(OpenSSL REQUIRED)

# Set common settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

# Add common as library
set(COMMON_DIR lego-common/main)
set(COMMON_SOURCES_DIR ${COMMON_DIR}/src)
set(COMMON_INCLUDE_DIR ${COMMON_DIR}/include)
file(GLOB_RECURSE COMMON_SOURCES "${COMMON_SOURCES_DIR}/*.cpp")

add_library(lego-common ${COMMON_SOURCES})
target_include_directories(lego-common PUBLIC ${COMMON_INCLUDE_DIR})
target_link_libraries(lego-common OpenSSL::SSL OpenSSL::Crypto)

# Subprojects
# add_subdirectory(lego-proxy)
add_subdirectory(lego-client)
add_subdirectory(lego-server)