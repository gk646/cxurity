file(GLOB_RECURSE ML_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")


set(Torch_DIR "${USER_HOME}/Documents/Libaries/libtorch/share/cmake/Torch")
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_library(ml STATIC ${ML_FILES})
target_precompile_headers(ml PRIVATE "${CMAKE_SOURCE_DIR}/src/headers/pch.h")

target_link_libraries(ml "${TORCH_LIBRARIES}")
target_include_directories(ml PUBLIC "${CMAKE_SOURCE_DIR}/src/include")
target_include_directories(ml PUBLIC ${TORCH_INCLUDE_DIRS})


#file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
#add_custom_command(TARGET cxurity POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TORCH_DLLS} ${CMAKE_BINARY_DIR})