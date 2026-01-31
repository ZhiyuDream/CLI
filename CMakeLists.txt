cmake_minimum_required(VERSION 3.10)
project(todo_cli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(todo_cli
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/todo_item.cpp
  ${SRC_DIR}/storage.cpp
  ${SRC_DIR}/todo_manager.cpp
  ${SRC_DIR}/cmd_parser.cpp
)
target_include_directories(todo_cli PRIVATE ${INC_DIR})
