file(GLOB tests "${PROJECT_SOURCE_DIR}/test/*.cpp"
                "${PROJECT_SOURCE_DIR}/test/storageTests/*.cpp")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_STANDARD 14)
include_directories(${PROJECT_SOURCE_DIR}/library ${PROJECT_SOURCE_DIR}/src)

set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR ~/mysql-connector-cpp)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib)

foreach(file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${sources}
            ${file}
            "${PROJECT_SOURCE_DIR}/test/main.cpp")
    target_link_libraries("${name}_tests" gtest_main gmock mysqlcppconn)
    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()