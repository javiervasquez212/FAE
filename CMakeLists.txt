cmake_minimum_required(VERSION 3.15)
project(FAE C)

find_package(RAYLIB REQUIRED)

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)