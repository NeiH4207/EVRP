
const int BIGM = 9999999;
const int NUMOPT = 2;
const int NUMVI = 3;

void Simulated_Annealing::run(int maxtime_sec) {
    Clock timer;
    best_solution.init();
    current_solution.init();

    double t_current = t_current;
    double t_cool = t_cool;
    double t_end = t_end;
    double t_greedy = t_greedy;
    double alpha = alpha;
    double beta = beta;

    double improve;

    int t_v = (int) (ACTUAL_PROBLEM_SIZE * t_v_factor);
    int cnt_div = 0;
    
    int G = 0;
    
    double sqrt_n = pow(ACTUAL_PROBLEM_SIZE, 0.5);

    while (t_current > t_end && cnt_div < t_v && timer.getseconds() < maxtime_sec)
    {
        t_cool = (alpha * sqrt_n - 1.0) / (alpha * sqrt_n);
        t_greedy = ACTUAL_PROBLEM_SIZE * beta;
        // double best_improve = -1 * BIGM;

        do {
            double rand_to_select_alg = (double) rand() / (double) RAND_MAX;
            
            if(rand_to_select_alg <= 0.9){
                break;
            } else {
                break;
            }
            
            //G+1
            G++;

            if (improve > 0)
                break;
            
            /* Select best */
            // if (optimal_this.fitness > improve){
            //     optimal_this.fitness = improve;
            // }
            
            /* Termination */
            if (G >= t_greedy)
            {
                double upper = improve / t_current;
                // upper *= 10.0 * ACTUAL_PROBLEM_SIZE / optimal_this.fitness;
                // double rho = exp(upper);
                double probability = (double)rand() / RAND_MAX;

                // if(probability < rho)
                // {

                    
                // }
                
                /* Compulsive Accept */
                cnt_div ++;
                break;
            }
            
        } while (improve < 0 && timer.getseconds() < maxtime_sec);
    
        // if(improve > 0)
        // {
            
            // current_solution.setNext();
            
            // if(optimal_value > current_solution.getlength())
            // {
            //     cnt_div = 0;
                
            //     optimal_value = current_solution.getlength();

            //     tsplog(debug) << "Optimal Value is updated, " << optimal_value << TspLogger::endl;
                
            //     best_solution.copy(*current_solution);

                continue;
            //}end if(optimality)
        //}end if
        
        t_current *= t_cool;
        G = 0;
    }//end while
    
    //Ends with Local Search
    // best_solution.localSearch();
}
