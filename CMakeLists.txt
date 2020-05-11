cmake_minimum_required(VERSION 3.1)
project(BackEndService)



include_directories(${CMAKE_SOURCE_DIR})
option(STATIC_VIEW "Build Static View instead of dynamically loaded one" OFF)
set (CMAKE_CXX_STANDARD 14)
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

#library
find_library(LIB_BOOSTER booster)
find_library(LIB_CPPCMS cppcms)
find_program(EXE_TMPL_CC cppcms_tmpl_cc)

#path
find_path(INC_BOOSTER booster/shared_ptr.h)
find_path(INC_CPPCMS cppcms/application.h)

#include
include_directories(${INC_BOOSTER})
include_directories(${INC_CPPCMS})

include_directories(${PROJECT_SOURCE_DIR}/cppcms-1.2.1)
include_directories(${PROJECT_SOURCE_DIR}/library/includes)
include_directories(${PROJECT_SOURCE_DIR}/library/source)
include_directories(${PROJECT_SOURCE_DIR}/BackendService)
include_directories(${PROJECT_SOURCE_DIR}/BackendService/template)
include_directories(${PROJECT_SOURCE_DIR}/src)

set(TEMPLATES BackendService/template)

#mysql
set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR ${PROJECT_SOURCE_DIR}/mysql-connector-cpp)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib)

add_executable(FileService src/main.cpp library/source/src.cpp BackendService/src/WebSite.cpp)

#templates
set(VIEW_TEMPLATES ${TEMPLATES}/PostForm.tmpl ${TEMPLATES}/GetForm.tmpl ${TEMPLATES}/PostResponse.tmpl)
set(VIEW_SRC "${CMAKE_CURRENT_BINARY_DIR}/view.cpp")
add_custom_command(
        OUTPUT ${VIEW_SRC}
        COMMAND ${EXE_TMPL_CC}
        -s "view"
        ${TMPL_CC_PARAMS}
        -o ${VIEW_SRC}
        ${VIEW_TEMPLATES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${VIEW_TEMPLATES})
add_library(view SHARED ${CMAKE_CURRENT_BINARY_DIR}/view.cpp)

add_dependencies(FileService view)


target_link_libraries(FileService ${LIB_BOOSTER} ${LIB_CPPCMS} mysqlcppconn)