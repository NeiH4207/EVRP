#include "Randoms.cpp"
#include "individual.hpp"

const int NUMBEROFANTS = 6;

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
	double PHI (int cityi, int cityj, int antk, int size);
	
	int city (int count);
	void route (int antk);
	
	void updatePHEROMONES ();

	
	int NUMBEROFCITIES, INITIALCITY;
	double ALPHA, BETA, Q, RO, TAUMAX;
	
	double BESTLENGTH;
	int *BESTROUTE;

	int **GRAPH, **ROUTES;
	double **CITIES, **PHEROMONES, **DELTAPHEROMONES, **PROBS;

	Randoms *randoms;
};

