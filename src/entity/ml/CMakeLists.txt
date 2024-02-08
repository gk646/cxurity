file(GLOB_RECURSE ML_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_library(ml STATIC ${ML_FILES})

target_include_directories(ml PUBLIC "${CMAKE_SOURCE_DIR}/src/include")
target_include_directories(ml PUBLIC ${TORCH_INCLUDE_DIRS})
