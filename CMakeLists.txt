cmake_minimum_required(VERSION 3.15)
project(ProblemSolver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(ProblemSolver CacheManager.h ClientHandler.h FileCacheManager.h MySerialServer.cpp MySerialServer.h MyTestClientHandler.h Server.h Solver.h StringReverse.cpp StringReverse.h Main.h main.cpp Searchable.h Searcher.h State.h BestFirstSearch.h MutualSearches.h MySerialServer.cpp Matrix.cpp Matrix.h Point.h MyClientHandler.h AlgorithmOptions.h SearcherSolver.h Astar.h MyParallelServer.cpp MyParallelServer.h BFS.h DFS.h)