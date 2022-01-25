# Electric Vehicle Routing Problem #

### This repository contains algorithms to solve the EVRP (Electric Vehicle Routing Problem) in C++ ###

<a name="algorithms"></a>
#### Algorithms: ####
1. Greedy Search Solution (Only)
2. Genetic Algorithm (GA) + GS
3. Simulated Annealing (SA) + GS
4. Simulated Ant Colony Optimization (SACO) + GS

### Source code
* EVRP.cpp EVRP.hpp
Implementation of the electric vehicle routing problem. 

* stats.cpp stats.hpp
Implementation to store the best solution for the 20 RUNS. 

* HMAGS.cpp, SA.cpp, GreedySearch.cpp, SACO.cpp
Metaheuristic Solution here.

* individual.cpp
algorithm, methods

* main.cpp 
Executable of the source code

/** Implementation Instructions **/ 

Step 1: Access to the path which containing the source code files with command line(CMD). 
Here are the commands necessary to run our c++ code in CMD.

```
$ cmake .
$ make
```

Step 2: Run this command in CMD: cmake .
(To create an executable file named "file_name")
```
$ evrp benchmark/input_file
```

Examples:
```
$ evrp benchmark/E-n101-k8.evrp
```
Note: The results store in Data/ folder

To make a graph solution, run command:
```
$ python3 evrpgraph.py Data/file_name
```