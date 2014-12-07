 
/**
 * Boyre Moore Implementation
 * Author : Adarsh A Tadimari (adarsh.tadimari@gmail.com)
 */

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <map>
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
     * Finding all position of ATCG
     */

    map<char, vector<int> > position;
    
    /**
     * Initializing
     */
    vector<int> position_a;
    vector<int> position_t;
    vector<int> position_c;
    vector<int> position_g;
    
    position['A'] = position_a;
    position['T'] = position_t;
    position['C'] = position_c;
    position['G'] = position_g;

    cout << pattern << endl;
    for (int i = pattern.size() - 1; i >= 0; --i)
    {
        position[pattern[i]].push_back(pattern.size() - i - 1);
    }
    
    map<pair<char, int>, int> table;
    
    /**
     * Bulding table for the base A
     */
    char base[] = {'A', 'T', 'C', 'G'};
    
    for (int k = 0; k < 4; ++k)
    {
    
        vector<int> temp_vec = position[base[k]];
        for (int i = temp_vec.size() - 1; i >= 0; --i)
        {
            for (int j = temp_vec[i]; j >= 0; --j)
            {
                table[make_pair(base[k], j)] = temp_vec[i] - j;
            }
        }

    }

    
    /**
     * Printing table to debug
     */
    cout << "Table created..." << endl;
    
    for (int k = 0; k < 4; ++k)
    {
        for (int i = 0; i < pattern.size(); ++i)
        {
            if (table.find(make_pair(base[k], i)) != table.end())
            {
                cout << table[make_pair(base[k], i)] << " ";   
            }
            else
            {
                cout << "n ";
            }
        }
        cout << endl;

    } 
    

    /**
     * Boyre-Moore algorithm
     */

    for (long int i = 0; i < sequence.size(); )
    {
        for (int j = pattern.size() - 1; j >= 0; --j)
        {
            if (pattern[j] == sequence[i + j])
            {
                if (j == 0)
                {
                    match_indices.push_back(i);
                    i = i + 1;
                }
            }
            else
            {
                if (table.find(make_pair(sequence[i + j], pattern.size() - j -1)) != table.end())
                {
                    i = i + table[make_pair(sequence[i + j], pattern.size() - j -1)]; 
                }
                else
                {
                    i = i + j + 1;
                }
                break;
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
