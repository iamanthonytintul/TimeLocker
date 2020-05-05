cmake_minimum_required(VERSION 3.1)
project(BackEndService)

include_directories(${CMAKE_SOURCE_DIR})
set (CMAKE_CXX_STANDARD 11)
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
add_subdirectory(test)

add_definitions(-DPATH_TO_UPLOADS="${PROJECT_SOURCE_DIR}/uploads/")



include_directories(${PROJECT_SOURCE_DIR}/cppcms-1.2.1)
include_directories(${PROJECT_SOURCE_DIR}/library/includes)
include_directories(${PROJECT_SOURCE_DIR}/library/source)
include_directories(${PROJECT_SOURCE_DIR}/BackendService)
include_directories(${PROJECT_SOURCE_DIR}/src)

find_library(LIB_BOOSTER booster)
find_library(LIB_CPPCMS cppcms)
find_path(INC_BOOSTER booster/config.h)
find_path(INC_CPPCMS cppcms/config.h)
include_directories(${INC_BOOSTER})
include_directories(${INC_CPPCMS})

set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR ${PROJECT_SOURCE_DIR}/mysql-connector-cpp)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib)




add_library(BackendLogicLibrary STATIC library/source/src.cpp)
add_library(BackendServiceLibrary STATIC BackendService/src/WebSite.cpp)

add_executable(FileService src/main.cpp)

target_link_libraries(FileService mysqlcppconn)
target_link_libraries(FileService ${LIB_CPPCMS})
target_link_libraries(FileService ${LIB_BOOSTER})
