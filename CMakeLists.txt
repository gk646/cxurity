cmake_minimum_required(VERSION 3.28)
project(cxurity CXX CUDA)
set(CMAKE_CXX_STANDARD 23)
include(FetchContent)

set(CMAKE_CUDA_STANDARD 11)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

if (WIN32)
    set(USER_HOME $ENV{USERPROFILE})
else ()
    set(USER_HOME $ENV{HOME})
endif ()

set(Torch_DIR "${USER_HOME}/Documents/Libaries/libtorch/share/cmake/Torch")


# Fetch cxstructs
FetchContent_Declare(cxstructs GIT_REPOSITORY https://github.com/gk646/CXStructures.git)
FetchContent_MakeAvailable(cxstructs)

# Fetch raylib
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG 5.0)
FetchContent_MakeAvailable(raylib)

# Download raygui header
set(RAYGUI_URL "https://raw.githubusercontent.com/raysan5/raygui/master/src/raygui.h")
set(RAYGUI_HEADER "${CMAKE_BINARY_DIR}/raygui.h")
if (NOT EXISTS "${RAYGUI_HEADER}")
    message(STATUS "Downloading raygui.h from ${RAYGUI_URL}")
    file(DOWNLOAD ${RAYGUI_URL} ${RAYGUI_HEADER} TIMEOUT 60 TLS_VERIFY ON SHOW_PROGRESS)
endif ()

# Function to download style files
function(download_file url dest)
    if (NOT EXISTS "${dest}")
        message(STATUS "Downloading ${dest} from ${url}")
        file(DOWNLOAD ${url} ${dest} TIMEOUT 60 TLS_VERIFY ON SHOW_PROGRESS)
    endif ()
endfunction()

# Download style files
set(STYLES_BASE_URL "https://raw.githubusercontent.com/raysan5/raygui/master/examples/styles")
set(STYLE_NAMES jungle candy lavanda cyber terminal ashes bluish dark cherry sunny enefete)
foreach (STYLE_NAME IN LISTS STYLE_NAMES)
    set(STYLE_URL "${STYLES_BASE_URL}/style_${STYLE_NAME}.h")
    set(STYLE_HEADER "${CMAKE_BINARY_DIR}/style_${STYLE_NAME}.h")
    download_file(${STYLE_URL} ${STYLE_HEADER})
endforeach ()

include_directories(${CMAKE_BINARY_DIR})

# Compiler-specific options for static linking
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
elseif (MSVC)
endif ()

# Source files
file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/*.h" "src/*.hpp")

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")


add_executable(cxurity ${SRC_FILES})

target_include_directories(cxurity PRIVATE "src/common")

# Comment when compiling the standalone executable
target_compile_definitions(cxurity PRIVATE CXU_COMPILE_DEBUG)
target_precompile_headers(cxurity PRIVATE src/headers/pch.h)

# Platform-specific configurations
if (WIN32)
    target_compile_definitions(cxurity PRIVATE CXU_HOST_SYSTEM_WIN)
    target_link_libraries(cxurity Kernel32 cxstructs raylib Psapi Iphlpapi advapi32 dwmapi "${TORCH_LIBRARIES}")

    #file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
    #add_custom_command(TARGET cxurity POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TORCH_DLLS} ${CMAKE_BINARY_DIR})

elseif (UNIX)
    target_compile_definitions(cxurity PRIVATE CXU_HOST_SYSTEM_UNIX)
endif ()
