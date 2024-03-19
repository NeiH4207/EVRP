#include<iostream>
using namespace std;

#include "time.h"
#include <cmath>
#include <iomanip>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>
#include<fstream>
#include <string>
#include <assert.h>
#include <limits.h>
#include "individual.hpp"
#include "Clock.h"

const double Pr_mutate = 0.1;
int remaining_energy[MAX_NODE];
int gen_temp[MAX_NODE];
int full_path[MAX_NODE];
short int _path[MAX_NODE];


void Individual::init(string _type = "random"){
    this->num_of_tours = 0;
    if (_type == "clustering")
        opt_generate();
    else
        rand_generate();
    setup();
}
void Individual::setup(){
    reset_tour_index();
    this->fitness = INF;
    local_search();
    complete_gen();
}

void Individual::rand_generate(){
    for(int i = 0; i < NUM_OF_CUSTOMERS; i++) {
        order[i] = i + 1;
        index_of_customer[i + 1] = i;
    }

    for(int i = 0; i < NUM_OF_CUSTOMERS; i++) {
        int idx_1, idx_2;
        idx_1 = rand() % NUM_OF_CUSTOMERS;
        idx_2 = rand() % NUM_OF_CUSTOMERS;
        swap(order[idx_1], order[idx_2]);
        swap(index_of_customer[order[idx_1]], index_of_customer[order[idx_2]]);
    }
    double capacity = 0;
    int idx = 0;

    for(int i = 0; i <= NUM_OF_CUSTOMERS; i++) {
        int customer = order[i];
        double demand = get_customer_demand(customer);
        if (capacity + demand <= MAX_CAPACITY && i < NUM_OF_CUSTOMERS) {
            capacity += demand;
        } else {
            tours[this->num_of_tours++] = {idx, i - 1};
            capacity = 0;
            idx = i;
        }
    }
    reset_tour_index();
}

void Individual::copy_order(Individual other){
    for (int i = 0; i < NUM_OF_CUSTOMERS; i++){
        order[i] = other.order[i];
        tour_index[i] = other.tour_index[i];
    }
    this->num_of_tours = other.get_num_of_tours();
    for (int i = 0; i < this->num_of_tours; i++){
        tours[i].left = other.tours[i].left;
        tours[i].right = other.tours[i].right;
    }
    this->fitness = other.get_fitness();

}

// generate a new order
/*
 * This function generates a new order for a individual.
 * The order is represented as an array of customers' index
 * The array is 0-indexed, so the first customer is at index 0,
 * and the last customer is at index NUM_OF_CUSTOMERS - 1.
 */
void Individual::opt_generate() {
    vector<int> have(NUM_OF_CUSTOMERS + 1, 0);
    for(int i = 0; i < NUM_OF_CUSTOMERS; i++) {
        order[i] = i + 1;
        index_of_customer[i + 1] = i;
    }
    // shuffle the customers
    for(int i = 0; i < NUM_OF_CUSTOMERS; i++) {
        int idx_1, idx_2;
        idx_1 = rand() % NUM_OF_CUSTOMERS; // random number from 0 to NUM_OF_CUSTOMERS - 1
        idx_2 = rand() % NUM_OF_CUSTOMERS; // random number from 0 to NUM_OF_CUSTOMERS - 1
        swap(index_of_customer[order[idx_1]], index_of_customer[order[idx_2]]);
        swap(order[idx_1], order[idx_2]);
    }
    // put the customers into tours
    int first_customer_index, capacity, idx;
    idx = 0;
    while(idx < NUM_OF_CUSTOMERS) {
        // rand()%N return random number from 0 to N-1
        first_customer_index = rand()%(NUM_OF_CUSTOMERS - idx) + idx;
        // set the index of the first customer to its correct index
        index_of_customer[order[idx]] = first_customer_index;
        // swap the first customer to its correct index
        swap(order[first_customer_index], order[idx]);
        first_customer_index = idx;
        int first_customer = order[idx];
        have[first_customer] = 1;
        capacity = get_customer_demand(first_customer);
        idx++;

        // add nearest customers to the current tour
        for(int customer : nearest[first_customer]){
            if(have[customer]) continue;
            if(capacity + get_customer_demand(customer) <= MAX_CAPACITY) {
                have[customer] = 1;
                capacity += get_customer_demand(customer);
                index_of_customer[order[idx]] = index_of_customer[customer];
                swap(order[idx], order[index_of_customer[customer]]);
                idx++;
            } else{
                // the current tour is full, so create a new tour
                tours[this->num_of_tours++] = {first_customer_index, idx - 1};
                break;
            }
        }
    }
    // the last tour
    tours[this->num_of_tours++] = {first_customer_index, NUM_OF_CUSTOMERS - 1};
    if (TYPE == 1){
        balancing_capacity();
    }
}

bool Individual::check_full_capacity() {
    int capa = 0;
    for (int i = 0; i < this->num_of_tours; i++) {
        capa = 0.0;
        for (int j = tours[i].left; j <= tours[i].right; j++) {
            capa += get_customer_demand(order[j]);

        }
        if (capa > MAX_CAPACITY)
            return false;
    }
    return true;
}


bool Individual::is_valid_solution() {
    return check_solution(solution, this->steps);
}

bool Individual::is_valid_order() {
    int have[NUM_OF_CUSTOMERS + 1];

    for(int i = 0; i <= NUM_OF_CUSTOMERS; i++) {
        have[i] = 0;
    }
    
    int cnt = 0;
    for(int i = 0; i < NUM_OF_CUSTOMERS; i++) {
        if (order[i] < 1 || order[i] > NUM_OF_CUSTOMERS) return false;
        if (!have[order[i]]) {
            have[order[i]] = 1;
            cnt++;
        }
    }
    return (cnt == NUM_OF_CUSTOMERS);
}

double Individual::get_capacity_of_tour(int tour_id) {
    double capa = 0;
    for(int i = tours[tour_id].left; i <= tours[tour_id].right; i++) 
        capa += get_customer_demand(order[i]);
    
    return capa;
}

void Individual::show(){
    std::cout << "-----------\nOrder: \n";
    for(int i = 0; i < NUM_OF_CUSTOMERS; i++){
        std::cout << order[i] << " ";
    }
    cout << "\n";
    cout << "Number of steps: " << this->steps << "\n";
    for(int i = 0; i < this->steps; i++){
        std::cout << solution[i] << " ";
    }
    cout << "\n";
    for (int t = 0; t < this->num_of_tours; t++){
        cout << "Tour " << t << " : " <<  tours[t].left << " " << tours[t].right << "\n";
    }
    cout << "Fitness: " << this->fitness << "\n";
    std::cout << "-----------\n";
}

void Individual::reset_tour_index() {
    // for (int i = 0; i < NUM_OF_CUSTOMERS; i++){
    //     cout << order[i] << " ";
    // } cout << "\n";
    for(int j = 0, k; j < this->num_of_tours; j++) {
        // cout << j << " " << tours[j].left << " " << tours[j].right << "**** \n";
        for(k = tours[j].left; k <= tours[j].right; k++) {
            tour_index[order[k]] = j;
            // cout << order[k] << " " << j << "\n";
        }
    }
    // for (int i = 0; i < NUM_OF_CUSTOMERS; i++){
    //     cout << tour_index[order[i]] << " ";
    // }cout << "\n";
}

void Individual::local_search(){

    static int l, r, x, y, i, j, u0, v0, u1, v1;
    static double t1, t2;
    static bool stop;
    for(int id_tour = 0; id_tour < this->num_of_tours; id_tour++) {
        l = tours[id_tour].left;
        r = tours[id_tour].right;
        while (true) {
            stop = true;
            for(i = l; i <= r; ++i) {
                for(j = r; j > i; --j) {
                    u0 = order[i], u1 = order[i - 1];
                    v0 = order[j], v1 = order[j + 1];

                    if(i - 1 < l)
                        u1 = 0;
                    if(j + 1 > r)
                        v1 = 0;

                    t1 = get_distance(u1, u0)+ get_distance(v0, v1);
                    t2 = get_distance(u1, v0) + get_distance(u0, v1);

                    if (t1 > t2) {
                        for(x = i, y = j; x <= y; ++x, --y) {
                            swap(order[x], order[y]);
                        }
                        stop = false;
                    }

                }
            }
            if (stop) break;
        }
    }
}

void Individual::balancing_capacity(){
    reset_tour_index();
    int last_tour_idx = this->num_of_tours - 1;
    int is_customer_in_last_tour[NUM_OF_CUSTOMERS + 1];
    int l = tours[last_tour_idx].left;
    int r = tours[last_tour_idx].right;

    for (int i = 0; i <= NUM_OF_CUSTOMERS; i++){
        is_customer_in_last_tour[i] = 0;
    }
    
    for(int i = l; i <= r; i++){
        is_customer_in_last_tour[order[i]] = 1;
    }

    // choose a customer in last tour
    double last_tour_capacity = get_capacity_of_tour(last_tour_idx);
    int random_customer_idx = rand() % (r - l + 1) + l;
    int selected_customer = order[random_customer_idx];

    for(int x: nearest[selected_customer]){
        if(is_customer_in_last_tour[x]) continue;
        double curr_tour_capacity = get_capacity_of_tour(tour_index[x]);

        // The new delta is the difference between the last tour capacity and the current tour capacity
        // Make sure that the new delta is smaller than the old delta (balancing capacity)
        double new_delta = abs(last_tour_capacity + get_customer_demand(x) - (curr_tour_capacity - get_customer_demand(x)));
        double delta = abs(last_tour_capacity - curr_tour_capacity);

        if(last_tour_capacity + get_customer_demand(x) <= MAX_CAPACITY && new_delta < delta){
            // move x to last tour
            int idx = -1;
            for (int i = 0; i < last_tour_idx; ++i) {
                for (int j = tours[i].left; j <= tours[i].right; ++j) {
                    if (order[j] == x) {
                        std::swap(order[j], order[j + 1]);
                        idx = i;
                        break;
                    }
                }
                if (idx != -1) {
                    --tours[idx].right;
                    --tours[idx + 1].left;
                    break;
                }
            }
            is_customer_in_last_tour[x] = 1;
            last_tour_capacity += get_customer_demand(x);
            assert(this->num_of_tours > 0);
            tour_index[x] = last_tour_idx;
            int l = tours[last_tour_idx].left;
            int r = tours[last_tour_idx].right;
            selected_customer = order[rand() % (r - l + 1) + l];
        } else{
            break;
        }
    }
}

// Find nearest station from 'to'

int Individual::nearest_station(int from, int to, double energy) {
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

int Individual::nearest_station_back(int from, int to, double energy) {

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

void Individual::optimize_station(int *full_path, int l, int r){
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
    for(int i = r; i - 2 > l; i--){
        if(!is_charging_station(full_path[i - 1])){
            energy -= get_energy_consumption(full_path[i], full_path[i - 1]);
            continue;
        }

        sz = 0;
        static double battery;
        battery = energy;
        int from = full_path[i];
        for(int j = i - 2; j >= l; j--){
            if(is_charging_station(full_path[j])){
                break;
            }
            battery -= get_energy_consumption(from, full_path[j]);
            if(battery <= 0) break;
            _path[sz++] = full_path[j];
            from = full_path[j];
        }

        static double deltaL1, deltaL2;
        deltaL1 = get_distance(full_path[i], full_path[i - 1])
                    + get_distance(full_path[i - 1], full_path[i - 2])
                    - get_distance(full_path[i], full_path[i - 2]);

        int index = 0;
        from = full_path[i];
        int best_station = full_path[i - 1];
        for(int j = 0, to; j < sz; j++){
            to = _path[j];
            int station;
            if (TYPE == 1){
                station = nearest_station(from, to, energy);
            } else{
                nearest_station_back(from, to, energy);
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
            from = _path[j];
        }
        int id = i - 1;
        for(int j = 0; j < sz; j++){
            int x = _path[j];
            if(j == index)
                full_path[id--] = best_station;
            full_path[id--] = x;
        }
        i -= index;
        energy = BATTERY_CAPACITY;
    }

}

// Complete a tour from l to r
bool Individual::complete_subgen(int* full_path, int* gen_temp, int l, int r, int &cnt){
    int have[MAX_NODE];
    int first_id = cnt;
    double energy = BATTERY_CAPACITY;

    for(int j = l; j <= r; j++) {
        remaining_energy[j] = have[j] = 0;
    }
    static int from, to;
    // remaining_energy[i]: remaining energy after visiting point i
    remaining_energy[l] = BATTERY_CAPACITY;

    int num_finding_safe = 0;
    for(int j = l; j < r; j++) {
        from = gen_temp[j];
        to = gen_temp[j + 1];
        
        if(get_energy_consumption(from, to) <= energy) {
            full_path[cnt++] = from;
            energy -= get_energy_consumption(from, to);
            remaining_energy[j + 1] = energy;
            continue;
        }

        bool stop = false;
        
        while(!stop){
            num_finding_safe ++;
            if(have[j] || num_finding_safe == MAX_NUM_FINDING_SAFE) {
                this->fitness = INF;
                return false;
            }
            have[j] = 1;
            int best_station = nearest_station(from, to, energy);
            if(best_station == -1) {
                while(have[j] && j - 1 >= l){
                    j--; 
                    while(full_path[--cnt] != gen_temp[j]);
                    energy = remaining_energy[j];
                    from = gen_temp[j];
                    to = gen_temp[j + 1];
                }
            } else {
                energy = BATTERY_CAPACITY - get_energy_consumption(best_station, to);
                if(to == 0) energy = BATTERY_CAPACITY;
                if(energy <= remaining_energy[j + 1]){
                    while(have[j] && j - 1 >= l){
                        j--; 
                        while(full_path[--cnt] != gen_temp[j])
                        energy = remaining_energy[j];
                        from = gen_temp[j];
                        to = gen_temp[j + 1];
                    }
                } else{
                    full_path[cnt++] = from;
                    full_path[cnt++] = best_station;
                    remaining_energy[j + 1] = energy;
                    stop = true;
                }
            }
        }
    }
    l = first_id;
    r = cnt;
    full_path[r] = 0;
    remaining_energy[l] = BATTERY_CAPACITY;
    for(int i = l + 1; i <= r; i++){
        remaining_energy[i] = remaining_energy[i - 1] - get_energy_consumption(full_path[i], full_path[i - 1]);
        if(is_charging_station(full_path[i])){
            remaining_energy[i] = BATTERY_CAPACITY;
        }
    }
    if (TYPE == 1)
        optimize_station(full_path, l, r);
    return true;
}

void Individual::complete_gen() {

    // insert depot
    int cnt = 0;
    gen_temp[0] = 0;
    for(int j = 0; j < this->num_of_tours; j++) {
        auto p = tours[j];
        for(int k = p.left; k <= p.right; k++) {
            gen_temp[++cnt] = order[k];
        }
        gen_temp[++cnt] = 0;
    }
    cnt = 0;

    // complete subtour from L . R
    static int l, r;
    for(int i = 0; i < this->num_of_tours; i++){
        auto seg = tours[i];
        l = seg.left + i;
        r = seg.right + i + 2;
        //insert charging station
        if(not complete_subgen(full_path, gen_temp, l, r, cnt)) {
            this->fitness = INF;
            return;
        }
    }
    full_path[cnt++] = 0;
    if(not check_solution(full_path, cnt)) {
        this->fitness = fitness_evaluation(full_path, cnt, false);
        // cout << this->fitness << "\n";
        add_penalty();
    } else{
        this->fitness = fitness_evaluation(full_path, cnt, true);
    }

    for (int i = 0; i < cnt; i++)
        solution[i] = full_path[i];
    
    this->steps = cnt;
}

void Individual::greedy_1(){
    reset_tour_index();
    int customer = rand() % (NUM_OF_CUSTOMERS) + 1;
    static int near_customer;
    near_customer = -1;

    for(int x: nearest[customer]){
        if ((rand() % INT_MAX) / (1.0 * INT_MAX) < 0.1) continue;
        if(tour_index[x] != tour_index[customer]){
            near_customer = x;
            break;
        }
    }

    if(near_customer != -1){

        for(int i = tours[tour_index[customer]].left; i <= tours[tour_index[customer]].right; i++){
            if(order[i] == customer){
                order[i] = near_customer;
                break;
            }
        }

        for(int i = tours[tour_index[near_customer]].left; i <= tours[tour_index[near_customer]].right; i++){
            if(order[i] == near_customer){
                order[i] = customer;
                break;
            }
        }
        swap(tour_index[customer], tour_index[near_customer]);
    }
}
void Individual::greedy_2(){
    reset_tour_index();
    // choose randomly a index of order
    int customer_index = rand() % (NUM_OF_CUSTOMERS);
    int customer = order[customer_index];
    double cost = get_capacity_of_tour(tour_index[customer]);

    int near_customer = -1;
    for(int x: nearest[customer]){
        if(tour_index[x] != tour_index[customer] && cost + get_customer_demand(x) <= MAX_CAPACITY
                && tours[tour_index[x]].right - tours[tour_index[x]].left > 1){
            near_customer = x;
            break;
        }
    }

    if(near_customer != -1){
        int near_customer_tour_index = tour_index[near_customer], customer_tour_index = tour_index[customer];

        int near_customer_index = -1;
        for(int i = tours[near_customer_tour_index].left; i <= tours[near_customer_tour_index].right; i++){
            if(order[i] == near_customer){
                near_customer_index = i;
                break;
            }
        }
        
        if(customer_tour_index < near_customer_tour_index){
            swap(order[near_customer_index], order[tours[near_customer_tour_index].left]);
            tours[near_customer_tour_index].left++;
            for(int i = near_customer_tour_index - 1; i > customer_tour_index; i--){
                for(int j = tours[i].right; j >= tours[i].left; j--){
                    order[j + 1] = order[j];
                }
                tours[i].left++;
                tours[i].right++;
            }
            tours[customer_tour_index].right++;
            order[tours[customer_tour_index].right] = near_customer;
            tour_index[near_customer] = customer_tour_index;
        } else{
            swap(order[near_customer_index], order[tours[near_customer_tour_index].right]);
            tours[near_customer_tour_index].right--;
            for(int i = near_customer_tour_index + 1; i < customer_tour_index; i++){
                for(int j = tours[i].left; j <= tours[i].right; j++){
                    order[j - 1] = order[j];
                }
                tours[i].left--;
                tours[i].right--;
            }
            tours[customer_tour_index].left--;
            order[tours[customer_tour_index].left] = near_customer;
            tour_index[near_customer] = customer_tour_index;
        }
    }
}
