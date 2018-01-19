#include "MSS.hpp"


struct Mss linearMSS(int array[], int n) {
    int maxSoFar = -1,
        maxEndingHere = 0,
        startIndex = 0,
        endIndex = 0,
        s = 0;
    struct Mss max;

    
    for(int i = 0; i < n; i++) {
        maxEndingHere += array[i];
        if(maxSoFar < maxEndingHere) {
            maxSoFar = maxEndingHere;
            startIndex = s;
            endIndex = i;
        }
        if(maxEndingHere < 0) {
            maxEndingHere = 0;
            s = i + 1;
        }
    }
    
    max.subArrSize = (endIndex - startIndex) + 1;    // calculate sub array size
    max.subA = (int*)malloc(sizeof(int) * max.subArrSize);
    for (int i = 0; i < max.subArrSize; i++) {    // fill new sub array
        max.subA[i] = array[startIndex];
        startIndex++;
    }
    max.maxMss = maxSoFar;
    
    return max;
}
