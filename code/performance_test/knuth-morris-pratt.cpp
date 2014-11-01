/**
 * Knuth-Morris-Pratt Algorithm for substring search
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

    vector<int> lps(pattern.size());

    /**
     * Computing the lps array
     */

    int len = 0; //length of the previous longest prefix suffix

    lps[0] = 0;
    int i = 1;
    while (i < pattern.size())
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
                len = lps[len - 1];             
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }

    /**
     * KMP algorithm
     */
    
    cout << "Searching for the substring" << endl;
    start = std::clock();    
    int j = 0;
    for (int i = 0; i < sequence.size() ; )
    {
        iter_count++;
        if (pattern[j] == sequence[i])
        {
            j++;
            i++;
        }
        
        if (j == pattern.size())
        {
            match_indices.push_back(i - j);
            j = lps[j - 1];
        }
        else if (pattern[j] != sequence[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }

    }
    end = std::clock();
    /**
     * Printing out the matches
     */

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
