file(GLOB tests "${PROJECT_SOURCE_DIR}/test/ViewTests/*.cpp" "${PROJECT_SOURCE_DIR}/test/PresenterTests/*.cpp" "${PROJECT_SOURCE_DIR}/test/ModelTests/*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/library ${PROJECT_SOURCE_DIR}/test/path/to)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DOUTPUT="${PROJECT_SOURCE_DIR}/test/path/to/outputFile")
add_definitions(-DVALID_FILE_KEY="${PROJECT_SOURCE_DIR}/test/path/to/correct/fileKey")
add_definitions(-DINVALID_FILE_KEY="${PROJECT_SOURCE_DIR}/test/path/to/incorrect/fileKey")
add_definitions(-DVALID_PASSWORD="${PROJECT_SOURCE_DIR}/test/path/to/correct/filePassword")
add_definitions(-DINVALID_PASSWORD="${PROJECT_SOURCE_DIR}/test/path/to/incorrect/filePassword")
add_definitions(-DVALID_FILE_PATH="${PROJECT_SOURCE_DIR}/test/path/to/correct/filePath")
add_definitions(-DINVALID_FILE_PATH="${PROJECT_SOURCE_DIR}/test/path/to/incorrect/filePath")
add_definitions(-DVALID_PASSWORD_PAIR="${PROJECT_SOURCE_DIR}/test/path/to/correct/filePasswordPair")
add_definitions(-DINVALID_PASSWORD_PAIR="${PROJECT_SOURCE_DIR}/test/path/to/incorrect/filePasswordPair")
add_definitions(-DVALID_FILE_LIFETIME="${PROJECT_SOURCE_DIR}/test/path/to/correct/fileLifetime")
add_definitions(-DINVALID_FILE_LIFETIME="${PROJECT_SOURCE_DIR}/test/path/to/incorrect/fileLifetime")
add_definitions(-DVALID_APP_MODE="${PROJECT_SOURCE_DIR}/test/path/to/correct/appMode")
add_definitions(-DINVALID_APP_MODE="${PROJECT_SOURCE_DIR}/test/path/to/incorrect/appMode")
add_definitions(-DDOWNLOAD_SCRIPT="${PROJECT_SOURCE_DIR}/test/path/to/correct/downloadScript")
add_definitions(-DUPLOAD_SCRIPT="${PROJECT_SOURCE_DIR}/test/path/to/correct/uploadScript")

foreach (file ${tests})
    set(name)
    get_filename_component(name ${file} NAME_WE)
    add_executable("${name}_tests"
            ${sources}
            ${file}
            "${PROJECT_SOURCE_DIR}/test/main.cpp")
    target_link_libraries("${name}_tests" gmock gmock_main TLConsoleApp)
    add_test(NAME ${name} COMMAND "${name}_tests")
endforeach ()
