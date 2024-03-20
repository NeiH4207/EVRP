#include "Randoms.cpp"
#include "Solution.hpp"
#include "Clock.h"
#include <algorithm>
#include <string>

const int NUMBEROFANTS = 6;
const int NUM_OF_INDVS = 200;

class GreedySearch {
public:

    Solution best_solution;
    Solution cur_sol;
    /* Implement algorithm */
    void run();

    Solution create_random_solution();

    void greedy_search(Solution &sol);

    void clustering(Solution &sol);

    /* Reoptimize */
    void local_search(Solution &sol);

    /* Insert energy station by optimal way */
    void insert_charging_stations(Solution &sol);

    /* balanced method */
    void balancing_capacity(Solution &sol);

    /* implement algo */
    void setting_path();
    
    /* optimize_station - a sub steps in complete_gen function */
    void optimize_station(int *tmp_path, int length, std::string direction);

    /* find a nearest energy station by Dijkstra's alg from left to right */
    int nearest_station(int from, int to, double energy);

    /* find a nearest energy station by Dijkstra's alg from right to left */
    int nearest_station_back(int from, int to, double energy);


};

class SACO {
public:
	SACO (double alpha, double beta, double q, double ro, double taumax, int initCity);
	virtual ~SACO ();
	
	Solution Ants[NUMBEROFANTS];

	void init (int _r);
	
	void connectCITIES (int cityi, int cityj);
	void setCITYPOSITION (int city, double x, double y);
	
	void printPHEROMONES ();
	
	void optimize ();
	void free_SACO();

private:
	bool exists (int cityi, int cityc);
	bool vizited (int antk, int size, int c);
	double PHI (int cityi, int cityj, int *visited);
	double PHI (int cityi, int cityj, int antk, int cnt);
	
	int city (int count);
	int route (int antk);
	
	void updatePHEROMONES ();
    void perturbationPHEROMONES();
	
	int NUMBEROFCITIES, INITIALCITY;
	double ALPHA, BETA, Q, RO, TAUMAX, K_T, K_B, t_cnt, b_cnt;
    double PERTU_RATE;
	
	double BESTLENGTH;
	int *BESTROUTE;

	int **GRAPH, **ROUTES;
	double **CITIES, **PHEROMONES, **DELTAPHEROMONES, **PROBS;

	Randoms *randoms;
};

class Simulated_Annealing{
public:

    Solution best_solution;
    Solution cur_sol;
    /* Implement algorithm */
    void run(Solution &sol);

    void init(Solution ant);

    void greedy_1(Solution &sol);

    void greedy_2(Solution &sol);

private:
    /* */
/*
    arguments
*/
    float alpha = 1000;
    float beta = 0.333333;
    double t_current = 1.0;
    double t_cool = 0.9999;
    double t_end = 0.02;
    double t_greedy = 10.0;
    double t_v_factor = 10.0;
    double optimal_fitness = INT_MAX;

};

struct GSGA : public GreedySearch {
    public:
        /* The population */
        Solution pop[3 * NUM_OF_INDVS];

        /* Ranking for each indv */
        double rank[3 * NUM_OF_INDVS];

        /* initial function generate new population */
        void init();

        /* compute rank for pop */
        void compute_rank(int n);

        /* choose next indv with probability(prob) 
        using binary search
        */
        int choose_by_rank(double prob);
    
        /* repopulation */
        void Repopulation();

        void mutate(Solution &indv, std::string method, double Pr_mutate);

        /* crossover function, return two new indvs */
        void distribute_crossover(Solution parent_1, 
                                Solution parent_2, 
                                int idx);
    
        /* weheel selection method, using by ranking */
        void Selection();
    
        /* evolution */
        void Evolution();
} ;

extern GSGA GSGA_Optimizer;

extern void initialize_GSGA();

extern void free_GSGA();

/*implement your heuristic in this function*/
extern void run_GSGA();


extern Simulated_Annealing SA_optimizer;

extern void initialize_SA();

extern void free_SA();

// Other algorithms

extern GreedySearch GS_optimizer;   
extern void initialize_GS();
extern void free_GS();