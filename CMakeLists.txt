cmake_minimum_required(VERSION 3.10)

project(CurrencyConverter VERSION 0.1)

configure_file(CurrencyConverter.h.in CurrencyConverter.h)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

add_subdirectory(Fetcher)

add_executable(CurrencyConverter main.cpp)

target_link_libraries(CurrencyConverter PUBLIC Fetcher ${CURL_LIBRARIES})

target_include_directories(CurrencyConverter PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/Fetcher"
                           )