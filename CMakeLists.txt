project(ga)
cmake_minimum_required(VERSION 2.8)
file(GLOB SRC_LIST "*.h" "*.cpp")
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

