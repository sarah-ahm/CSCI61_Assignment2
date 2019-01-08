#ifndef RANDOM_H
#define RANDOM_H

#include <ctime>
using namespace std;

//Returns random number between low and high inclusive 
unsigned int randBetween(int low, int high);

unsigned int randBetween(int low, int high){
    srand(time(0));
    return rand() % (high - low + 1) + low;
}

#endif