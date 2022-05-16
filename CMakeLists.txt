cmake_minimum_required(VERSION 3.10)

project(CurrencyConverter VERSION 0.1)

configure_file(CurrencyConverter.h.in CurrencyConverter.h)

set(CMAKE_AUTOMOC ON)

find_package(PkgConfig)

add_subdirectory(Fetcher)
add_subdirectory(UI)

add_executable(CurrencyConverter main.cpp)
target_link_libraries(CurrencyConverter PRIVATE UI)

target_include_directories(CurrencyConverter PRIVATE
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/Fetcher"
                           "${PROJECT_SOURCE_DIR}/UI"
                           )

target_compile_options(CurrencyConverter PRIVATE -Werror)
target_compile_features(CurrencyConverter PRIVATE cxx_std_11)
