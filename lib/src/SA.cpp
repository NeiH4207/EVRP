#include "Algorithms.hpp"
#include <math.h>
#include <algorithm>

using namespace std;

Simulated_Annealing SA_optimizer;

void Simulated_Annealing:: init(Individual ant){
    cur_sol.copy_order(ant);
    cur_sol.setup();
}

void Simulated_Annealing::run(Individual &cur_sol) {
    Clock timer;
    Individual new_solution;
    double t_current = this->t_current;
    double t_cool = this->t_cool;
    double t_greedy = this->t_greedy;
    double alpha = this->alpha;
    double beta = this->beta;

    double improve;

    // cout << "initial fitness: " << cur_sol.get_fitness() << "\n";

    // int t_v = (int) (ACTUAL_PROBLEM_SIZE * this->t_v_factor);
    int cnt_div = 0;
    
    int G = 0;
    
    double sqrt_n = log10(ACTUAL_PROBLEM_SIZE);
    vector<double> conv;

    while (get_evals() < TERMINATION && t_current > t_end){
        t_greedy = ACTUAL_PROBLEM_SIZE * beta;
        // double prob = (double)rand() / RAND_MAX;
        t_cool = (alpha * sqrt_n - 1.0) / (alpha * sqrt_n);
        do {
            // cout << "Search: " << t_current << "\n";
            conv.push_back(cur_sol.get_fitness());
            new_solution.copy_order(cur_sol);
            
            double rand_t = (double) rand() / (double) RAND_MAX;
            if(rand_t <= 0.5){
                new_solution.greedy_1();
            } else {
                new_solution.greedy_2();
            }
            new_solution.setup();
            improve = cur_sol.get_fitness() - new_solution.get_fitness();
            G++;

            if (improve > 0)
                break;

            if(new_solution.get_fitness() + 1e10 > INF) {
                continue;
            }

            /* Termination */
            if (G >= t_greedy) {
                double upper = abs(new_solution.get_fitness() - cur_sol.get_fitness() ) / 
                    abs(new_solution.get_fitness() - best_sol->tour_length + 1e-5);
                // double rho = exp(upper) * t_current;
                double accept_prob = exp(- upper / t_current);
                // cout << upper << " " << cur_sol.get_fitness() << " " << new_solution.get_fitness() << " "
                    // << best_sol->tour_length << " prob: " << accept_prob << " " << t_current << "\n";
                // getchar();
                double r = ((double) rand() / (RAND_MAX));
                if(accept_prob > r){
                    cur_sol.copy_order(new_solution);
                }
                
                /* Compulsive Accept */
                cnt_div ++;
                break;
            }
            
        } while (improve < 0 && get_evals() < TERMINATION );
    
        cur_sol.copy_order(new_solution);
        if(new_solution.is_valid_solution()) {
            if(best_sol->tour_length > cur_sol.get_fitness()){
                best_sol->tour_length = cur_sol.get_fitness();
                best_sol->steps = cur_sol.get_steps();    
                for(int j = 0; j < best_sol->steps; j++){
                    best_sol->tour[j] = cur_sol.solution[j];
                }
                // cout << best_sol->tour_length << "\n";
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
