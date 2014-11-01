/**
 * Boyre Moore Implementation
 * Author : Adarsh A Tadimari (adarsh.tadimari@gmail.com)
 */

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <map>
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

   // cout << pattern << endl;
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
    //cout << "Table created..." << endl;
    
    /**
     * Initialzing time counter and operations (Iterations) count
     */
    clock_t start, end;
    long long int iter_count = 0;
    
    int table_2d[(int)('T' - 'A') + 1][1000];
    for (int k = 0; k < 4; ++k)
    {
        for (int i = 0; i < pattern.size(); ++i)
        {
            if (table.find(make_pair(base[k], i)) != table.end())
            {
               // cout << table[make_pair(base[k], i)] << " ";   
                table_2d[(int)(base[k] - 'A')][i] = table[make_pair(base[k], i)];
            }
            else
            {
                table_2d[(int)(base[k] - 'A')][i] = -1;
                //cout << "n ";
            }
        }
        //cout << endl;

    } 
    

    /**
     * Boyre-Moore algorithm
     */
    start = std::clock(); //Computation Starts 
    for (long int i = 0; i  <= sequence.size() - pattern.size(); )
    {
        for (int j = pattern.size() - 1; j >= 0; --j)
        {
            iter_count++;
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
                if (table_2d[(int)(sequence[i + j] - 'A')][pattern.size() - j -1] != -1)
                {
                    i = i +  table_2d[(int)(sequence[i + j] - 'A')][pattern.size() - j -1];
                }
                else
                {
                    i = i + j + 1;
                }
                break;
            }

        }

    }

    end = std::clock(); //Computation ends
    //cout << "Matches:" << endl;
    for (int i = 0; i < match_indices.size(); ++i)
    {
        //cout << match_indices[i] << " ";   
    }
    //cout << endl;
    //cout << "There were " << match_indices.size() << " matches" << endl; 
    cout << sequence.size() << " " << pattern.size() << " " << (end - start) / (double)(CLOCKS_PER_SEC / 1000) << " " << iter_count << endl;

} 
