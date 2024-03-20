#include "Algorithms.hpp"
#include <math.h>
#include <algorithm>
#include <assert.h>

using namespace std;

GreedySearch GS_optimizer;

void GreedySearch::run() {
    Solution sol = create_random_solution();
    
    greedy_search(sol);

    if(sol.is_valid_solution()) {
        if(best_sol->tour_length > sol.get_fitness()){
            best_sol->tour_length = sol.get_fitness();
            best_sol->steps = sol.get_steps();    
            for(int j = 0; j < best_sol->steps; j++){
                best_sol->tour[j] = sol.solution[j];
            }
        }
    } 
}

void GreedySearch::greedy_search(Solution &sol){
    clustering(sol);
    balancing_capacity(sol);
    local_search(sol);
    insert_charging_stations(sol);
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

Solution GreedySearch::create_random_solution(){
    Solution sol;
    for(int i = 0; i < NUM_OF_CUSTOMERS; i++) {
        sol.order[i] = i + 1;
        sol.index_of_customer[i + 1] = i;
    }
    // shuffle the customers
    for(int i = 0; i < NUM_OF_CUSTOMERS; i++) {
        int idx_1, idx_2;
        idx_1 = rand() % NUM_OF_CUSTOMERS; // random number from 0 to NUM_OF_CUSTOMERS - 1
        idx_2 = rand() % NUM_OF_CUSTOMERS; // random number from 0 to NUM_OF_CUSTOMERS - 1
        swap(sol.index_of_customer[sol.order[idx_1]], sol.index_of_customer[sol.order[idx_2]]);
        swap(sol.order[idx_1], sol.order[idx_2]);
    }
    return sol;
}

void GreedySearch::clustering(Solution &sol){
    // put the customers into tours
    vector<int> have(NUM_OF_CUSTOMERS + 1, 0);
    int first_customer_index, capacity, idx;
    idx = 0;
    while(idx < NUM_OF_CUSTOMERS) {
        // rand()%N return random number from 0 to N-1
        first_customer_index = rand()%(NUM_OF_CUSTOMERS - idx) + idx;
        // set the index of the first customer to its correct index
        sol.index_of_customer[sol.order[idx]] = first_customer_index;
        // swap the first customer to its correct index
        swap(sol.order[first_customer_index], sol.order[idx]);
        first_customer_index = idx;
        int first_customer = sol.order[idx];
        have[first_customer] = 1;
        capacity = get_customer_demand(first_customer);
        idx++;

        // add nearest customers to the current tour
        for(int customer : nearest[first_customer]){
            if(have[customer]) continue;
            if(capacity + get_customer_demand(customer) <= MAX_CAPACITY) {
                have[customer] = 1;
                capacity += get_customer_demand(customer);
                sol.index_of_customer[sol.order[idx]] = sol.index_of_customer[customer];
                swap(sol.order[idx], sol.order[sol.index_of_customer[customer]]);
                idx++;
            } else{
                int num_of_tours = sol.get_num_of_tours();
                // the current tour is full, so create a new tour
                sol.tours[num_of_tours] = {first_customer_index, idx - 1};
                sol.set_num_of_tours(num_of_tours + 1);
                break;
            }
        }
    }
    // the last tour
    int num_of_tours = sol.get_num_of_tours();
    sol.tours[num_of_tours] = {first_customer_index, NUM_OF_CUSTOMERS - 1};
}

void GreedySearch::local_search(Solution &sol){

    static int l, r, x, y, i, j, u0, v0, u1, v1;
    static double t1, t2;
    static bool stop;
    for(int id_tour = 0; id_tour < sol.get_num_of_tours(); id_tour++) {
        l = sol.tours[id_tour].left;
        r = sol.tours[id_tour].right;
        while (true) {
            stop = true;
            for(i = l; i <= r; ++i) {
                for(j = r; j > i; --j) {
                    u0 = sol.order[i], u1 = sol.order[i - 1];
                    v0 = sol.order[j], v1 = sol.order[j + 1];

                    if(i - 1 < l)
                        u1 = 0;
                    if(j + 1 > r)
                        v1 = 0;

                    t1 = get_distance(u1, u0)+ get_distance(v0, v1);
                    t2 = get_distance(u1, v0) + get_distance(u0, v1);

                    if (t1 > t2) {
                        for(x = i, y = j; x <= y; ++x, --y) {
                            swap(sol.order[x], sol.order[y]);
                        }
                        stop = false;
                    }

                }
            }
            if (stop) break;
        }
    }
}

/**
 * A function to balance the capacity of a solution by adjusting the distribution of customers among tours.
 *
 * @param sol the Solution object representing the solution to be balanced
 *
 * @throws None
 */
void GreedySearch::balancing_capacity(Solution &sol){
    sol.reset_tour_index();
    int last_tour_idx = sol.get_num_of_tours() - 1;
    int is_customer_in_last_tour[NUM_OF_CUSTOMERS + 1];
    int l = sol.tours[last_tour_idx].left;
    int r = sol.tours[last_tour_idx].right;

    for (int i = 0; i <= NUM_OF_CUSTOMERS; i++){
        is_customer_in_last_tour[i] = 0;
    }
    
    for(int i = l; i <= r; i++){
        is_customer_in_last_tour[sol.order[i]] = 1;
    }

    // choose a customer in last tour
    double last_tour_capacity = sol.get_capacity_of_tour(last_tour_idx);
    int random_customer_idx = rand() % (r - l + 1) + l;
    int selected_customer = sol.order[random_customer_idx];

    for(int x: nearest[selected_customer]){
        if(is_customer_in_last_tour[x]) continue;
        double curr_tour_capacity = sol.get_capacity_of_tour(sol.tour_index[x]);

        // The new delta is the difference between the last tour capacity and the current tour capacity
        // Make sure that the new delta is smaller than the old delta (balancing capacity)
        double new_delta = abs(last_tour_capacity + get_customer_demand(x) - (curr_tour_capacity - get_customer_demand(x)));
        double delta = abs(last_tour_capacity - curr_tour_capacity);

        if(last_tour_capacity + get_customer_demand(x) <= MAX_CAPACITY && new_delta < delta){
            // move x to last tour
            int idx = -1;
            for (int i = 0; i < last_tour_idx; ++i) {
                for (int j = sol.tours[i].left; j <= sol.tours[i].right; ++j) {
                    if (sol.order[j] == x) {
                        swap(sol.order[j], sol.order[j + 1]);
                        idx = i;
                        break;
                    }
                }
                if (idx != -1) {
                    --sol.tours[idx].right;
                    --sol.tours[idx + 1].left;
                    break;
                }
            }
            is_customer_in_last_tour[x] = 1;
            last_tour_capacity += get_customer_demand(x);
            assert(sol.get_num_of_tours() > 0);
            sol.tour_index[x] = last_tour_idx;
            int l = sol.tours[last_tour_idx].left;
            int r = sol.tours[last_tour_idx].right;
            selected_customer = sol.order[rand() % (r - l + 1) + l];
        } else{
            break;
        }
    }
}

// Find nearest station from 'to'

int GreedySearch::nearest_station(int from, int to, double energy) {
    static double min_length, length;
    min_length = INF;
    static int best_station;
    best_station = -1;

    for(int v = NUM_OF_CUSTOMERS + 1; v != ACTUAL_PROBLEM_SIZE && v != 1; v++) {
        if(!is_charging_station(v)){
            v = 0;
        }
        length = get_distance(v, to);
        if(get_energy_consumption(from, v) <= energy) {
            if(min_length > length){
                min_length = length;
                best_station = v;
            }
        }
    }
    return best_station;
}

// Find shortest path from 'from' to 'to' such that minimize tour length

int GreedySearch::nearest_station_back(int from, int to, double energy) {

    static double min_length, length1, length2;
    min_length = INF;
    static int best_station;
    best_station = -1;

    for(int v = NUM_OF_CUSTOMERS + 1; v != ACTUAL_PROBLEM_SIZE && v != 1; v++) {
        if(!is_charging_station(v)){
            v = 0;
        }
        if(get_energy_consumption(from, v) <= energy) {
            length1 = get_distance(from, v);
            length2 = get_distance(v, to);
            if(min_length > length1 + length2){
                min_length = length1 + length2;
                best_station = v;
            }
        }
    }
    return best_station;
}

void GreedySearch::optimize_station(int *tmp_path, int length, string direction){
    /*
    * Note at this function, number of continuous charging stations S and S' is 1. But it can be more than 1.
    valid tour after inserting energy stations
    : depot_L -> c6 -> c5 -> c4 -> c3 -> S(S1 -> S2) -> c2 -> c1 -> depot_R
    Reverse tour
    : depot_R -> c1 -> c2 -> S(S1 -> S2) -> c3 -> c4 -> c5 -> c6 -> depot_L
    Replace S to other:
    step 1. from depot_R, get a subtour that vehicle reach farest from depot_R but not visit any charging station
        : depot_R -> c1 -> c2 -> c3 -> c4 - (not enough energy to reach c5) -> c5
        : delta_L1 = (d(c2, s1) + d(s1, s2) + d(s2, c3) - d(c2, c3))
    step 2: From c2->c3, c3->c4, c4->c5, find S' (>= 1 charging stations):
        : delta_L2 = d(c3, S') + d(S', c3) - d(c2, c3)
        : delta_L2 = d(c3, S') + d(S', c4) - d(c3, c4)
        : delta_L2 = d(c4, S') + d(S', c5) - d(c4, c5)
        if delta_L2 < delta_L1 then replace S with S'
        # see the paper: https://doi.org/10.1007/s10489-022-03555-8 for more details
    */

    static double energy;
    energy = BATTERY_CAPACITY;
    static int sz;
    double remaining_energy[MAX_NODE];
    int customer_stack[MAX_NODE];
    // Recalculate energy after inserting charging stations

    remaining_energy[0] = BATTERY_CAPACITY;
    for(int i = 1; i <= length; i++){
        int from = tmp_path[i - 1];
        int to = tmp_path[i];
        remaining_energy[to] = remaining_energy[from] - get_energy_consumption(tmp_path[to], tmp_path[from]);
        if(is_charging_station(tmp_path[to])){
            remaining_energy[to] = BATTERY_CAPACITY;
        }
    }

    for(int i = length; i - 2 > 0; i--){
        int from = tmp_path[i - 1];
        int to = tmp_path[i];

        if(!is_charging_station(tmp_path[from])){
            energy -= get_energy_consumption(tmp_path[to], tmp_path[from]);
            continue;
        }

        sz = 0;
        static double battery;
        battery = energy;

        for(int j = i - 2; j >= 0; j--){
            if(is_charging_station(tmp_path[j])){
                break;
            }
            battery -= get_energy_consumption(from, tmp_path[j]);
            if(battery <= 0) break;
            customer_stack[sz++] = tmp_path[j];
            from = tmp_path[j];
        }

        static double deltaL1, deltaL2;
        deltaL1 = get_distance(tmp_path[i], tmp_path[i - 1])
                    + get_distance(tmp_path[i - 1], tmp_path[i - 2])
                    - get_distance(tmp_path[i], tmp_path[i - 2]);

        int index = 0;
        from = tmp_path[i];
        int best_station = tmp_path[i - 1];
        for(int j = 0, to; j < sz; j++){
            to = customer_stack[j];
            int station;
            if (direction == "backward") {
                nearest_station_back(from, to, energy);
            } else {
                station = nearest_station(from, to, energy);
            }
            energy -= get_energy_consumption(from, to);
            if(station != -1){
                if(j == 0){
                    if(get_distance(best_station, to) > get_distance(station, to)){
                        deltaL2 = get_distance(from, station) + get_distance(station, to) - get_distance(from, to);
                        if(deltaL2 < deltaL1){
                            deltaL1 = deltaL2;
                            best_station = station;
                            index = j;
                        }
                    }
                } else{
                    deltaL2 = get_distance(from, station) + get_distance(station, to) - get_distance(from, to);
                    if(deltaL2 < deltaL1 && remaining_energy[to] + get_energy_consumption(station, to)<= BATTERY_CAPACITY){
                        deltaL1 = deltaL2;
                        best_station = station;
                        index = j;
                    }

                }
            }
            from = customer_stack[j];
        }
        int id = i - 1;
        for(int j = 0; j < sz; j++){
            int x = customer_stack[j];
            if(j == index)
                tmp_path[id--] = best_station;
            tmp_path[id--] = x;
        }
        i -= index;
        energy = BATTERY_CAPACITY;
    }

}

// Complete a tour from l to r
void GreedySearch::insert_charging_stations(Solution &sol){
    double remaining_energy[MAX_NODE];
    int tried[MAX_NODE];
    int full_path[MAX_NODE];
    int tmp_path[MAX_NODE];
    int customer_order[MAX_NODE];
    int full_length = 0;
    
    for (int i = 0; i < sol.get_num_of_tours(); i++){
        int l = sol.tours[i].left;
        int r = sol.tours[i].right;
        int subtour_length = r - l + 1;
        int iter = 0;
        double curr_remaining_energy = BATTERY_CAPACITY;
        
        for (int j = l; j <= r; j++){
            customer_order[j - l] = sol.order[j];
        }

        for (int j = 0; j < subtour_length; j++){
            remaining_energy[customer_order[j]] = 0;
            tried[customer_order[j]] = 0;
        }

        // remaining_energy[i]: remaining energy after visiting point i
        remaining_energy[customer_order[0]] = BATTERY_CAPACITY;

        int from, to;
        int num_finding_safe = 0;

        for(int j = 0; j < subtour_length - 1; j++){
            from = customer_order[j];
            to = customer_order[j + 1];
            
            if(get_energy_consumption(from, to) <= curr_remaining_energy) {
                tmp_path[iter++] = from;
                curr_remaining_energy -= get_energy_consumption(from, to);
                remaining_energy[to] = curr_remaining_energy;
                continue;
            }

            bool stop = false;
            
            while(!stop){
                num_finding_safe ++;
                if(tried[from] || num_finding_safe == MAX_NUM_FINDING_TRIALS) {
                    sol.set_fitness(INF);
                    return ;
                }
                tried[from] = 1;
                int best_station = nearest_station(from, to, curr_remaining_energy);
                if(best_station == -1) {
                    while(tried[from] && j - 1 >= 0){
                        j--; 
                        while(tmp_path[--iter] != customer_order[j]);
                        curr_remaining_energy = remaining_energy[j];
                        from = customer_order[j];
                        to = customer_order[j + 1];
                    }
                } else {
                    curr_remaining_energy = BATTERY_CAPACITY - get_energy_consumption(best_station, to);
                    if(to == 0) curr_remaining_energy = BATTERY_CAPACITY;
                    if(curr_remaining_energy <= remaining_energy[to]){
                        while(tried[from] && j - 1 >= 0){
                            j--; 
                            while(tmp_path[--iter] != customer_order[j])
                            curr_remaining_energy = remaining_energy[j];
                            from = customer_order[j];
                            to = customer_order[to];
                        }
                    } else{
                        tmp_path[iter++] = from;
                        tmp_path[iter++] = best_station;
                        remaining_energy[to] = curr_remaining_energy;
                        stop = true;
                    }
                }
            }
        }

        tmp_path[iter] = 0;
        optimize_station(tmp_path, iter, "forward");
    }
}


