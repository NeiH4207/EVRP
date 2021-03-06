#include<iostream>
#include "utils.hpp"
// #include "HMAGS.hpp"

using namespace std;


/****************************************************************/
/*                Main Function                                 */
/****************************************************************/
int main(int argc, char *argv[]) {

  int run;
  /*Step 1*/
  problem_instance = argv[1];       //pass the .evrp filename as an argument
  read_problem(problem_instance);   //Read EVRP from file from EVRP.h

  /*Step 2*/
  open_stats();//open text files to store the best values from the 20 runs stats.h

  for(run = 1; run <= 1; run++){
    /*Step 3*/
    start_run(run);
    // //Initialize your heuristic here
    // vector<double> conv;
    initialize_HMAGS();
    // // initialize_SA();
    // // run_SA();  // simulated anneling

    // /*Step 4*/
    // while(!termination_condition()){
    //   //Execute your heuristic
    //   conv.push_back(best_sol->tour_length);
    //   run_HMAGS();  //heuristic.h
    // }
    // conv.push_back(best_sol->tour_length);
    // save_conv(conv, "conv_file_3");
    save_solution(run);
    // free_HMAGS();
    // free_SA();
    /*Step 5*/
    end_run(run);  //store the best solution quality for each run
  }
  /*Step 6*/
  close_stats(); //close text files to calculate the mean result from the 20 runs stats.h


  //free memory

  return 0;
}
