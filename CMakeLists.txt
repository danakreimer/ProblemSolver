cmake_minimum_required(VERSION 3.15)
project(ProblemSolver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ProblemSolver CacheManager.h ClientHandler.h FileCacheManager.h MySerialServer.cpp MySerialServer.h MyTestClientHandler.h Server.h Solver.h StringReverse.cpp StringReverse.h Main.h main.cpp)