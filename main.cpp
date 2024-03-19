#include<iostream>
#include<string>
#include "utils.hpp"         

using namespace std;

int main(int argc, char *argv[]) {
  
  std::cout << "EVRP" << std::endl;
  try {
    if (argc < 4 || MAX_TRIALS < 1) {
      std::cerr << "Usage: " << argv[0] << " <algorithm> <inputfile> <outputpath>" << std::endl;
      return 1;
    }
    std::string algo(argv[1]), outputpath(argv[3]);
    char *filename = argv[2];
    std::cout << "Algorithm: " << algo << std::endl;
    std::cout << "Input file: " << filename << std::endl;
    std::cout << "Output path: " << outputpath << std::endl;
    std::cout << "-------------" << std::endl;

    read_problem(filename);   //Read EVRP from file from EVRP.h
    open_stats(filename, algo, outputpath); //open text files to store the best values from the MAX_TRIALS runs stats.h
    cout << "Running " << MAX_TRIALS << " times" << endl;

    for(int trial = 1; trial <= MAX_TRIALS; ++trial){
      start_run(trial);
      if (algo == "SACO"){
        SACO  *ants = new SACO (1, 2, 80, 0.1, 2, 0);
        while(!termination_condition(1)){
          ants->optimize();
        }
        save_solution(outputpath, algo, filename, trial);
        ants->free_SACO();
      } else if (algo == "GS"){
        initialize_GS();
        gs_optimizer.run(gs_optimizer.best_solution);
        save_solution(outputpath, algo, filename, trial);
        free_GS();
      } else if (algo == "HMAGS"){
        initialize_HMAGS();
        while(!termination_condition(1)){
          run_HMAGS(); 
        }
        save_solution(outputpath, algo, filename, trial);
        free_HMAGS();
      } else if (algo == "SA"){
        initialize_SA();
        SA_optimizer.run(SA_optimizer.cur_sol);  
        save_solution(outputpath, algo, filename, trial);
        free_SA();
      } else{
        std::cerr << "Algorithm " << algo << " not found" << std::endl;
      }
      end_run(trial);  //store the best solution quality for each run
    }
    close_stats(); 
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
