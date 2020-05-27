include_directories(../googletest-src/googlemock/include/gmock/)
set (CMAKE_CXX_STANDARD 17)
file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main.cpp")

add_definitions(-DPATH_TO_UPLOADS="${PROJECT_SOURCE_DIR}/uploads/")
add_definitions(-DPATH_TO_DB_CONFIG="${PROJECT_SOURCE_DIR}/src/configs/database.config"
        -DPATH_TO_STRING_CREATOR="${PROJECT_SOURCE_DIR}/src/configs/stringCreator.config")
add_definitions(-DPATH_TO_FILE_LOGS="${PROJECT_SOURCE_DIR}/test/log_files/")
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

file (GLOB source
        "${PROJECT_SOURCE_DIR}/BackendService/src/WebSite.cpp"
        "${PROJECT_SOURCE_DIR}/library/source/*.cpp")


foreach(file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${sources}
            ${file}
            "${PROJECT_SOURCE_DIR}/test/main.cpp" ${source})
    target_link_libraries("${name}_tests" gtest_main gmock ${LIB_CPPCMS} ${LIB_BOOSTER} mysqlcppconn)
    add_dependencies("${name}_tests" view)
    set (CMAKE_CXX_STANDARD 17)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs -ftest-coverage -Wall -Werror -Wpedantic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()