cmake_minimum_required(VERSION 3.17)
project(TetrisJet)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS "-fexec-charset=CP949")
add_executable(Tetris main.cpp Tetris.cpp Tetris.h Tetris_Shape.cpp Utility.h )