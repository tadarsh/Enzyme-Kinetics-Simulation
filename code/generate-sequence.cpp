/**
 * Program to generate a given length of sequence consisting of the terms A, T, C, G
 * Author : Adarsh A Tadimari (adarsh.tadimari@gmail.com)
 *
 * Usage :  [bin] [length-of-sequence] [output-file]
 *      
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;


int main(int argc, char *argv[])
{
    /**
     * Taking the length of string as a command line argument
     */
    
    long int n = atol(argv[1]);

    /**
     * Opening the file for writing the database
     */
    
    ofstream fout(argv[2]); //Write mode is the default    

    /**
     * Initializing the random seed
     */
    
    srand(time(NULL));
    
    /**
     * The array elements
     */

    char bases[] = {'A', 'T', 'C', 'G'};
    int base_int;
    /**
     * Generating the sequence
     */
    
    cout << "Generating " << n << " long sequence..." << endl;

    for (int i = 0; i < n; ++i)
    {
        base_int = rand() % 4;
        fout << bases[base_int];
    }
    
    cout << "Completed" << endl;
    fout.close();

} 
