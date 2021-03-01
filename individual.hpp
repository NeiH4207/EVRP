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

class Individual {
public:
    // Individual();

    /*  The positions of the tours
        decoding order to tour (1,3) : 1 3 5  (4,5) 7 8    (6,6) 9 
    */
    segment tours[NUM_OF_INDVS]; 

    /* Mapping customer and a tour */
    int tour_index[NUM_OF_INDVS];// 1 3 5 7 8 9 order

    /* Mapping customer and a tour */
    int index_of_customer[NUM_OF_INDVS];// 1 3 5 7 8 9 order

    /* The order of customers */
    int order[NUM_OF_INDVS];// 1 3 5 7 8 9 order

    int solution[MAX_NODE];

    void init(std::string _type);

    /* Generate an individual */
    void setup();
    void rand_generate();
    void opt_generate();
    void copy_order(Individual);
    /* Checking valid order of individual*/
    bool is_valid_order();
    
    /* Checking valid solution*/
    bool is_valid_solution(int *t, int size);
    
    /* Checking fully capacity, return True if invalid */
    bool check_full_capacity();
    
    /* Calculates the length of a tour */
    float calcTourLength(const std::vector<int> & tour) const;
    
    /* Returns the distance between cities i and j */
    double get_capacity_of_tour(int tour_id);

    /* Reoptimize */
    void local_search();

    void set_tour_index();

    void complete_gen();

    bool complete_subgen(int l, int r, int &cnt);

    void mutation();

    void redistribute_customer();

    void setting_path();
    
    void optimize_station(int l, int r);

    int nearest_station(int from, int to, double energy);

    int nearest_station_back(int from, int to, double energy);

    /* Shows order */
    void show();

    double get_fitness(){
        return this->fitness;
    }

    void add_penalty(){
        this->fitness *= this-> PENALTY;
    }

    int get_steps(){
        return this->steps;
    }

    int get_num_of_tours(){
        return this->num_of_tours;
    }

private:
    int steps = 0;

    /* The fitness of individuals */
    double fitness = INF;

    /* The number of tours */
    int num_of_tours = 0;
    
    /* The penalty rate for invalid solution */
    double PENALTY = 1.3;
};

