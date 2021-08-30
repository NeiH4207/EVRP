EVRP.cpp EVRP.hpp
Implementation of the electric vehicle routing problem. 

stats.cpp stats.hpp
Implementation to store the best solution for the 20 RUNS. 

HMAGS.cpp
Evolution Algorithm here.

individual.cpp
algorithm, methods

main.cpp 
Executable of the source code

/** Implementation Instructions **/ 

NOTE: You could place the input files in the same position with source code files

Step 1: Access to the path which containing the source code files with command line(CMD). 
Here are the commands necessary to run our c++ code in CMD.

Step 2: Run this command in CMD: g++ -Wall -std=c++14 EVRP.cpp stats.cpp HMAGS.cpp utils.cpp main.cpp -o file_name
(To create an executable file named "file_name")
g++ -Wall -std=c++14 EVRP.cpp stats.cpp individual.cpp SA.cpp Algorithms.cpp utils.cpp main.cpp -o main

Step 3: Run this command in CMD: ./file_name <input instance name> 
Examples: file_name E-n22-k4.evrp
(to excute source code in E-n22-k4 instance of EVRP benchmark)
./main benchmark/E-n22-k4.evrp 
