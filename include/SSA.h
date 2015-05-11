#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

#ifndef _SSA_CLASS_H
#define _SSA_CLASS_H
template<class T>
class SSA
{
    public:
    
    //Constructor definition, rand initialized
    SSA()
    {
        srand(time(NULL));
    }

    //Function to generate random number between 0 and 1
    T generate_random();
   
    /**
     * Returns average velocity of Product formation given 
     * initial conditions and rate constants
     */
    T Michaelis_Menten_Reaction(int e0, int s0, T k1f, T k1b, T k2);
   
    //Km and Vmax assuming QSSA
    pair<T, T> QSSA_Km_Vmax(int e0, T k1f, T k1b, T k2);

    /**
     * Without QSSA, finding Km and Vmax for a given 
     * e0 by averaging over a 100 iterations
     * of a particular s0 and plotting 1/v vs 1/s0
     */
    pair<T, T> Simulation_Km_Vmax(int e0, T k1f, T k1b, T k2);
    
    pair<T, T> linear_regression_1d(vector<T> x, vector<T> y);
    
    T sum_vector(vector<T> x);
    
    T inner_product(vector<T> x, vector<T> y);
    



};
#endif
