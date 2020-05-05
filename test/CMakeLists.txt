include_directories(../googletest-src/googlemock/include/gmock/)
file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main.cpp")

include_directories(${PROJECT_SOURCE_DIR}/library/includes)
include_directories(${PROJECT_SOURCE_DIR}/library/source)
include_directories(${PROJECT_SOURCE_DIR}/BackendService)
include_directories(${PROJECT_SOURCE_DIR}/cppcms-1.2.1/cppcms)
find_library(LIB_BOOSTER booster)
find_library(LIB_CPPCMS cppcms)
find_path(INC_BOOSTER booster/config.h)
find_path(INC_CPPCMS cppcms/config.h)
include_directories(${INC_BOOSTER})
include_directories(${INC_CPPCMS})

foreach(file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${sources}
            ${file}
            "${PROJECT_SOURCE_DIR}/test/main.cpp")
    target_link_libraries("${name}_tests" gtest_main gmock BackendLogicLibrary BackendServiceLibrary ${LIB_CPPCMS} ${LIB_BOOSTER})
    set (CMAKE_CXX_STANDARD 11)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs -ftest-coverage -Wall -Werror -Wpedantic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()