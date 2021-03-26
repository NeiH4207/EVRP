#include <vector>
#include <limits.h>
#include <string>
#define CHAR_LEN 100
#define MAX_NODE 1500
#define MAX_NUM_FINDING_SAFE 10

const double INF = 2e15;
#define TERMINATION 25000*ACTUAL_PROBLEM_SIZE  	//DO NOT CHANGE THE NUMBER

extern double current_best;
extern char* problem_instance;          //Name of the instance
void init_evals();					    //initializes the evaluations
void init_current_best();				//initializes the best solution quality

struct node {
  int id;
  double x;
  double y;
};


extern void save_solution(int run);

extern void save_conv(std::vector<double> conv, std::string name);

struct solution{
  int *tour;	//this is what the fitness_evaluation function in EVRP.hpp will evaluate
  int id;
  double tour_length; //quality of the solution
  int steps; //size of the solution
  //the format of the solution is as follows:
  //*tour:  0 - 5 - 6 - 8 - 0 - 1 - 2 - 3 - 4 - 0 - 7 - 0
  //*steps: 12
  //this solution consists of three routes:
  //Route 1: 0 - 5 - 6 - 8 - 0
  //Route 2: 0 - 1 - 2 - 3 - 4 - 0
  //Route 3: 0 - 7 - 0
};

extern solution *best_sol;

extern struct node *node_list;     //List of nodes with id and x and y coordinates

//PARAMETERS THAT CAN BE USED IN YOUR ALGORITHM IMPLEMENTATION
extern int NUM_OF_CUSTOMERS;			//number of customer set
extern int ACTUAL_PROBLEM_SIZE; 		//total number of nodes
extern int NUM_OF_STATIONS;	//number of charging stations
extern int MAX_CAPACITY;				//maxmimum cargo capacity
extern int DEPOT;						//id of the depot
extern double OPTIMUM;     //Global optimum (or upper bound) of the problem instance (if known)
extern int BATTERY_CAPACITY;			//maximum energy level
extern int MIN_VEHICLES;
extern int problem_size;

extern std::vector<short int> nearest[MAX_NODE];
//METHODS THAT CAN BE USED IN YOUR ALGORITHM IMPLEMENTATION
double fitness_evaluation(int *routes, int size, bool save);		//evaluates an EVRP solution
void print_solution(int *routes, int size); 				//used to print the solution
void check_solution(int *routes, int size); 				//used to validate the solution
void read_problem(char* filename);					//reads .evrp file
double get_energy_consumption(int from, int to);	//returns the energy consumption
int get_customer_demand(int customer);				//returns the customer demand
double get_distance(int from, int to);				//returns the distance
bool is_charging_station(int node);					//returns true if node is a charging station
double get_current_best();							//returns the best solution quality from all evaluation
double get_evals();									//returns the number of evaluations
void free_EVRP();									//free memory
void compute_nearest_points();





