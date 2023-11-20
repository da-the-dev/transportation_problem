cmake_minimum_required(VERSION 3.9.1)
project(Interior_points)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(SOURCES main.cpp
  transportation_matrix.cpp
  bfs_generator.cpp
  russell.cpp
  )
add_executable(transport ${SOURCES})
