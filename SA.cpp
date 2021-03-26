#include "SA.hpp"
#include <math.h>
#include <algorithm>

using namespace std;

Simulated_Annealing sa;

void Simulated_Annealing::run(int maxtime_sec) {
    Clock timer;
    Individual current_solution;
    Individual new_solution;
    current_solution.init("optimal");
    double t_current = this->t_current;
    double t_cool = this->t_cool;
    double t_greedy = this->t_greedy;
    double alpha = this->alpha;
    double beta = this->beta;

    double improve;

    // int t_v = (int) (ACTUAL_PROBLEM_SIZE * this->t_v_factor);
    int cnt_div = 0;
    
    int G = 0;
    
    double sqrt_n = log10(ACTUAL_PROBLEM_SIZE);
    vector<double> conv;

    while (timer.getseconds() < maxtime_sec && get_evals() < TERMINATION && t_current > t_end){
        t_greedy = ACTUAL_PROBLEM_SIZE * beta;
        // double prob = (double)rand() / RAND_MAX;
        t_cool = (alpha * sqrt_n - 1.0) / (alpha * sqrt_n);
        do {
            conv.push_back(current_solution.get_fitness());
            new_solution.copy_order(current_solution);
            double rand_to_select_alg = (double) rand() / (double) RAND_MAX;
            
            if(rand_to_select_alg <= 0.5){
                new_solution.greedy_1();
            } else {
                new_solution.greedy_2();
            }
            new_solution.setup();
            
            //G+1
            G++;

            improve = current_solution.get_fitness() - new_solution.get_fitness();

            if (improve > 0)
                break;


            if(new_solution.get_fitness() + 1e10 > INF) {
                continue;
            }

            /* Termination */
            if (G >= t_greedy) {
                double upper = improve / abs(new_solution.get_fitness() - best_sol->tour_length + 1e-5);
                // double rho = exp(upper) * t_current;
                double probability = (double)rand() / RAND_MAX;
                if(probability < t_current){
                    current_solution.copy_order(new_solution);
                }
                
                /* Compulsive Accept */
                cnt_div ++;
                break;
            }
            
        } while (improve < 0 && timer.getseconds() < maxtime_sec);
    
        if(improve > 0) {
             current_solution.copy_order(new_solution);
            if(new_solution.is_valid_solution()) {
                if(best_sol->tour_length > current_solution.get_fitness()){
                    best_sol->tour_length = current_solution.get_fitness();
                    best_sol->steps = current_solution.get_steps();    
                    for(int j = 0; j < best_sol->steps; j++){
                        best_sol->tour[j] = current_solution.solution[j];
                    }
                }
            } 
        }
        t_current *= t_cool;
        t_current = max(t_current, t_end);

        G = 0;
    }//end while
    save_conv(conv, "conv_file_3");
}

void initialize_SA() {
    best_sol = new solution;
    best_sol->tour = new int[MAX_NODE];
    best_sol->id = 1;
    best_sol->steps = 0;
    best_sol->tour_length = INF;
    compute_nearest_points();
}

void free_SA(){
    delete[] best_sol->tour;
    delete best_sol;
}

/*implement your heuristic in this function*/
void run_SA() {
    sa.run(7200);
}
