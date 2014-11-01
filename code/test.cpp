/**
 * Test file for the library created
 * Author : Adarsh A Tadimari (adarsh.tadimari@gmail.com)
 */

#include <iostream>
#include <stdio.h>
#include "DNA.h"
using namespace std;

int main(int argc, char *argv[])
{
   SearchDNA test;
   
   /**
    * Setting pattern and sequence
    */

   test.setPattern(string(argv[2]));
   test.readSequenceFromFile(string(argv[1]));
   
   /**
    * KMP alogrithm tried
    * You could use test.naiveSearch(), test.BoyreMoore() instead
    */
   vector<long int> matches = test.KnuthMorrisPratt();

} 
