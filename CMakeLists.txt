cmake_minimum_required(VERSION 3.16)
project(tetris CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window)

add_executable(tetris
    Source/DrawText.cpp
    Source/GetTetromino.cpp
    Source/GetWallKickData.cpp
    Source/Main.cpp
    Source/Tetromino.cpp)
target_include_directories(tetris PRIVATE Source/Headers)
target_link_libraries(tetris PRIVATE sfml-graphics sfml-window)
install(TARGETS tetris)
