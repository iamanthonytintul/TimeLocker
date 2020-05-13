cmake_minimum_required(VERSION 3.15)
project(TLConsoleApplication)

set(CMAKE_CXX_STANDARD 17
include_directories(include)
file(GLOB libs_models "${PROJECT_SOURCE_DIR}/lib/Models/*.cpp")
file(GLOB libs_boost "${PROJECT_SOURCE_DIR}/lib/BoostNetworkClient/*.cpp")
file(GLOB libs_views_download_upload "${PROJECT_SOURCE_DIR}/lib/Views/pages/download/*.cpp" "${PROJECT_SOURCE_DIR}/lib/Views/pages/upload/*.cpp")
file(GLOB libs_views "${PROJECT_SOURCE_DIR}/lib/Views/pages/*.cpp")
file(GLOB libs_views_err "${PROJECT_SOURCE_DIR}/lib/Views/*.cpp")
file(GLOB libs_presenter "${PROJECT_SOURCE_DIR}/lib/Presenters/*.cpp")
file(GLOB headers "${PROJECT_SOURCE_DIR}/include/*.h" "${PROJECT_SOURCE_DIR}/include/*.hpp")

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

add_executable(TLConsoleApplication src/main.cpp ${headers} ${libs_boost} ${libs_models} ${libs_views} ${libs_presenter} ${libs_views_err} ${libs_views_download_upload} )

target_link_libraries(TLConsoleApplication pthread)
enable_testing()
add_subdirectory(test)