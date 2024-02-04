cmake_minimum_required(VERSION 3.27)

option(CXU_BUILD_TESTS "Build test executable" ON)
option(BUILD_TESTS "Build test executable" OFF)

project(cxurity CXX)
set(CMAKE_CXX_STANDARD 23)
include(FetchContent)


FetchContent_Declare(cxstructs GIT_REPOSITORY https://github.com/gk646/CXStructures.git)
FetchContent_MakeAvailable(cxstructs)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
)
FetchContent_MakeAvailable(raylib)

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



