cmake_minimum_required(VERSION 3.26)

option(CXU_BUILD_TESTS "Build test executable" ON)
option(BUILD_TESTS "Build tests" OFF) #For cxstructs

project(cxurity CXX)
set(CMAKE_CXX_STANDARD 23)
include(FetchContent)


FetchContent_Declare(cxstructs GIT_REPOSITORY https://github.com/gk646/CXStructures.git)
FetchContent_MakeAvailable(cxstructs)

FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG 5.0
)
FetchContent_MakeAvailable(raylib)

set(RAYGUI_URL "https://raw.githubusercontent.com/raysan5/raygui/master/src/raygui.h")
set(RAYGUI_VERSION "4.0")
set(RAYGUI_HEADER "${CMAKE_BINARY_DIR}/raygui.h")

if (NOT EXISTS "${RAYGUI_HEADER}")
    message(STATUS "Downloading raygui.h from ${RAYGUI_URL}")
    file(DOWNLOAD ${RAYGUI_URL} ${RAYGUI_HEADER}
            TIMEOUT 60
            TLS_VERIFY ON
            SHOW_PROGRESS)
endif ()

function(download_file url dest)
    if(NOT EXISTS "${dest}")
        message(STATUS "Downloading ${dest} from ${url}")
        file(DOWNLOAD ${url} ${dest}
                TIMEOUT 60
                TLS_VERIFY ON
                SHOW_PROGRESS)
    endif()
endfunction()

set(STYLES_BASE_URL "https://raw.githubusercontent.com/raysan5/raygui/master/examples/styles")

set(STYLE_NAMES jungle candy lavanda cyber terminal ashes bluish dark cherry sunny enefete)

foreach(STYLE_NAME IN LISTS STYLE_NAMES)
    set(STYLE_URL "${STYLES_BASE_URL}/style_${STYLE_NAME}.h")
    set(STYLE_HEADER "${CMAKE_BINARY_DIR}/style_${STYLE_NAME}.h")
    download_file(${STYLE_URL} ${STYLE_HEADER})
endforeach()

include_directories(${CMAKE_BINARY_DIR})


if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
endif ()


file(GLOB_RECURSE SRC_FILES
        "src/*.cpp"
        "src/*.h"
        "src/*.hpp")

if (CXU_BUILD_TESTS)
    add_executable(cxurity ${SRC_FILES})
else ()
    add_library(cxurity STATIC ${SRC_FILES})
endif ()


if (WIN32)
    target_compile_definitions(cxurity PRIVATE CXU_HOST_SYSTEM_WIN)
endif ()

target_link_libraries(cxurity Kernel32 cxstructs raylib)


