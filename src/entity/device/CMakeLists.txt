file(GLOB_RECURSE DEVICE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(device STATIC ${DEVICE_FILES})

target_include_directories(device PUBLIC "${CMAKE_SOURCE_DIR}/src/include")
