#include "Algorithms.hpp"
#include <math.h>
#include <algorithm>

using namespace std;

Simulated_Annealing SA_optimizer;

void Simulated_Annealing:: init(Solution ant){
    cur_sol.copy_order(ant);
}

void Simulated_Annealing::run(Solution &cur_sol) {
    Clock timer;
    Solution new_solution;
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
                greedy_1(cur_sol);
            } else {
                greedy_2(cur_sol);
            }
            
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
                    best_sol->tour[j] = cur_sol.full_path[j];
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



void Simulated_Annealing::greedy_1(Solution &cur_sol){
    cur_sol.reset_tour_index();
    int customer = rand() % (NUM_OF_CUSTOMERS) + 1;
    static int near_customer;
    near_customer = -1;

    for(int x: nearest[customer]){
        if ((rand() % INT_MAX) / (1.0 * INT_MAX) < 0.1) continue;
        if(cur_sol.tour_index[x] != cur_sol.tour_index[customer]){
            near_customer = x;
            break;
        }
    }

    if(near_customer != -1){

        for(int i = cur_sol.tours[cur_sol.tour_index[customer]].left; i <= cur_sol.tours[cur_sol.tour_index[customer]].right; i++){
            if(cur_sol.order[i] == customer){
                cur_sol.order[i] = near_customer;
                break;
            }
        }

        for(int i = cur_sol.tours[cur_sol.tour_index[near_customer]].left; i <= cur_sol.tours[cur_sol.tour_index[near_customer]].right; i++){
            if(cur_sol.order[i] == near_customer){
                cur_sol.order[i] = customer;
                break;
            }
        }
        swap(cur_sol.tour_index[customer], cur_sol.tour_index[near_customer]);
    }
}
void Simulated_Annealing::greedy_2(Solution &Solution) {
    Solution.reset_tour_index();
    int customer_index = rand() % NUM_OF_CUSTOMERS;
    int customer = Solution.order[customer_index];
    int tour_index = Solution.tour_index[customer];
    int tour_size = Solution.tours[tour_index].right - Solution.tours[tour_index].left + 1;
    int capacity = Solution.get_capacity_of_tour(tour_index);

    int neighbor = -1;
    for (int x : nearest[customer]) {
        if (Solution.tour_index[x] != tour_index && capacity + get_customer_demand(x) <= MAX_CAPACITY && tour_size > 2) {
            neighbor = x;
            break;
        }
    }

    if (neighbor != -1) {
        int neighbor_tour_index = Solution.tour_index[neighbor];
        int neighbor_index = -1;
        for (int i = Solution.tours[neighbor_tour_index].left;
                i <= Solution.tours[neighbor_tour_index].right; i++) {
            if (Solution.order[i] == neighbor) {
                neighbor_index = i;
                break;
            }
        }

        if (tour_index < neighbor_tour_index) {
            swap(Solution.order[neighbor_index], Solution.order[Solution.tours[neighbor_tour_index].left]);
            Solution.tours[neighbor_tour_index].left++;
            for (int i = neighbor_tour_index - 1; i > tour_index; i--) {
                for (int j = Solution.tours[i].right; j >= Solution.tours[i].left; j--) {
                    Solution.order[j + 1] = Solution.order[j];
                }
                Solution.tours[i].left++;
                Solution.tours[i].right++;
            }
            Solution.tours[tour_index].right++;
            Solution.order[Solution.tours[tour_index].right] = neighbor;
            Solution.tour_index[neighbor] = tour_index;
        } else {
            swap(Solution.order[neighbor_index], Solution.order[Solution.tours[neighbor_tour_index].right]);
            Solution.tours[neighbor_tour_index].right--;
            for (int i = neighbor_tour_index + 1; i < tour_index; i++) {
                for (int j = Solution.tours[i].left; j <= Solution.tours[i].right; j++) {
                    Solution.order[j - 1] = Solution.order[j];
                }
                Solution.tours[i].left--;
                Solution.tours[i].right--;
            }
            Solution.tours[tour_index].left--;
            Solution.order[Solution.tours[tour_index].left] = neighbor;
            Solution.tour_index[neighbor] = tour_index;
        }
    }
}



void free_SA(){
    delete[] best_sol->tour;
    delete best_sol;
}
