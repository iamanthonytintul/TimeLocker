cmake_minimum_required(VERSION 3.15)
project(TLConsoleApplication)

set(CMAKE_CXX_STANDARD 14)
include_directories(include)

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)


add_executable(TLConsoleApplication src/main.cpp lib/ConsoleApplication.cpp)

enable_testing()
add_subdirectory(test)