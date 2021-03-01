#include<iostream>
#include <iomanip>
#include<vector>
#include<queue>
#include<string>
#include<algorithm>
#include<fstream>
#include <string>
#include <assert.h>
#include <limits.h>
#include "HMAGS.hpp"
#include "individual.hpp"
#define Sz(a) (int)(a).size()

using namespace std;

const float new_indv_rate = 0.1;
const float new_child_rate = 0.8;
const float old_indv_rate = 0.1;
int counter = 0;

solution *best_sol;   //see heuristic.hpp for the solution structure
extern double evals;

struct HMAGS {

    Individual pop[3 * NUM_OF_INDVS];
    
    void init(){
        for(int i = 0; i < NUM_OF_INDVS; i++) {
            pop[i].init("optimal");
            if (pop[i].get_fitness() < best_sol->tour_length){
                best_sol->tour_length = pop[i].get_fitness();
                best_sol->steps = pop[i].get_steps();    
                for(int j = 0; j < best_sol->steps; j++){
                    best_sol->tour[j] = pop[i].solution[j];
                }
            }
        }
    }

    void Repopulation() {
        // assert((int)pop.size() > 1);
        for(int i = 0, p1, p2; i < 2 * NUM_OF_INDVS; i += 2) {
            // choose the two parents
            p1 = rand()%(NUM_OF_INDVS);
            p2 = rand()%(NUM_OF_INDVS);
            while(p1 == p2)
                p2 = rand()%(NUM_OF_INDVS);
            distribute_crossover(pop[p1], pop[p2], NUM_OF_INDVS + i);
        }
        int cnt = 0;
        for (int i = NUM_OF_INDVS; i < 3 * NUM_OF_INDVS; i++){
            if( pop[i].get_steps() == 0){
                cnt++;
            }
            if (pop[i].get_fitness() < best_sol->tour_length){
                best_sol->tour_length = pop[i].get_fitness();
                best_sol->steps = pop[i].get_steps();    
                for(int j = 0; j < best_sol->steps; j++){
                    best_sol->tour[j] = pop[i].solution[j];
                }
            }
        }
    }

    void distribute_crossover(Individual parent_1, Individual parent_2, int idx) {

        int num = rand()%(NUM_OF_CUSTOMERS) + 1;// so ngau nhien tu 1 den size of customers
        int id1 = parent_1.tour_index[num];// customer 'num' of id1 tour in parent_1
        int id2 = parent_2.tour_index[num];// customer 'num' of id2 tour in parent_2
        int have[NUM_OF_CUSTOMERS + 1];
        int alens[NUM_OF_CUSTOMERS + 1];

        Individual child1;
        Individual child2;
        child1.copy_order(parent_1);
        child2.copy_order(parent_2);

        for(int i = 0; i <= NUM_OF_CUSTOMERS; i++){
            have[i] = 0;// have : exists in the alens or not
            alens[i] = 0;
        }

        int index = 0;

        // merge tour_id1, tour_id2 into alens
        for(int i = parent_1.tours[id1].right; i >= parent_1.tours[id1].left; i--) {
            alens[index++] = parent_1.order[i];
            have[parent_1.order[i]] = 1;
        }

        for(int i = parent_2.tours[id2].right; i >= parent_2.tours[id2].left; i--) {
            if(!have[parent_2.order[i]]) {
                alens[index++] = parent_2.order[i];
                have[parent_2.order[i]] = 1;
            }
        }
        int index2 = 0; // size of alens

        // Distribute alens to both of child1 and child2

        for(int i = 0; i < NUM_OF_CUSTOMERS; i++){
            if(have[child1.order[i]]){
                child1.order[i] = alens[--index];
            }
            if(have[child2.order[i]]){
                child2.order[i] = alens[index2++];
            }
        }
        child1.mutation();
        child2.mutation();
        pop[idx].copy_order(child1);
        pop[idx + 1].copy_order(child2);
        pop[idx].setup();
        pop[idx + 1].setup();
    }

    void Selection() {

        // for(int i = 0; i < 30; i++){
        //     cout << pop[i].get_fitness() << " ";
        // }
        // cout << "\n";

        sort(pop, pop + NUM_OF_INDVS, [](Individual x, Individual y) {
                return x.get_fitness() < y.get_fitness();
        });

        sort(pop + NUM_OF_INDVS, pop + 3 * NUM_OF_INDVS, [](Individual x, Individual y) {
                return x.get_fitness() < y.get_fitness();
        });

        for (int i = NUM_OF_INDVS * old_indv_rate; i < NUM_OF_INDVS * (old_indv_rate + new_child_rate); i++){
            pop[i].copy_order(pop[i + NUM_OF_INDVS]);
        }

        for (int i = NUM_OF_INDVS * (old_indv_rate + new_child_rate); i < NUM_OF_INDVS; i++){
            pop[i].init("optimal");
        }

        // for(int i = 0; i < 30; i++){
        //     cout << pop[i].get_fitness() << " ";
        // }
        // cout << "\n";


    }

    void Evolution() {
        // cout << counter ++ << " " << best_sol->tour_length << "\n";
        Repopulation();
        Selection();
    }

} ;

HMAGS hmags;

/*initialize the structure of your heuristic in this function*/

void initialize_HMAGS() {
    best_sol = new solution;
    best_sol->tour = new int[MAX_NODE];
    best_sol->id = 1;
    best_sol->steps = 0;
    best_sol->tour_length = INF;
    compute_nearest_points();
    hmags.init();
}

void free_HMAGS(){
    delete[] best_sol->tour;
    delete best_sol;
}

/*implement your heuristic in this function*/
void run_HMAGS() {
    hmags.Evolution();
}
