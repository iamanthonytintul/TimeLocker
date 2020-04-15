cmake_minimum_required(VERSION 3.1)
project(TimeLocker)

set(CMAKE_CXX_STANDARD 14)

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

add_executable(TimeLocker src/main.cpp src/storage.cpp)

enable_testing()
add_subdirectory(test)
include_directories(${PROJECT_SOURCE_DIR}/library)
