#ifndef MSS_hpp
#define MSS_hpp

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>

struct Mss {
    int maxMss;
    int subArrSize;
    //std::vector<int>* subA;
    int* subA;
};

//alg1
struct Mss cubicMSS(int arr[], int size);

//alg2
struct Mss quadMSS(int A[], int n);

//alg3
int max(int a, int b);
int max(int a, int b, int c);
struct Mss maxCrossingSum(int array[], int low, int mid, int hi);
struct Mss recursiveMSS(int array[], int low, int hi);

//alg4
struct Mss linearMSS(int array[], int n);


#endif /* MSS_hpp */
