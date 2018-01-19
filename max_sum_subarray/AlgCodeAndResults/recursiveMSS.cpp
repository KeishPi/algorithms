

#include <limits.h>         //INT_MIN
#include "MSS.hpp"

//find the maximum possible sum in arr[] such that arr[m] is part of it
struct Mss maxCrossingSum(int array[], int low, int mid, int hi) {
    
    //vars
    struct Mss max;
    int start = 0,
        end = 0;
    
    //left of mid.
    int sum = 0;
    int leftSum = INT_MIN; //-2147483648 in limits.h
    for (int i = mid; i >= low; i--)
    {
        sum = sum + array[i];
        if (sum > leftSum) {
            leftSum = sum;
            start = i;
        }
    }
    
    //right of mid
    sum = 0;
    int rightSum = INT_MIN;
    for (int j = mid + 1; j <= hi; j++) {
        sum = sum + array[j];
        if (sum > rightSum) {
            rightSum = sum;
            end = j;
        }
    }
    
    //return sum of elements on left and right of mid
    max.maxMss = leftSum + rightSum;
    max.subArrSize = (end - start) + 1;
    int j = start;
    max.subA = (int*)malloc(sizeof(int) * max.subArrSize);
    for (int i = 0; i <  max.subArrSize; i++) {
        max.subA[i] = array[j++];
    }
    return max;

}

//returns sum of maxium sum subarray in array[l..n]
struct Mss recursiveMSS(int array[], int low, int hi) {
    
    // Base Case: Only one element
    if (low == hi) {
        struct Mss max;
        max.subArrSize = 1;
        max.subA = (int*)malloc(sizeof(int) * max.subArrSize);
        max.subA[0] = array[low];
        max.maxMss = array[low];
        return max;
    }
                         
    // Find middle point
    int mid = (low + hi)/2;
    
    // There are three possible cases
    // a) Maximum subarray sum in left half
    struct Mss leftMSS;
    leftMSS = recursiveMSS(array, low, mid);
    // b) Maximum subarray sum in right half
    struct Mss rightMSS;
    rightMSS = recursiveMSS(array, mid + 1, hi);
    // c) Maximum subarray sum such that the subarray crosses the midpoint
    struct Mss crossMSS;
    crossMSS = maxCrossingSum(array, low, mid, hi);
    
    // Return maximum of the 3 cases
    if (leftMSS.maxMss >= rightMSS.maxMss && leftMSS.maxMss >= crossMSS.maxMss) {
        return leftMSS;
    }
    else if (rightMSS.maxMss >= leftMSS.maxMss && rightMSS.maxMss >= crossMSS.maxMss) {
        return rightMSS;
    }
    else {
        return crossMSS;
    }

}




