cmake_minimum_required(VERSION 3.28)
project(cxurity CXX CUDA)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CUDA_STANDARD 11)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

include(FetchContent)

if (WIN32)
    #add_compile_definitions(CXU_HOST_SYSTEM_WIN)
    set(USER_HOME $ENV{USERPROFILE})
else ()
    add_compile_definitions(CXU_HOST_SYSTEM_UNIX)
    set(USER_HOME $ENV{HOME})
endif ()

# Fetches easy dependencies
include(cmake/FetchLibs.cmake)

# Add the subdirectory modules
add_subdirectory(src/ui)
add_subdirectory(src/app)
add_subdirectory(src/entity)

add_executable(cxurity "src/main.cpp")

# Comment when compiling the standalone executable
target_compile_definitions(cxurity PRIVATE CXU_COMPILE_DEBUG)


# Compiler-specific options for static linking
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
elseif (MSVC)
endif ()

# Platform-specific configurations
if (WIN32)
    target_link_libraries(cxurity gui app entity Kernel32 cxstructs Psapi Iphlpapi advapi32 dwmapi)
elseif (UNIX)
    target_link_libraries(cxurity gui app data)
endif ()
