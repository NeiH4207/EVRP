#include <vector>
#include <iostream>
#include <string>
#include "EVRP.hpp"

extern void compute_nearest_points();

struct segment{
    int left, right; 
    segment(){};
    segment(int l, int r): left(l), right(r){}
};

class Solution {
public:
    // Solution();

    /*  The positions of the tours
        decoding order to tour (1,3) : 1 3 5  (4,5) 7 8    (6,6) 9 
    */
    segment tours[MAX_NODE]; 

    /* Mapping customer and a tour */
    int tour_index[MAX_NODE];// 1 3 5 7 8 9 order

    /* Mapping customer and a tour */
    int index_of_customer[MAX_NODE];// 1 3 5 7 8 9 order

    /* The order of customers */
    int order[MAX_NODE];// 1 3 5 7 8 9 order

    int solution[MAX_NODE];

    void init();
    
    /* generate random initial indv*/
    void rand_generate();
    /* generate optimal initial indv*/
    void opt_generate();
    /* copy a other: order, tours and fitness*/
    void copy_order(Solution);
    /* Checking valid order of Solution*/
    bool is_valid_order();

    bool is_valid_solution(); 
    
    /* Checking fully capacity, return True if invalid */
    bool check_full_capacity();
    
    /* Calculates the length of a tour */
    float calcTourLength(const std::vector<int> & tour) const;
    
    /* Returns the distance between cities i and j */
    double get_capacity_of_tour(int tour_id);

    /* Seting index for each chromosome */
    void reset_tour_index();

    /* Shows order */
    void show();

    /* return fitness */
    double get_fitness(){
        return this->fitness;
    }
    /* return fitness */
    void set_fitness(double f){
        this->fitness = f;
    }

    /* add penalty for false indv */
    void add_penalty(){
        this->fitness *= this-> PENALTY;
    }

    /* return the number of steps in all tours */
    int get_steps(){
        return this->steps;
    }

    /* return the number of steps in all tours */
    void set_steps(int s){
        this->steps = s;
    }

    /* return the number of tours */
    int get_num_of_tours(){
        return this->num_of_tours;
    }

    void set_num_of_tours(int n){
        this->num_of_tours = n;
    }

    int TYPE = 1;

private:
    /* the number of steps in all tours */
    int steps = 0;

    /* The fitness of Solutions */
    double fitness = INF;

    /* The number of tours */
    int num_of_tours = 0;
    
    /* The penalty rate for invalid solution */
    double PENALTY = 1.3;
};

