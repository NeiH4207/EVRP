#include "Algorithms.hpp"

using namespace std;

HMAGS hmags;

void HMAGS::init(){
    for(int i = 0; i < NUM_OF_INDVS; i++) {
        pop[i].init("clustering");
        if (pop[i].get_fitness() < best_sol->tour_length){
            best_sol->tour_length = pop[i].get_fitness();
            best_sol->steps = pop[i].get_steps();    
            for(int j = 0; j < best_sol->steps; j++){
                best_sol->tour[j] = pop[i].solution[j];
            }
        }
    }
}

void HMAGS::compute_rank(int n){
    double sum = 0;
    double fit_min = INF;
    double fit_max = 0;
    for(int i = 0; i < n; i++){
        fit_min = min(fit_min, pop[i].get_fitness());
        fit_max = max(fit_max, pop[i].get_fitness());
    }
    for(int i = 0; i < n; i++){
        double temp_fit = pow((fit_max - pop[i].get_fitness()) / (fit_max - fit_min + 1e-6), 2);
        sum += temp_fit;
        rank[i] = temp_fit;
    }
    for(int i = 0; i < n; i++){
        rank[i] /= sum;
        if(i > 0)
            rank[i] += rank[i - 1];
    }
}

int HMAGS::choose_by_rank(double prob){
    return (int) (upper_bound(rank, rank + NUM_OF_INDVS, prob) - rank);
}

void HMAGS::Repopulation() {
    compute_rank(NUM_OF_INDVS);
    for(int i = 0; i < 2 * NUM_OF_INDVS; i += 2) {
        // choose the two parents
        double p1 = (double) rand() / (double) RAND_MAX;
        double p2 = (double) rand() / (double) RAND_MAX;
        int idx_1 = choose_by_rank(p1);
        int idx_2 = choose_by_rank(p2);
        while(p1 == p2)
            p2 = (double) rand() / (double) RAND_MAX;
        distribute_crossover(pop[idx_1], pop[idx_2], NUM_OF_INDVS + i);
    }
    int cnt = 0;
    for (int i = NUM_OF_INDVS; i < 3 * NUM_OF_INDVS; i++){
        if( pop[i].get_steps() == 0){
            cnt++;
        }
        if (pop[i].get_fitness() < best_sol->tour_length){
            best_sol->tour_length = pop[i].get_fitness();
            best_sol->steps = pop[i].get_steps();    
            for(int j = 0; j < best_sol->steps; j++){
                best_sol->tour[j] = pop[i].solution[j];
            }
        }
    }
}

void HMAGS::mutate(Individual &indv, string method, double Pr_mutate = 0.1) {

    double mutate_prob = (double) rand() / (double) RAND_MAX;
    indv.reset_tour_index();

    if (mutate_prob > Pr_mutate) {
        return;
    }

    if (method == "hsm"){
        int customer = rand() % (NUM_OF_CUSTOMERS) + 1;
        static int near_customer;
        near_customer = -1;

        for(int x: nearest[customer]){
            if(indv.tour_index[x] != indv.tour_index[customer]){
                near_customer = x;
                break;
            }
        }

        if(near_customer != -1){

            for(int i = indv.tours[indv.tour_index[customer]].left; i <= indv.tours[indv.tour_index[customer]].right; i++){
                if(indv.order[i] == customer){
                    indv.order[i] = near_customer;
                    break;
                }
            }

            for(int i = indv.tours[indv.tour_index[near_customer]].left; i <= indv.tours[indv.tour_index[near_customer]].right; i++){
                if(indv.order[i] == near_customer){
                    indv.order[i] = customer;
                    break;
                }
            }

            swap(indv.tour_index[customer], indv.tour_index[near_customer]);
        }
    }

    if (method == "hmm"){
        // choose randomly a index of order
        int customer_index = rand() % (NUM_OF_CUSTOMERS);
        int customer = indv.order[customer_index];
        double cost = indv.get_capacity_of_tour(indv.tour_index[customer]);

        int near_customer = -1;
        for(int x: nearest[customer]){
            if(indv.tour_index[x] != indv.tour_index[customer] && cost + get_customer_demand(x) <= MAX_CAPACITY
                    && indv.tours[indv.tour_index[x]].right - indv.tours[indv.tour_index[x]].left > 1){

                near_customer = x;
                break;
            }
        }
        if(near_customer != -1){
            int near_customer_tour_index = indv.tour_index[near_customer], customer_tour_index = indv.tour_index[customer];

            int near_customer_index = -1;
            for(int i = indv.tours[near_customer_tour_index].left; i <= indv.tours[near_customer_tour_index].right; i++){
                if(indv.order[i] == near_customer){
                    near_customer_index = i;
                    break;
                }
            }

            // pick from near_customer_tour_index . customer_tour_index
            if(customer_tour_index < near_customer_tour_index){
                swap(indv.order[near_customer_index], indv.order[indv.tours[near_customer_tour_index].left]);
                indv.tours[near_customer_tour_index].left++;
                for(int i = near_customer_tour_index - 1; i > customer_tour_index; i--){
                    for(int j = indv.tours[i].right; j >= indv.tours[i].left; j--){
                        indv.order[j + 1] = indv.order[j];
                    }
                    indv.tours[i].left++;
                    indv.tours[i].right++;
                }
                indv.tours[customer_tour_index].right++;
                indv.order[indv.tours[customer_tour_index].right] = near_customer;
                indv.tour_index[near_customer] = customer_tour_index;
            } else{
                swap(indv.order[near_customer_index], indv.order[indv.tours[near_customer_tour_index].right]);
                indv.tours[near_customer_tour_index].right--;
                for(int i = near_customer_tour_index + 1; i <= customer_tour_index; i++){
                    for(int j = indv.tours[i].left; j <= indv.tours[i].right; j++){
                        indv.order[j - 1] = indv.order[j];
                    }
                    indv.tours[i].left--;
                    indv.tours[i].right--;
                }
                indv.tours[customer_tour_index].right++;
                indv.order[indv.tours[customer_tour_index].right] = near_customer;
                indv.tour_index[near_customer] = customer_tour_index;
            }
        }
        return;
    }
}

void HMAGS::distribute_crossover(Individual parent_1, Individual parent_2, int idx) {

    int num = rand()%(NUM_OF_CUSTOMERS) + 1;// so ngau nhien tu 1 den size of customers
    int id1 = parent_1.tour_index[num];// customer 'num' of id1 tour in parent_1
    int id2 = parent_2.tour_index[num];// customer 'num' of id2 tour in parent_2
    int have[NUM_OF_CUSTOMERS + 1];
    int alens[NUM_OF_CUSTOMERS + 1];

    Individual child1;
    Individual child2;
    child1.copy_order(parent_1);
    child2.copy_order(parent_2);

    for(int i = 0; i <= NUM_OF_CUSTOMERS; i++){
        have[i] = 0;// have : exists in the alens or not
        alens[i] = 0;
    }

    int index = 0;

    // merge tour_id1, tour_id2 into alens
    for(int i = parent_1.tours[id1].right; i >= parent_1.tours[id1].left; i--) {
        alens[index++] = parent_1.order[i];
        have[parent_1.order[i]] = 1;
    }

    for(int i = parent_2.tours[id2].right; i >= parent_2.tours[id2].left; i--) {
        if(!have[parent_2.order[i]]) {
            alens[index++] = parent_2.order[i];
            have[parent_2.order[i]] = 1;
        }
    }
    int index2 = 0; // size of alens

    // Distribute alens to both of child1 and child2

    for(int i = 0; i < NUM_OF_CUSTOMERS; i++){
        if(have[child1.order[i]]){
            child1.order[i] = alens[--index];
        }
        if(have[child2.order[i]]){
            child2.order[i] = alens[index2++];
        }
    }
    mutate(child1, "hsm", 0.1);
    mutate(child1, "hsm", 0.1);
    mutate(child2, "hmm", 0.1);
    mutate(child2, "hmm", 0.1);
    pop[idx].copy_order(child1);
    pop[idx + 1].copy_order(child2);
    pop[idx].setup();
    pop[idx + 1].setup();
}

void HMAGS::Selection() {

    sort(pop, pop + 3 * NUM_OF_INDVS, [](Individual x, Individual y) {
            return x.get_fitness() < y.get_fitness();
    });

    compute_rank(2 * NUM_OF_INDVS);

    for (int i = 0; i < NUM_OF_INDVS; i++){
        double prob = (double) rand() / (double) RAND_MAX;
        int idx = choose_by_rank(prob);
        pop[2 * NUM_OF_INDVS + i].copy_order(pop[idx]);
    }
    
    for (int i = 0; i < NUM_OF_INDVS; i++){
        pop[i].copy_order(pop[NUM_OF_INDVS * 2 + i]);
    }
    
}

void HMAGS::Evolution() {
    Repopulation();
    Selection();
}

void initialize_HMAGS() {
    best_sol = new solution;
    best_sol->tour = new int[MAX_NODE];
    best_sol->id = 1;
    best_sol->steps = 0;
    best_sol->tour_length = INF;
    compute_nearest_points();
    hmags.init();
}

void free_HMAGS(){
    delete[] best_sol->tour;
    delete best_sol;
}

/*implement your heuristic in this function*/
void run_HMAGS() {
    hmags.Evolution();
}
