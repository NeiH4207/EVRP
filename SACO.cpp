#include "SACO.hpp"

#include <cstdio>
#include <iostream>
#include <cstdlib>

#include <cmath>
#include <limits>
#include <climits>
#include <algorithm>

using namespace std;


SACO::SACO (double alpha, double beta, double q, double ro, double taumax,
		int initCity) {
	ALPHA 			= alpha;
	BETA 			= beta;
	Q 				= q;
	RO 				= ro;
	TAUMAX 			= taumax;
}
SACO::~SACO () {
	for(int i=0; i<ACTUAL_PROBLEM_SIZE; i++) {
		delete [] GRAPH[i];
		delete [] CITIES[i];
		delete [] PHEROMONES[i];
		delete [] DELTAPHEROMONES[i];
		if(i < ACTUAL_PROBLEM_SIZE - 1) {
			delete [] PROBS[i];
		}
	}
	delete [] GRAPH;
	delete [] CITIES;
	delete [] PHEROMONES;
	delete [] DELTAPHEROMONES;
	delete [] PROBS;
}

void SACO::init (int _r) {
	GRAPH 			= new int*[ACTUAL_PROBLEM_SIZE];
	CITIES 			= new double*[ACTUAL_PROBLEM_SIZE];
	PHEROMONES 		= new double*[ACTUAL_PROBLEM_SIZE];
	DELTAPHEROMONES = new double*[ACTUAL_PROBLEM_SIZE];
	PROBS 			= new double*[ACTUAL_PROBLEM_SIZE-1];
	for(int i=0; i<ACTUAL_PROBLEM_SIZE; i++) {
		GRAPH[i] 			= new int[ACTUAL_PROBLEM_SIZE];
		CITIES[i] 			= new double[2];
		PHEROMONES[i] 		= new double[ACTUAL_PROBLEM_SIZE];
		DELTAPHEROMONES[i] 	= new double[ACTUAL_PROBLEM_SIZE];
		PROBS[i] 			= new double[2];
		for (int j=0; j<2; j++) {
			CITIES[i][j] = -1.0;
			PROBS[i][j]  = -1.0;
		}
		for (int j=0; j<ACTUAL_PROBLEM_SIZE; j++) {
			GRAPH[i][j] 			= 0;
			PHEROMONES[i][j] 		= 0.0;
			DELTAPHEROMONES[i][j] 	= 0.0;
		}
	}	
	randoms = new Randoms (_r);	

	for (int i=0; i<NUMBEROFANTS; i++) {
		for (int j=0; j<ACTUAL_PROBLEM_SIZE; j++) {
			Ants[i].solution[j] = -1;
		}
	}

    for (int i = 0; i < ACTUAL_PROBLEM_SIZE; i++){
        for (int j = i + 1; j < ACTUAL_PROBLEM_SIZE; j++){
            connectCITIES(i, j);
        }
    }

    best_sol = new solution;
    best_sol->tour = new int[MAX_NODE];
    best_sol->id = 1;
    best_sol->steps = 0;
    best_sol->tour_length = INF;
    // compute_nearest_points();
}


void SACO::connectCITIES (int cityi, int cityj) {
	GRAPH[cityi][cityj] = 1;
	PHEROMONES[cityi][cityj] = randoms -> Uniforme() * TAUMAX;
	GRAPH[cityj][cityi] = 1;
	PHEROMONES[cityj][cityi] = PHEROMONES[cityi][cityj];
}
void SACO::setCITYPOSITION (int city, double x, double y) {
	CITIES[city][0] = x;
	CITIES[city][1] = y;
}
void SACO::printPHEROMONES () {	
	cout << " PHEROMONES: " << endl;
	cout << "  | ";
	for (int i=0; i<ACTUAL_PROBLEM_SIZE; i++) {
		printf("%5d   ", i);
	}
	cout << endl << "- | ";
	for (int i=0; i<ACTUAL_PROBLEM_SIZE; i++) {
		cout << "--------";
	}
	cout << endl;
	for (int i=0; i<ACTUAL_PROBLEM_SIZE; i++) {
		cout << i << " | ";
		for (int j=0; j<ACTUAL_PROBLEM_SIZE; j++) {
			if (i == j) {
				printf ("%5s   ", "x");
				continue;
			}
			if (exists(i, j)) {
				printf ("%7.3f ", PHEROMONES[i][j]);
			}
			else {
				if(PHEROMONES[i][j] == 0.0) {
					printf ("%5.0f   ", PHEROMONES[i][j]);
				}
				else {
					printf ("%7.3f ", PHEROMONES[i][j]);
				}
			}
		}
		cout << endl;
	}
	cout << endl;
}

bool SACO::exists (int cityi, int cityc) {
	return (GRAPH[cityi][cityc] == 1);
}
bool SACO::vizited (int antk, int size,  int c) {
	for (int l=0; l<size; l++) {
		if (Ants[antk].solution[l] == -1) {
			break;
		}
		if (Ants[antk].solution[l] == c) {
			return true;
		}
	}
	return false;
}
double SACO::PHI (int cityi, int cityj, int antk, int size) {
	double ETAij = (double) pow (1 / get_distance(cityi, cityj), BETA);
	double TAUij = (double) pow (PHEROMONES[cityi][cityj],   ALPHA);

	double sum = 0.0;
	for (int c=1; c<=NUM_OF_CUSTOMERS; c++) {
        if (!vizited(antk, size, c)) {
            double ETA = (double) pow (1 / get_distance (cityi, c), BETA);
            double TAU = (double) pow (PHEROMONES[cityi][c],   ALPHA);
            sum += ETA * TAU;
        }	
	}
	return (ETAij * TAUij) / sum;
}


int SACO::city (int count) {
	double xi = randoms -> Uniforme();
	int i = 0;
	double total = 0;
	for (int i = 0; i < count; i++){
		total += PROBS[i][0];
	}
	xi *= total;
	double sum = PROBS[i][0];
	while (sum < xi) {
		i++;
		sum += PROBS[i][0];
	}
	return (int) PROBS[i][1];
}

void SACO::route (int antk) {
	Ants[antk].solution[0] = INITIALCITY;
    int cnt = 1;
    static int from, to;
    static double energy_temp, capacity_temp;
    energy_temp = BATTERY_CAPACITY;
    capacity_temp = MAX_CAPACITY;
    int start_depot = 0, end_depot = 0;
	int n_customer = 0;
	int n_search = 0;
	// cout << "------------------------------\n";
	
	RUN: while (n_customer < NUM_OF_CUSTOMERS){
		n_search++;
		if (n_search > ACTUAL_PROBLEM_SIZE){
			return;
		}
		from = Ants[antk].solution[cnt - 1];	
		// cout << "mid " << i << " "<< from << " " << capacity_temp << "\n";
		int count = 0;
		for (to = 1; to <= NUM_OF_CUSTOMERS; to++) {
			if (from == to) 
				continue;	
            
            // cout << to << " mid1\n";
            if (capacity_temp < get_customer_demand(to)){
                continue;
            }

			if (energy_temp > get_energy_consumption(from,to)) {
            	// cout <<energy_temp << " mid4\n";
				if (!vizited (antk, cnt, to)) {
					PROBS[count][0] = PHI (from, to, antk, cnt);
					PROBS[count][1] = (double) to;
					count++;
				}
            	// cout <<energy_temp << " endmid4\n";
			} else{
            	// cout <<energy_temp << " mid2\n";
                int best_station = Ants[antk].nearest_station(from, to, energy_temp);
				// cout << from << " " << to << " " << best_station  << "\n";
                if (best_station > 0){
                    PROBS[count][0] = PHI (from, best_station, antk, cnt);
					PROBS[count][1] = (double) best_station;
					count++;
                }
			}
		}

		// cout << "end mid\n";
		int excap = false;
		// deadlock
		if (0 == count) {
            to = DEPOT;

			// cout << "Start dead\n";
				// cout << capacity_temp << " deadlock\n";
            
			if (energy_temp > get_energy_consumption(from,to)) {
                PROBS[count][0] = PHI (from, to, antk, cnt);
                PROBS[count][1] = (double) to;
                count++;
				excap = true;
			} else{
                int best_station = Ants[antk].nearest_station(from, to, energy_temp);
				while (best_station == -1){
					cnt -= 1;
					from = Ants[antk].solution[cnt - 1];
					to = Ants[antk].solution[cnt];
					energy_temp += get_energy_consumption(from, to);
					capacity_temp += get_customer_demand(to);
					best_station = Ants[antk].nearest_station(from, to, energy_temp);

					if (not is_charging_station(to)){
						n_customer--;
					}
				}
				PROBS[count][0] = PHI (from, best_station, antk, cnt);
				PROBS[count][1] = (double) best_station;
				count++;
            }
		}
		// cout << "endmid2\n";
		int next_city = excap ? DEPOT : city(count);
		// cout << i << " " << count << " " << cnt <<  "--------\n";
		Ants[antk].solution[cnt++] = next_city;

		if (next_city == DEPOT || is_charging_station(next_city)){
			energy_temp = BATTERY_CAPACITY;
			if (next_city == DEPOT){
				capacity_temp = MAX_CAPACITY;
				end_depot = cnt - 1;
				Ants[antk].optimize_station(Ants[antk].solution, start_depot, end_depot);
				start_depot = end_depot;
			}
		} else{
			capacity_temp -= get_customer_demand(next_city);
			energy_temp -= get_energy_consumption(from,next_city);
			n_customer ++;
		}
		// for (int j = 0; j < cnt; j++){
		// 	cout << Ants[antk].solution[j] << " ";
		// }
		// cout << "\n";
	}
	// cout << "endmid3\n";
    int next_city = INITIALCITY;
	from = Ants[antk].solution[cnt - 1];
	if (energy_temp < get_energy_consumption(from,next_city)) {
		int best_station = Ants[antk].nearest_station(from, next_city, energy_temp);
		while (best_station == -1){
			cnt -= 1;
			from = Ants[antk].solution[cnt - 1];
			to = Ants[antk].solution[cnt];
			energy_temp += get_energy_consumption(from, to);
			capacity_temp += get_customer_demand(to);
			best_station = Ants[antk].nearest_station(from, next_city, energy_temp);
			if (not is_charging_station(to)){
				n_customer--;
			}
		}
    	Ants[antk].solution[cnt++] = best_station;
		if (n_customer < NUM_OF_CUSTOMERS) goto RUN;
	}
    Ants[antk].solution[cnt++] = next_city;
	end_depot = cnt - 1;
	Ants[antk].optimize_station(Ants[antk].solution, start_depot, end_depot);
    Ants[antk].set_steps(cnt);
    if(Ants[antk].is_valid_solution()) {
        Ants[antk].set_fitness(fitness_evaluation(Ants[antk].solution, cnt, true));
    } else{
        Ants[antk].set_fitness(fitness_evaluation(Ants[antk].solution, cnt, false));
        Ants[antk].add_penalty();
    }
	// cout << "endmid4\n";

    // Ants[antk].show();
	// int have[50];
	// for (int i = 0; i < cnt; i++){
	// 	have[i] = 0;
	// }
	// int _c = 0;
	// for (int i = 0; i < cnt; i++){
	// 	have[Ants[antk].solution[i]] = 1;
	// }
	// for (int i = 1; i <= NUM_OF_CUSTOMERS; i++){
	// 	if (have[i] != 1){
	// 		cout << i << "\n";
	// 		getchar();
	// 	}
	// }
}


void SACO::updatePHEROMONES () {
    sort(Ants, Ants + NUMBEROFANTS, [](Individual x, Individual y){
        return x.get_fitness() < y.get_fitness();
    });
    
	for (int k=0; k<NUMBEROFANTS - 1; k++) {
		double rlength = Ants[k].get_fitness();
		for (int r=0; r< Ants[k].get_steps()-1; r++) {
			int cityi = Ants[k].solution[r];
			int cityj = Ants[k].solution[r+1];
			DELTAPHEROMONES[cityi][cityj] += (NUMBEROFANTS - k) / rlength;
			DELTAPHEROMONES[cityj][cityi] += (NUMBEROFANTS - k) / rlength;
		}
	}

    for (int j = 0; j < best_sol->steps - 1; j++){
			int cityi = best_sol->tour[j];
			int cityj = best_sol->tour[j + 1];
			DELTAPHEROMONES[cityi][cityj] += NUMBEROFANTS / best_sol->tour_length;
			DELTAPHEROMONES[cityj][cityi] += NUMBEROFANTS / best_sol->tour_length;
    }

	for (int i=0; i<ACTUAL_PROBLEM_SIZE; i++) {
		for (int j=0; j<ACTUAL_PROBLEM_SIZE; j++) {
			PHEROMONES[i][j] = (1 - RO) * PHEROMONES[i][j] + DELTAPHEROMONES[i][j];
			DELTAPHEROMONES[i][j] = 0.0;
		}	
	}
}


void SACO::optimize () {
    for (int k = 0; k < NUMBEROFANTS; k++) {
        do {
            for (int i=0; i<MAX_NODE; i++) {
                Ants[k].solution[i] = -1;	
            }
            Ants[k].set_steps(0);
            route(k);
            // Ants[k].show();
        } while (check_solution( Ants[k].solution, Ants[k].get_steps()));
        if (Ants[k].get_fitness() < best_sol->tour_length){
            best_sol->tour_length = Ants[k].get_fitness();
            best_sol->steps = Ants[k].get_steps();    
            for(int j = 0; j < best_sol->steps; j++){
                best_sol->tour[j] = Ants[k].solution[j];
            }
        }			
        // cout << " : ant " << k << " has ended!" << endl;		
    }		
    // cout << endl << "updating PHEROMONES . . .";
    updatePHEROMONES ();
        // Ants[0].show();	
    // cout << " done!" << endl << endl;
    // printPHEROMONES ();

    cout << best_sol->tour_length << "\n";
}

void SACO::free_SACO(){
    delete[] best_sol->tour;
    delete best_sol;
}