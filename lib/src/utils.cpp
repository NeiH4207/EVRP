#include "utils.hpp"
/*initialiazes a run for your heuristic*/
void start_run(int r){

  srand(r); //random seed
  init_evals();
  init_current_best();
  cout << "Run: " << r << " with random seed " << r << endl;
}

/*gets an observation of the run for your heuristic*/
void end_run(int r){
  get_mean(r-1,get_current_best()); //from stats.h
  cout << "End of run " << r << " with best solution quality " << get_current_best() << " total evaluations: " << get_evals()  << endl;
  cout << " " << endl;
}

/*sets the termination conidition for your heuristic*/
bool termination_condition(double rate = 1.0) {

  bool flag;
  if(get_evals() >= rate * TERMINATION)
    flag = true;
  else
    flag = false;

  return flag;
}
