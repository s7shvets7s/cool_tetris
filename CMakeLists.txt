cmake_minimum_required(VERSION 3.19)
project(cool_tetris LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core )

add_subdirectory(TetrisClient)
add_subdirectory(TetrisServer)
