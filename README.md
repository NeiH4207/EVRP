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


Step 2: Run this command in CMD (To create an executable file named "file_name"): 
```
$ cmake .
$ make
```

Step 3: Run this command in CMD (To run the executable file):
```
$ ./evrp <algorithm> <benchmark_file> <output_file>
```

example:
```
$ ./evrp HMAGS benchmark/E-n23-k3.evrp output_files/
```

To make a solution in graph using python script:
```
$ python3 evrpgraph.py -i <solution-file>
```

```
$ python3 evrpgraph.py -i output_files/1/solution_HMAGS_E-n23-k3.evrp.txt
```
