
#include "individual.hpp"
#include "Clock.h"

class Simulated_Annealing{
public:

    Individual best_solution;
    Individual current_solution;
    /* Implement algorithm */
    void run(int maxtime_sec);

private:
    /* */
/*
    arguments
*/
    float alpha = 100;
    float beta = 0.333333;
    double t_current = 1.0;
    double t_cool = 0.9999;
    double t_end = 0.0001;
    double t_greedy = 100.0;
    double t_v_factor = 10.0;
    double optimal_fitness = INT_MAX;

};


extern Simulated_Annealing sa;

extern void initialize_SA();

extern void free_SA();

/*implement your heuristic in this function*/
extern void run_SA();