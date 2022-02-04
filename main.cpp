#include<iostream>
#include<string>
#include "utils.hpp"         

using namespace std;

int main(int argc, char *argv[]) {

  int run;
  /*Step 1*/
  algorithm = argv[1];
  if (argv[2]){
    problem_instance = argv[2]; 
  } else {
    cout << "Please specify a problem instance" << endl;
    return 0;
  }
        //pass the .evrp filename as an argument
  read_problem(problem_instance);   //Read EVRP from file from EVRP.h
  /*Step 2*/
  // cout << problem_instance << "\n";
  open_stats();//open text files to store the best values from the 20 runs stats.h4
  // cout << "Running " << MAX_TRIALS << " times" << endl;
  vector<double> conv;
  for(run = 1; run <= MAX_TRIALS; run++){
    /*Step 3*/
    start_run(run);
    if (algorithm == "SACO"){
      SACO  *ANTS = new SACO (1, 2, 80, 0.1, 2, 0);
      while(!termination_condition(1)){
        ANTS->optimize();
        if (run == 1){
          conv.push_back(best_sol->tour_length);
        }
      }
      save_solution(algorithm, problem_instance, run); 
      ANTS->free_SACO();
    } else if (algorithm == "GS"){
      initialize_GS();
      gs_optimizer.run(gs_optimizer.best_solution);
      save_solution(algorithm, problem_instance, run); 
      free_GS();
    } else if (algorithm == "HMAGS"){
      initialize_HMAGS();
      while(!termination_condition(1)){
        run_HMAGS();  //heuristic.
        if (run == 1){
          conv.push_back(best_sol->tour_length);
        }
      }
      save_solution(algorithm, problem_instance, run); 
      free_HMAGS();
    } else if (algorithm == "SA"){
      initialize_SA();
      SA_optimizer.run(SA_optimizer.cur_sol);  //heuristic.
      save_solution(algorithm, problem_instance, run); 
      free_SA();
    } else{
      cout << "Algorithm " << algorithm << " not found" << endl;
    }
    // }
    // conv.push_back(best_sol->tour_length);
    // save_conv(conv, "conv_file_3");
    end_run(run);  //store the best solution quality for each run
  }
  /*Step 6*/
  close_stats(); //close text files to calculate the mean result from the 20 runs stats.h


  //free memory

  return 0;
}
