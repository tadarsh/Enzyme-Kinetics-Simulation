#include "DNA.h"
SearchDNA::SearchDNA()
{
    
}
SearchDNA::SearchDNA(string pattern)
{
    pattern = pattern;
}

SearchDNA::SearchDNA(string sequence, string pattern)
{
    sequence = sequence;
    pattern = pattern;
}

void SearchDNA::readSequenceFromFile(string filename)
{
    ifstream fin(filename.c_str());
    getline(fin, sequence);
    fin.close();
}

void SearchDNA::setSequence(string sequence)
{
    sequence = sequence;
}

void SearchDNA::setPattern(string pattern2)
{
    pattern = pattern2;
}

string SearchDNA::getSequence()
{
    return sequence;
}

string SearchDNA::getPattern()
{
    return pattern;
}

void SearchDNA::generateSequence(long int n, string filename)
{
    /**
     * Opening the file for writing the database
     */
    
    ofstream fout(filename.c_str()); //Write mode is the default    

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

vector<long int> SearchDNA::naiveSearch()
{
   /**
     * Vector to store the indices
     */
    
    vector<long int> match_indices;

    /**
     * Naive Search
     */
        
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
        }
    }
    cout << "Matches:" << endl;
    for (int i = 0; i < match_indices.size(); ++i)
    {
        cout << match_indices[i] << " ";   
    }
    cout << endl;
    cout << "There were " << match_indices.size() << " matches" << endl; 
    
    return match_indices;
}


vector<long int> SearchDNA::BoyreMoore()
{
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
    
    int table_2d[(int)('T' - 'A') + 1][1000];
    for (int k = 0; k < 4; ++k)
    {
        for (int i = 0; i < pattern.size(); ++i)
        {
            if (table.find(make_pair(base[k], i)) != table.end())
            {
                cout << table[make_pair(base[k], i)] << " ";   
                table_2d[(int)(base[k] - 'A')][i] = table[make_pair(base[k], i)];
            }
            else
            {
                table_2d[(int)(base[k] - 'A')][i] = -1;
                cout << "n ";
            }
        }
        cout << endl;

    } 
    

    /**
     * Boyre-Moore algorithm
     */

    for (long int i = 0; i  <= sequence.size() - pattern.size(); )
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

    
    cout << "Matches:" << endl;
    for (int i = 0; i < match_indices.size(); ++i)
    {
        cout << match_indices[i] << " ";   
    }
    cout << endl;
    cout << "There were " << match_indices.size() << " matches" << endl;
    return match_indices;
}

vector<long int>  SearchDNA::KnuthMorrisPratt()
{
    /**
     * Vector to store the indices
     */
    
    vector<long int> match_indices;

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
        
    int j = 0;
    for (int i = 0; i < sequence.size() ; )
    {
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
    return match_indices;


}
