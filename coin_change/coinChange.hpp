

#ifndef coinChange_hpp
#define coinChange_hpp

#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>

struct coinChange {
    int* coinArray; // array of number of each coin denomination
    int minNumberOfCoins; // minimum number of coins
    int arrSize;
};

//alg1
struct coinChange changeslow(int V[], int numCoins, int A);
int* changeCoins(int minCoins[], int V[], int length, int A);
struct coinChange changeNaive(int V[], int numCoins, int A);

//alg2
struct coinChange changegreedy(int V[], int numCoins, int A);


//alg3
struct coinChange changedp(int V[], int numCoins, int A);


#endif /* coinChange_hpp */

