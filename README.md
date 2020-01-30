# ProblemSolver using searching algorithms - C++ edition

In this project we were asked to build a server which can support 10 clients in parallel. The server recieves clients and gets their problems and returns to the clients solutions in parallel. The server gets a searching problem and solves it by using the A* algorithm - giving the optimal cost to the solution.

# Detailes

Each client, after connecting to the server as mentioned above, sends a problem as a matrix with a starting point and ending point specified in the two last lines. The server directs each client to a client handler that will read the matrix, interprets it and later solves the problem. First, the client handler will check if there is already a solution to the problem stored in one of the cache files and if there is a solution - it will be sent back to the client as the answer to the problem. Otherwise, if there isn't an existing solution, our program uses the best algorithm which found the cheapest path compared to the other algorithms to solve the given searching problem. Afterwards it sends the solution's path back to the client and ends the communication. We tested four different algorithms for a variety of different searching problems. compared the resulting path costs in an empirical experiment. The chosen algorithm that solved the problems with the best results almost each time was the Astar algorithm - considering the findings we chose it from all the other options to be implemented on our project.

# Running the project

In order to start the program you should do the following:

compile all file with commands:

``` 
$ g++‬‬ ‫‪-std=c++14‬‬ */*.cpp ‫‪*.cpp‬‬ ‫‪-Wall‬‬ ‫‪-Wextra‬‬ ‫‪-Wshadow‬‬ ‫‪-Wnon-virtual-dtor‬‬ ‫‪-ped antic‬‬ ‫ ‪-o‬‬a.out-pthread
```

Next, to run a standard - solves matrix using the paraller server:

```
$ ./a.out 5600 //can use another port
```

# So, what now?


To connect as a client to a server, use the following command:
```
$ telnet 127.0.0.1 5600
```

Then, send a mtrix in the following format:

```
 1,3,5
-1,10,8
15,1,9
 0,0
 2,2
 end
 ```
 
this matrix is 3X3, start point is located in the index (0,0) and end is located in the index (2,2).
The command end in a separete line will start the solving process by the program.

- Note: the value (-1) when located as one of the matrix cells, stands for a wall that blocks the path through that cell.

# Authors

:star2: Chen Baadani


:star2: Dana Kreimer
