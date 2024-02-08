file(GLOB_RECURSE DATA_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(data STATIC ${DATA_FILES})

target_include_directories(data PUBLIC "${CMAKE_SOURCE_DIR}/src/include")
target_include_directories(data PUBLIC "${cxstructs_SOURCE_DIR}/include")
