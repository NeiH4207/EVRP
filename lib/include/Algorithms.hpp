#include "Randoms.cpp"
#include "individual.hpp"
#include "Clock.h"
#include <algorithm>

const int NUMBEROFANTS = 6;
const int NUM_OF_INDVS = 200;

class SACO {
public:
	SACO (double alpha, double beta, double q, double ro, double taumax, int initCity);
	virtual ~SACO ();
	
	Individual Ants[NUMBEROFANTS];

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

    Individual best_solution;
    Individual cur_sol;
    /* Implement algorithm */
    void run(Individual &sol);

    void init(Individual ant);

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

class GreedySearch {
public:

    Individual best_solution;
    Individual cur_sol;
    /* Implement algorithm */
    void run(Individual &sol);

    void init();

};

struct HMAGS {
  
    /* The population */
    Individual pop[3 * NUM_OF_INDVS];

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

    /* crossover function, return two new indvs */
    void distribute_crossover(Individual parent_1, 
                              Individual parent_2, 
                              int idx);
  
    /* weheel selection method, using by ranking */
    void Selection();
  
    /* evolution */
    void Evolution();

} ;

extern HMAGS hmags;

extern void initialize_HMAGS();

extern void free_HMAGS();

/*implement your heuristic in this function*/
extern void run_HMAGS();


extern Simulated_Annealing SA_optimizer;

extern void initialize_SA();

extern void free_SA();

// Other algorithms

extern GreedySearch gs_optimizer;   
extern void initialize_GS();
extern void free_GS();