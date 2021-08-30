#include<iostream>
#include "utils.hpp"            

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
  for(run = 1; run <= MAX_TRIALS; run++){
    /*Step 3*/
    start_run(run);
    SACO  *ANTS = new SACO (1, 2, 80, 0.1, 2, 0);
    // //Initialize your heuristic here
    // vector<double> conv;
    // initialize_HMAGS();
    // // initialize_SA();
    // // run_SA();  // simulated anneling
    ANTS->init(run);
    /*Step 4*/
    while(!termination_condition(1)){
      //Execute your heuristic
      // run_HMAGS();  //heuristic.
      ANTS->optimize();
      // conv.push_back(best_sol->tour_length);
    }
    // conv.push_back(best_sol->tour_length);
    // save_conv(conv, "conv_file_3");
    // save_solution(run);
    // free_HMAGS();
    // free_SA();
    // for (int i = 0; i < best_sol->steps; i++){
    //   cout << best_sol->tour[i] << " ";
    // }
    // cout << "\n";
    /*Step 5*/
    // SA_optimizer.init(ANTS->Ants[0]);
    // SA_optimizer.run(7200);
    end_run(run);  //store the best solution quality for each run
    ANTS->free_SACO();
  }
  /*Step 6*/
  close_stats(); //close text files to calculate the mean result from the 20 runs stats.h


  //free memory

  return 0;
}
