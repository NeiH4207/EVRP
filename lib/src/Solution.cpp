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
#include "Solution.hpp"
#include "Clock.h"

const double Pr_mutate = 0.1;
int remaining_energy[MAX_NODE];
int gen_temp[MAX_NODE];
int full_path[MAX_NODE];
short int _path[MAX_NODE];


void Solution::init(){
    this->num_of_tours = 0;
    this->fitness = INF;
    rand_generate();
}

void Solution::rand_generate(){
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

void Solution::copy_order(Solution other){
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

bool Solution::check_full_capacity() {
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


bool Solution::is_valid_solution() {
    return check_solution(this->full_path, this->steps);
}

bool Solution::is_valid_order() {
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

double Solution::get_capacity_of_tour(int tour_id) {
    double capa = 0;
    for(int i = tours[tour_id].left; i <= tours[tour_id].right; i++) 
        capa += get_customer_demand(order[i]);
    
    return capa;
}

void Solution::show(){
    std::cout << "-----------\nOrder: \n";
    for(int i = 0; i < NUM_OF_CUSTOMERS; i++){
        std::cout << order[i] << " ";
    }
    cout << "\n";
    for (int t = 0; t < this->num_of_tours; t++){
        cout << "Tour " << t << " : " <<  tours[t].left << " " << tours[t].right << "\n";
    }
    cout << "\n";
    cout << "Fitness: " << this->fitness << "\n";
    cout << "Number of steps: " << this->steps << "\n";
    for(int i = 0; i < this->steps; i++){
        std::cout << this->full_path[i] << " ";
    }
    std::cout << "\n-----------\n";
}

void Solution::reset_tour_index() {
    for(int j = 0, k; j < this->num_of_tours; j++) {
        for(k = tours[j].left; k <= tours[j].right; k++) {
            tour_index[order[k]] = j;
        }
    }
}
