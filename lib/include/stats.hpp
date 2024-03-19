#define MAX_TRIALS 	10 									//DO NOT CHANGE THE NUMBER
#define CHAR_LEN 100
#include <string>
using namespace std;

void open_stats(char* problem_instance, string algorithm, string output_path);									//creates the output file
void close_stats(void);									//stores the best values for each run
void get_mean(int r, double value);						//stores the observation from each run
void free_stats();										//free memory

