/**
 * Naive Substring search
 * Author : Adarsh A Tadimari (adarsh.tadimari@gmail.com)
 */

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

int main(int argc, char *argv[])
{
    /**
     * Loading the large string to search on
     */
    ifstream fin(argv[1]);
    string sequence;
    getline(fin, sequence);

    /**
     * Loading the pattern
     */

    string pattern(argv[2]);

    /**
     * Vector to store the indices
     */
    
    vector<long int> match_indices;

    /**
     * Initialzing time counter and operations (Iterations) count
     */
    clock_t start, end;
    long long int iter_count = 0;

    
    /**
     * Naive Search
     */
    start = std::clock();  //Computation starts

    for (long int i = 0; i <= sequence.size() - pattern.size(); ++i)
    {
        for (int j = 0; j < pattern.size(); ++j)
        {
            if ((sequence[i + j] != pattern[j]))
            {
                break;
            }
            else if (j == pattern.size() - 1)
            {
                match_indices.push_back(i);
            }
            iter_count++;
        }
    }

    end = std::clock(); //Computation ends here

    cout << "Matches:" << endl;
    for (int i = 0; i < match_indices.size(); ++i)
    {
        cout << match_indices[i] << " ";   
    }
    cout << endl;
    cout << "There were " << match_indices.size() << " matches" << endl; 
    cout << "Time taken: " << (end - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl; 
    cout << "Iterations: " << iter_count << endl;

} 