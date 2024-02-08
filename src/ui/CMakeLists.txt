file(GLOB_RECURSE GUI_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(gui STATIC ${GUI_FILES})

target_link_libraries(gui PUBLIC raylib)

target_include_directories(gui PUBLIC "${CMAKE_SOURCE_DIR}/src/include")
