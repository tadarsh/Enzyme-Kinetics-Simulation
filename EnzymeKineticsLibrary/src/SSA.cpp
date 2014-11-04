/**
 * Function implementation for the SSA library
 * Author : Adarsh A Tadimari (adarsh.tadimari@gmail.com)
 */


#include "../include/SSA.h"
#include <stdlib.h>
#include <math.h>
using namespace std;

template <class T>
pair<T, T>  SSA<T>::linear_regression_1d(vector<T> x, vector<T> y)
{
    int n = x.size();
    T var = n * inner_product(x, x) - sum_vector(x) * sum_vector(x);
    T coeff0 = inner_product(x, x) * sum_vector(y) - sum_vector(x) * inner_product(x, y);    coeff0 = coeff0 / var;

    T coeff1 = -1 * sum_vector(x) * sum_vector(y) + n * inner_product(x, y);
    coeff1 = coeff1 / var;
    return make_pair(coeff0, coeff1);

}

template<class T>
T SSA<T>::sum_vector(vector<T> x)
{
    T sum = 0;
    for (int i = 0; i < x.size(); ++i)
    {
        sum += x[i];
    }
    return sum;
}

template<class T>
T SSA<T>::inner_product(vector<T> x, vector<T> y)
{
    T prod = 0;
    if (x.size() != y.size())
    {
        cout << "Dimension mismatch";
        return 0;
    }
    for (int i = 0; i < x.size(); ++i)
    {
        prod += x[i] * y[i];
    }
    return prod;
}

template<class T>
T SSA<T>::Michaelis_Menten_Reaction(int e0, int s0, T k1f, T k1b, T k2)
{
    /**
     * Initializing variables
     */

    int p = 0;
    int es = 0;
    int e = e0;
    int s = s0;

    /**
     * Initializing Vectors to store p, es, e, s concentration wrt to time
     */
    vector<int> P;
    vector<int> ES;
    vector<int> E;
    vector<int> S;
    vector<T> time;

    P.push_back(p);
    ES.push_back(es);
    E.push_back(e);
    S.push_back(s);
    time.push_back(0);

    double t = 0;
    double r1, r2;
   /**
    * Starting the simulation
    */ 
    double reaction_flux, tau;
    
    while (1)
    {
        r1 = generate_random();
        r2 = generate_random();
 
        reaction_flux = k1f * e * s + k1b * es + k2 * es;
        tau = (T)(1.0/reaction_flux)*log(1/r1);
        
        if (r2 < k1f * e * s / reaction_flux )
        {
            e = e - 1;
            s = s - 1;
            es = es + 1;
        }
        else if (r2 < (k1f * e *s + k1b * es ) / reaction_flux)
        {
            es = es - 1;
            e = e + 1;
            s = s + 1;
        }
        else
        {
            es = es - 1;
            e = e + 1;
            p = p + 1;
        }

        t = t + tau;
        
        /**
         * Checking for boundary conditions
         */
        
        if ((e < 0 || e > e0) || (s < 0 || s > s0) || (es < 0 || es > e0 ) || (p > s0))
        {   
            e = E[E.size() - 1];
            s = S[S.size() - 1];
            es = ES[ES.size() - 1];
            p = P[P.size() - 1];
            t = time[time.size() - 1];
            continue;
        }

        P.push_back(p);
        ES.push_back(es);
        E.push_back(e);
        S.push_back(s);
        time.push_back(t);
        
        if (p == s0)
            break;
    }
    return (T) p / t;
}

template<class T>
T SSA<T>::generate_random()
{
    return 1.0 * rand()/RAND_MAX;
}

template<class T>
pair<T, T> SSA<T>::QSSA_Km_Vmax(int e0, T k1f, T k1b, T k2)
{
    T Vmax = k2 * e0;
    T Km = (k1b + k2)/k1f;
    return make_pair(Km, Vmax);
}

template<class T>
pair<T, T> SSA<T>::Simulation_Km_Vmax(int e0, T k1f, T k1b, T k2)
{
    /**
     * Iteration over different values of s0 from 100 to 1500 with
     * steps of 20
     */
    
    vector<T> v_inv;
    vector<T> s0_inv;
    for (int s0 = 100; s0 <= 1000; s0 = s0 + 20)
    {
        /**
         * Running the simulation a hundred times to
         * get a good average estimate
         */
        T v = 0, vc;
        for (int j = 0; j < 100; ++j)
        {
            vc = Michaelis_Menten_Reaction(e0, s0, k1f, k1b, k2);        
            v = v + vc; 
        }
        v = v/100;
        v_inv.push_back(1.0/v);
        s0_inv.push_back(1.0/s0);
    }
    
    pair<T, T> coeffs = linear_regression_1d(s0_inv, v_inv);

    T Vmax  = 1.0 / coeffs.first;
    T Km = coeffs.second * Vmax;
    return make_pair(Km, Vmax);

}
