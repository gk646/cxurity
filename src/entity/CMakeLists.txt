add_subdirectory(data)
add_subdirectory(device)
add_subdirectory(ml)

add_library(entity "Entity.cpp")
target_link_libraries(entity data device ml)
target_include_directories(entity PUBLIC "${CMAKE_SOURCE_DIR}/src/include")
