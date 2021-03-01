EVRP.cpp EVRP.hpp
Implementation of the electric vehicle routing problem. 

stats.cpp stats.hpp
Implementation to store the best solution for the 20 RUNS. 

heuristic.cpp heuristic.hpp
my solver here.

main.cpp 
Executable of the source code

NOTE: We have just changed the heuristic.cpp file, other files is exactly the 
same files provided at the address: https://mavrovouniotis.github.io/EVRPcompetition2020/
so you can compile is the same way to compile the initial random heuristic algorithm

/** Implementation Instructions **/ 

NOTE: You could place the input files in the same position with source code files

Step 1: Access to the path which containing the source code files with command line(CMD). 
Here are the commands necessary to run our c++ code in CMD.

Step 2: Type in CMD: g++ -Wall -std=c++14 EVRP.cpp stats.cpp heuristic.cpp main.cpp -o runfile
(To create an executable file named "runfile.exe")

Step 3: Type in CMD to compile: runfile <input filename> 
Examples: runfile E-n22-k4.evrp
(to excute source code in E-n22-k4 instance of EVRP benchmark)