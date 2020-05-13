file(GLOB tests "${PROJECT_SOURCE_DIR}/test/ReaderTest.cpp")
#list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/test/main.cpp")

include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/test/path/to)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_STANDARD 14)

add_definitions(-DVALID_PASSWORD_TEST="${PROJECT_SOURCE_DIR}/test/path/to/passwordTests/ValidPasswordTest"
        -DTOO_LONG_PASSWORD_TEST="${PROJECT_SOURCE_DIR}/test/path/to/passwordTests/TooLongPasswordTest"
        -DTOO_SHORT_PASSWORD_TEST="${PROJECT_SOURCE_DIR}/test/path/to/passwordTests/TooShortPasswordTest")

add_definitions(-DVALID_FILE_PATH_TEST="${PROJECT_SOURCE_DIR}/test/path/to/filePathTests/ValidFilePathTest"
        -DNO_SUCH_FILE_TEST="${PROJECT_SOURCE_DIR}/test/path/to/filePathTests/NoSuchFileTest")

add_definitions(-DDOWNLOAD_ARGUMENT_TEST="${PROJECT_SOURCE_DIR}/test/path/to/argumentHandlerTests/DownloadArgumentTest"
        -DUPLOAD_ARGUMENT_TEST="${PROJECT_SOURCE_DIR}/test/path/to/argumentHandlerTests/UploadArgumentTest"
        -DNO_ARGUMENTS_TEST="${PROJECT_SOURCE_DIR}/test/path/to/argumentHandlerTests/NoArgumentsTest"
        -DINVALID_COUNT_OF_ARGUMENTS_TEST="${PROJECT_SOURCE_DIR}/test/path/to/argumentHandlerTests/InvalidCountOfArgumentsTest")

add_definitions(-DVALID_DOWNLOAD_TEST="${PROJECT_SOURCE_DIR}/test/path/to/downloadManagerTests/ValidDownloadTest"
              -DINVALID_DOWNLOAD_TEST="${PROJECT_SOURCE_DIR}/test/path/to/downloadManagerTests/InvalidDownloadTest")

#add_library(ConsoleApplication STATIC ${PROJECT_SOURCE_DIR}/lib/ConsoleApplication.cpp)

foreach (file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${sources}
            ${file}
            "${PROJECT_SOURCE_DIR}/test/main.cpp")
    target_link_libraries("${name}_tests" gtest gmock gmock_main)
    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach ()