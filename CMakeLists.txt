cmake_minimum_required(VERSION 3.28)
project(cxurity CXX CUDA)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CUDA_STANDARD 11)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

include(FetchContent)

if (WIN32)
    add_compile_definitions(CXU_HOST_SYSTEM_WIN)
    set(USER_HOME $ENV{USERPROFILE})
else ()
    add_compile_definitions(CXU_HOST_SYSTEM_UNIX)
    set(USER_HOME $ENV{HOME})
endif ()


set(Torch_DIR "${USER_HOME}/Documents/Libaries/libtorch/share/cmake/Torch")
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

include(cmake/FetchLibs.cmake)

# Compiler-specific options for static linking
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
elseif (MSVC)
endif ()

# Source files
file(GLOB_RECURSE SRC_FILES "src/main.cpp" "src/entity/*.cpp" "src/entity/*.h" "src/headers/*.cpp" "src/headers/*.h" "src/util/*.h" )



add_subdirectory(src/ui)

add_executable(cxurity ${SRC_FILES})

target_include_directories(cxurity PRIVATE "src/common")

# Comment when compiling the standalone executable
target_compile_definitions(cxurity PRIVATE CXU_COMPILE_DEBUG)

target_precompile_headers(cxurity PRIVATE src/headers/pch.h)

# Platform-specific configurations
if (WIN32)
    target_link_libraries(cxurity gui Kernel32 cxstructs Psapi Iphlpapi advapi32 dwmapi "${TORCH_LIBRARIES}")

    #file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    #add_custom_command(TARGET cxurity POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TORCH_DLLS} ${CMAKE_BINARY_DIR})

elseif (UNIX)
    target_compile_definitions(cxurity PRIVATE CXU_HOST_SYSTEM_UNIX)
endif ()
