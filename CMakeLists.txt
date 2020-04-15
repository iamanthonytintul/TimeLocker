cmake_minimum_required(VERSION 3.1)
project(BackEndService)

#  GTest
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(backend_server_testing)


include_directories(${PROJECT_SOURCE_DIR}/library/includes)
include_directories(${PROJECT_SOURCE_DIR}/library/source)
include_directories(${PROJECT_SOURCE_DIR}/BackendService)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/cppcms-1.2.1/cppcms)
include_directories(${PROJECT_SOURCE_DIR}/cppcms-1.2.1)

find_library(LIB_BOOSTER booster)
find_library(LIB_CPPCMS cppcms)

add_library(BackendLogicLibrary STATIC library/source/src.cpp)
add_library(BackendServiceLibrary STATIC BackendService/WebSite.cpp)

add_executable(FileService src/main.cpp)

target_link_libraries(FileService BackendLogicLibrary BackendServiceLibrary LIB_BOOSTER)
