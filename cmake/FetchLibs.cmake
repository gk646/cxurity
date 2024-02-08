# Fetch cxstructs
FetchContent_Declare(cxstructs GIT_REPOSITORY https://github.com/gk646/CXStructures.git)
FetchContent_MakeAvailable(cxstructs)

# Fetch raylib
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG 5.0)
FetchContent_MakeAvailable(raylib)

# Download raygui header
set(RAYGUI_URL "https://raw.githubusercontent.com/raysan5/raygui/master/src/raygui.h")
set(RAYGUI_HEADER "${CMAKE_SOURCE_DIR}/src/include/raygui/raygui.h")
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
    set(STYLE_HEADER "${CMAKE_SOURCE_DIR}/src/include/raygui/style_${STYLE_NAME}.h")
    download_file(${STYLE_URL} ${STYLE_HEADER})
endforeach ()

