/**
 * Naive Substring search
 * Author : Adarsh A Tadimari (adarsh.tadimari@gmail.com)
 */

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
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
     * Naive Search
     */
        
    for (long int i = 0; i <= sequence.size() - pattern.size() ;)
    {
        for (int j = 0; j < pattern.size(); ++j)
        {
            if ((sequence[i + j] != pattern[j]))
            {
                if (j == 0)
                    i = i + 1;
                else
                    i = i + j;
                break;

            }
            else if (j == pattern.size() - 1)
            {
                match_indices.push_back(i);
                i = i + 1;
            }
        }
    }
    cout << "Matches:" << endl;
    for (int i = 0; i < match_indices.size(); ++i)
    {
        cout << match_indices[i] << " ";   
    }
    cout << endl;
    cout << "There were " << match_indices.size() << " matches" << endl; 

} 
