cmake_minimum_required(VERSION 3.15)
project(ProblemSolver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ProblemSolver CacheManager.cpp CacheManager.h ClientHandler.h FileCacheManager.cpp FileCacheManager.h MySerialServer.cpp MySerialServer.h MyTestClientHandler.cpp MyTestClientHandler.h Server.h Solver.h)