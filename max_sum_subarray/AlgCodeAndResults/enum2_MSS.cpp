#include "MSS.hpp"

struct Mss quadMSS(int A[], int n) {
    int maxSum = 0;
    int sum = 0;
    int i, j, k;
    int startIndex = 0;
    int endIndex = 0;
    int subASize = 0;
    struct Mss max;
	
    for (i = 0 ; i < n; i++) { 		// beginning index
		sum = 0;
        for (j = i; j < n; j++) {	// ending index
			sum += A[j];
			if (sum > maxSum) {
				startIndex = i;		// start index of max subarray
				endIndex = j;		// end index of max subarray
				maxSum = sum;
			}
        }
    }
    subASize = (endIndex - startIndex) + 1;	// calculate size of subarray
    max.subArrSize = subASize;
    max.subA = (int*)malloc(sizeof(int) * max.subArrSize);
	
    for (i = 0; i < subASize; i++) {	// MSS subarray
        max.subA[i] = A[startIndex];
        startIndex++;
    }
	
    //printf("Max Sum: %d \n", maxSum);
    max.maxMss = maxSum;
	
    return max;
}
