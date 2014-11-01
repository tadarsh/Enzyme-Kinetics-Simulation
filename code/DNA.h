#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
using namespace std;

class SearchDNA
{
    private:
        string sequence;
        string pattern;
    public:
        SearchDNA();
        SearchDNA(string pattern);
        SearchDNA(string sequence, string pattern);
        void readSequenceFromFile(string filename);
        void setSequence(string sequence);
        void setPattern(string pattern);
        string getSequence();
        string getPattern();
        void generateSequence(long int n, string filename);
        vector<long int> naiveSearch();
        vector<long int> BoyreMoore();
        vector<long int> KnuthMorrisPratt();

};

