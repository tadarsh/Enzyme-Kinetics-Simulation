/**
 * Testing SSA Library
 * Author : Adarsh A Tadimari (adarsh.tadimari@gmail.com)
 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include "../include/SSA.h"
#include "../src/SSA.cpp"
using namespace std;

int main(int argc, char *argv[])
{
    SSA<float> ssa;
    /**
     * Printing out the average velocity for a single simulation
     */
    cout << ssa.Michaelis_Menten_Reaction(20, 1000, 0.1, 0.01, 0.001) << endl;

}
