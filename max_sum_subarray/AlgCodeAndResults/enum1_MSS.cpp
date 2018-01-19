#include "MSS.hpp"

struct Mss cubicMSS(int A[], int n) {
    int maxSum = 0;
    int sum = 0;
    int i, j, k;
    int startIndex = 0;
    int endIndex = 0;
    int subASize = 0;
    struct Mss max;
    
    //struct Mss cubicMSS(int A[], int n) {
    //int cubicMSS(float A[], int n) {
    for (i = 0 ; i < n; i++) { 		// beginning index
        for (j = i; j < n; j++) {	// ending index
            sum = 0;
            for (k = i; k <= j; k++) {	// compute sum from i, j
                sum += A[k];
                if (sum > maxSum) {
                    startIndex = i;
                    endIndex = j;
                    maxSum = sum;
                }
            }
        }
    }
    subASize = (endIndex - startIndex) + 1;	// calculate size of subarray
    max.subArrSize = subASize;
    //float subArr[subASize];
    max.subA = (int*)malloc(sizeof(int) * max.subArrSize);
    for (i = 0; i < subASize; i++) {	// MSS subarray
        max.subA[i] = A[startIndex];
        startIndex++;
    }
    //struct Mss max = {maxSum, startIndex, endIndex};
    //struct Mss max = {maxSum, subASize, subArr};
    //printf("Max Sum: %d \n", maxSum);
    
    max.maxMss = maxSum;
    //max.startIdx = startIndex;
    //max.endIdx = endIndex;
    return max;
    //return maxSum;
}
