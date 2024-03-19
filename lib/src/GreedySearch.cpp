#include "Algorithms.hpp"
#include <math.h>
#include <algorithm>

using namespace std;

GreedySearch gs_optimizer;

void GreedySearch:: init(){
    Individual sol;
    best_solution.copy_order(sol);
}

void GreedySearch::run() {
    Individual sol;
    sol.init("optimal");
    if(sol.is_valid_solution()) {
        if(best_sol->tour_length > sol.get_fitness()){
            best_sol->tour_length = sol.get_fitness();
            best_sol->steps = sol.get_steps();    
            for(int j = 0; j < best_sol->steps; j++){
                best_sol->tour[j] = sol.solution[j];
            }
        }
    }  else {
        cout << "Invalid solution\n";
    }
}

void initialize_GS() {
    best_sol = new solution;
    best_sol->tour = new int[MAX_NODE];
    best_sol->id = 1;
    best_sol->steps = 0;
    best_sol->tour_length = INF;
    compute_nearest_points();
}

void free_GS(){
    delete[] best_sol->tour;
    delete best_sol;
}
