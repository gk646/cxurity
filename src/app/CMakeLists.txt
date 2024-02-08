file(GLOB_RECURSE APP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(app STATIC ${APP_FILES})

target_include_directories(app PUBLIC "${CMAKE_SOURCE_DIR}/src/include")
