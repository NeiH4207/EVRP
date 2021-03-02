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
short int gen_temp[MAX_NODE];
int full_path[MAX_NODE];
short int _path[MAX_NODE];


void Individual::init(string _type = "random"){
    this->num_of_tours = 0;
    if (_type == "optimal")
        opt_generate();
    else
        rand_generate();
    setup();
}
void Individual::setup(){
    set_tour_index();
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
    set_tour_index();
}

void Individual::copy_order(Individual other){
    for (int i = 0; i < NUM_OF_CUSTOMERS; i++){
        order[i] = other.order[i];
    }
    this->num_of_tours = other.get_num_of_tours();
    for (int i = 0; i < this->num_of_tours; i++){
        tours[i] = other.tours[i];
    }
    this->fitness = other.get_fitness();

}

// generate a new order
void Individual::opt_generate() {
    vector<int> have(NUM_OF_CUSTOMERS + 1, 0);
    for(int i = 0; i < NUM_OF_CUSTOMERS; i++) {
        order[i] = i + 1;
        index_of_customer[i + 1] = i;
    }
    for(int i = 0; i < NUM_OF_CUSTOMERS; i++) {
        int idx_1, idx_2;
        idx_1 = rand() % NUM_OF_CUSTOMERS;
        idx_2 = rand() % NUM_OF_CUSTOMERS;
        swap(index_of_customer[order[idx_1]], index_of_customer[order[idx_2]]);
        swap(order[idx_1], order[idx_2]);
    }
    int first_customer_index, capacity, idx;
    idx = 0;
    while(idx < NUM_OF_CUSTOMERS) {
        // rand()%N return random number from 0 to N-1
        first_customer_index = rand()%(NUM_OF_CUSTOMERS - idx) + idx;
        index_of_customer[order[idx]] = first_customer_index;
        swap(order[first_customer_index], order[idx]);
        first_customer_index = idx;
        int first_customer = order[idx];
        have[first_customer] = 1;
        capacity = get_customer_demand(first_customer);
        idx++;

        for(int customer : nearest[first_customer]){
            if(have[customer]) continue;
            if(capacity + get_customer_demand(customer) <= MAX_CAPACITY) {
                have[customer] = 1;
                capacity += get_customer_demand(customer);
                index_of_customer[order[idx]] = index_of_customer[customer];
                swap(order[idx], order[index_of_customer[customer]]);
                idx++;
            } else{
                tours[this->num_of_tours++] = {first_customer_index, idx - 1};
                break;
            }
        }
    }
    tours[this->num_of_tours++] = {first_customer_index, NUM_OF_CUSTOMERS - 1};
    redistribute_customer();
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
    return is_valid_solution(solution, this->steps);
}

bool Individual::is_valid_solution(int *t, int size) {

    static int i, from, to;
    static double energy_temp, capacity_temp, distance_temp;
    energy_temp = BATTERY_CAPACITY;
    capacity_temp = MAX_CAPACITY;
    distance_temp = 0.0;
    for (i = 0; i < size - 1; i++) {
        from = t[i];
        to = t[i + 1];
        capacity_temp -= get_customer_demand(to);
        energy_temp -= get_energy_consumption(from,to);
        distance_temp += get_distance(from,to);
        
        if (capacity_temp < 0.0) 
            return false;
        
        if (energy_temp < 0.0) 
            return false;
        
        if (to == DEPOT) 
            capacity_temp = MAX_CAPACITY;
        
        if (is_charging_station(to) == true || to == DEPOT) 
            energy_temp = BATTERY_CAPACITY;
        
    }
    return true;
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

void Individual::set_tour_index() {
    for(int j = 0, k; j < this->num_of_tours; j++) {
        for(k = tours[j].left; k <= tours[j].right; k++) {
            tour_index[order[k]] = j;
        }
    }
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

void Individual::redistribute_customer(){
    set_tour_index();
    int customer;
    int have[NUM_OF_CUSTOMERS + 1];
    for (int i = 0; i <= NUM_OF_CUSTOMERS; i++){
        have[i] = 0;
    }
    double cap1 = 0, cap2 = 0;
    for(int i = tours[this->num_of_tours - 1].left; i <= tours[this->num_of_tours - 1].right; i++){
        have[order[i]] = 1;
    }

    // choose a customer in last tour
    cap1 = get_capacity_of_tour(this->num_of_tours - 1);
    int l = tours[this->num_of_tours - 1].left;
    int r = tours[this->num_of_tours - 1].right;
    customer = order[rand() % (r - l + 1) + l];

    for(int x: nearest[customer]){
        if(have[x]) continue;
        cap2 = get_capacity_of_tour(tour_index[x]);

        // Better ?
        if(cap1 + get_customer_demand(x) <= MAX_CAPACITY
            && abs(cap1 + get_customer_demand(x) - (cap2 - get_customer_demand(x))) < abs(cap1 - cap2)){

            // . convert
            int t = -1;
            for(int i = 0; i < this->num_of_tours - 1; i++){
                for(int j = tours[i].left; j <= tours[i].right; j++){
                    if(order[j] == x){
                        swap(order[j], order[j + 1]);
                        t = 0;
                    }
                }

                if(t == 0){
                    tours[i].right--;
                    tours[i + 1].left--;
                }
            }
            have[x] = 1;
            cap1 += get_customer_demand(x);
            assert(this->num_of_tours > 0);
            tour_index[x] = this->num_of_tours - 1;
            int l = tours[this->num_of_tours - 1].left;
            int r = tours[this->num_of_tours - 1].right;
            customer = order[rand() % (r - l + 1) + l];
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

void Individual::optimize_station(int l, int r){

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
            int station = nearest_station_back(from, to, energy);
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
bool Individual::complete_subgen(int l, int r, int &cnt){
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
    // optimal station
    l = first_id;
    r = cnt;

    remaining_energy[l] = BATTERY_CAPACITY;
    for(int i = l + 1; i <= r; i++){
        remaining_energy[i] = remaining_energy[i - 1] - get_energy_consumption(full_path[i], full_path[i - 1]);

        if(is_charging_station(full_path[i])){
            remaining_energy[i] = BATTERY_CAPACITY;
        }
    }
    optimize_station(l, r);
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
        if(not complete_subgen(l, r, cnt)) {
            this->fitness = INF;
            return;
        }
    }
    full_path[cnt++] = 0;
    if(not is_valid_solution(full_path, cnt)) {
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

void Individual::mutation(){
    double mutate_prob_1 = (double) rand() / (double) RAND_MAX;
    double mutate_prob_2 = (double) rand() / (double) RAND_MAX;
    set_tour_index();
    if(mutate_prob_1 < Pr_mutate){
        int customer = rand() % (NUM_OF_CUSTOMERS) + 1;
        static int near_customer;
        near_customer = -1;

        for(int x: nearest[customer]){
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

    if(mutate_prob_2 < Pr_mutate){
        // choose randomly a index of order
        int index_customer = rand() % (NUM_OF_CUSTOMERS);
        int customer = order[index_customer];
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

            // pick from near_customer_tour_index . customer_tour_index
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
                for(int i = near_customer_tour_index + 1; i <= customer_tour_index; i++){
                    for(int j = tours[i].left; j <= tours[i].right; j++){
                        order[j - 1] = order[j];
                    }
                    tours[i].left--;
                    tours[i].right--;
                }
                tours[customer_tour_index].right++;
                order[tours[customer_tour_index].right] = near_customer;
                tour_index[near_customer] = customer_tour_index;
            }
        }
    }
}




void Individual::greedy_1(){
    set_tour_index();
    int customer = rand() % (NUM_OF_CUSTOMERS) + 1;
    static int near_customer;
    near_customer = -1;

    for(int x: nearest[customer]){
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
    set_tour_index();
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

        // pick from near_customer_tour_index to customer_tour_index
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
            for(int i = near_customer_tour_index + 1; i <= customer_tour_index; i++){
                for(int j = tours[i].left; j <= tours[i].right; j++){
                    order[j - 1] = order[j];
                }
                tours[i].left--;
                tours[i].right--;
            }
            tours[customer_tour_index].right++;
            order[tours[customer_tour_index].right] = near_customer;
            tour_index[near_customer] = customer_tour_index;
        }
    }
}
