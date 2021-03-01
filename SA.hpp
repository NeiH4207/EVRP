
class Simulated_Annealing{
public:

    /* Implement algorithm */
    void run(int maxtime_sec);

private:
    /* */
    Individual best_solution;
    Individual current_solution;
/*
    arguments
*/
    float alpha = 160000;
    float beta = 0.333333;
    double t_current = 100.0;
    double t_cool = 0.99;
    double t_end = 0.0025;
    double t_greedy = 100.0;
    double t_v_factor = 10.0;
    double optimal_fitness = INT_MAX;

};
