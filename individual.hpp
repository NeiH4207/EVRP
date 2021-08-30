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
    segment tours[MAX_NODE]; 

    /* Mapping customer and a tour */
    int tour_index[MAX_NODE];// 1 3 5 7 8 9 order

    /* Mapping customer and a tour */
    int index_of_customer[MAX_NODE];// 1 3 5 7 8 9 order

    /* The order of customers */
    int order[MAX_NODE];// 1 3 5 7 8 9 order

    int solution[MAX_NODE];

    void init(std::string _type);

    /* Generate an individual */
    void setup();
    /* generate random initial indv*/
    void rand_generate();
    /* generate optimal initial indv*/
    void opt_generate();
    /* copy a other: order, tours and fitness*/
    void copy_order(Individual);
    /* Checking valid order of individual*/
    bool is_valid_order();
    
    /* Checking valid solution*/
    bool is_valid_solution(int *t, int size); 
    bool is_valid_solution(); // this
    
    /* Checking fully capacity, return True if invalid */
    bool check_full_capacity();
    
    /* Calculates the length of a tour */
    float calcTourLength(const std::vector<int> & tour) const;
    
    /* Returns the distance between cities i and j */
    double get_capacity_of_tour(int tour_id);

    /* Reoptimize */
    void local_search();

    /* Seting index for each chromosome */
    void set_tour_index();

    /* Insert energy station by optimal way */
    void complete_gen();

    /* Insert energy station by optimal way for each tours */
    bool complete_subgen(int* full_path, int * gen_temp, int l, int r, int &cnt);

    /* mutation method for GA */
    void mutation();

    /* greedy method for SA */
    void greedy_1();
    void greedy_2();

    /* balanced method */
    void redistribute_customer();

    /* implement algo */
    void setting_path();
    
    /* optimize_station - a sub steps in complete_gen function */
    void optimize_station(int *full_path, int l, int r);

    /* find a nearest energy station by Dijkstra's alg from left to right */
    int nearest_station(int from, int to, double energy);

    /* find a nearest energy station by Dijkstra's alg from right to left */
    int nearest_station_back(int from, int to, double energy);

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

    /* The fitness of individuals */
    double fitness = INF;

    /* The number of tours */
    int num_of_tours = 0;
    
    /* The penalty rate for invalid solution */
    double PENALTY = 1.3;
};

