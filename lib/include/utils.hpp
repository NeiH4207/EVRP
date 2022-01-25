#include <vector>
#include <fstream>
#include<iostream>
#include<limits.h>
#include<stdlib.h>
// #include "HMAGS.hpp"
#include "Algorithms.hpp"
#include "stats.hpp"

using namespace std;

/*initialiazes a run for your heuristic*/
void start_run(int r);

/*gets an observation of the run for your heuristic*/
void end_run(int r);

/*sets the termination conidition for your heuristic*/
bool termination_condition(double rate);