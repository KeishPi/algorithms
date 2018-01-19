/********************************************************************************
 *  Group 11: Jacob Karcz, David Haskell, Keisha Arnold
 *  CS 325-400: Project 1
 *  Date: 4/23/2017
 *  Filename: MSS_ExpAnalysis.cpp
 *  Description: Creates a number of arrays of random integers.  Each successive array is incrementally larger than the last.
 *      The initial array size and number of arrays are given by the user as CLI arguments.
 *      Each array is analyzed to find the Maximum Sum Subarray (MSS), using four different algorithms.  
 *      The output to console is a list of runtimes (seconds) for the selected algorithm.
 *      The data is to be analyzed elsewhere, to compare the running times for the various algorithms.
 *  Citation: https://oregonstate.instructure.com/courses/1627304/assignments/6963940?module_item_id=17322236  (4/2017)
 ********************************************************************************/

//#include <iostream>		// <<cout cin>>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <limits.h>    //INT_MIN

using namespace std;

#define MAX_VALUE 10000 // array element values will be range +/-(MAX_VALUE/2)


// function declarations
int alg1_Enumeration(int A[], int);
int alg2_BetterEnumeration(int A[], int);
int max(int a, int b);//alg3
int max(int a, int b, int c);//alg3
struct Mss maxCrossingSum(int array[], int low, int mid, int hi);//alg3
struct Mss recursiveMSS(int array[], int low, int hi);//alg3
int alg4_LinearTime(int A[], int);

struct Mss {//alg3
    int maxMss;
    int subArrSize;
    int* subA;
};

int main(int argc, char *argv[])
{
    srand (time(NULL));

    int n_initial; // initial number of elements in the array
    int n; // current number of elements in the array
    int numberOfRuns; // number of runs
    int algFlag; // 1 for alg1, 2 for alg2, ...
    int tracerFlag; // 1 = ON, 0 = OFF
    int maxSubarraySum;
    struct Mss nlgn;
    clock_t timeBegin;
    clock_t timeEnd;
    float timeElapsed = 0;
    float timeElapsedSeconds = 0;
    float totalTimeElapsedSeconds = 0;

/************************************* user input from CLI arguments **************************************************/
    if (argc < 5) { fprintf(stderr,"USAGE: %s n_initial numberOfRuns algFlag tracerFlag\n", argv[0]); exit(0); } // Check usage & args
    n_initial = atoi(argv[1]); // this will change according to each alg.  try 100 to start with...
    numberOfRuns = atoi(argv[2]); // number of runs for each array size, to be averaged over. Set this to 10
    algFlag = atoi(argv[3]); // 1 for alg1, 2 for alg2, ...
    tracerFlag = atoi(argv[4]); // 1 = ON, 0 = OFF

    n = n_initial;
   // for (int arrayIncrementCounter = 0; arrayIncrementCounter < 10; ++arrayIncrementCounter) // increments the array size 10 times
   // {
    /*********************************** begin looping through array creation and analysis ****************************/
        for (int runCount = 1; runCount <= numberOfRuns; ++runCount)
        {

    /********************************** construct array of n random integers +/-(MAX_VALUE/2) ***************************/
        	int A[n]; // complete array (this gets filled by increasing amounts of random numbers)
        	if (tracerFlag == 1) printf("A[%d]: ", n); //tracer

    	    for (int i =0; i<=n; i++) {
    	        A[i] = (rand() % MAX_VALUE) - (MAX_VALUE/2);  // Fill array with n random positive integers between +/-(MAX_VALUE/2)
    	        if (tracerFlag == 1) printf("%d ", A[i]); // tracer
    	    }
    	    if (tracerFlag == 1) printf("\n"); // tracer formatting

    	    /******************************* call each alg function  *************************************************/
            if (algFlag == 1)
            {
            timeBegin = clock();
            maxSubarraySum = alg1_Enumeration(A, n); // returns maxArraySum just for testing/tracing
            timeEnd = clock();
            
            }

            if (algFlag == 2)
            {
            timeBegin = clock();
            maxSubarraySum = alg2_BetterEnumeration(A, n); // returns maxArraySum just for testing/tracing
            timeEnd = clock();

            }

            if (algFlag == 3)
            {
            timeBegin = clock();
            nlgn = recursiveMSS(A, 0, n-1); // returns nlgn just for testing/tracing
            timeEnd = clock();
            }

            if (algFlag == 4)
            {
            timeBegin = clock();
            maxSubarraySum = alg4_LinearTime(A, n); // returns maxArraySum just for testing/tracing
            timeEnd = clock();
            }

    /************************************** calculate results *************************************************************/
            if (tracerFlag == 1 && algFlag == 3)
            {
                maxSubarraySum = nlgn.maxMss;  // because alg3 uses a struct 
            }

            if (tracerFlag == 1) printf("alg%d: n: %d maxSubarraySum: %d timeElapsed: %ld\n", algFlag, n, maxSubarraySum, timeElapsed);

            timeElapsed = (float)timeEnd - (float)timeBegin;
            timeElapsedSeconds = timeElapsed/CLOCKS_PER_SEC; // convert to seconds
            //totalTimeElapsedSeconds += timeElapsedSeconds; // for averaging 

            if (tracerFlag == 1) printf("%d\t%f\n", n, timeElapsed); // clock ticks
            printf("%d\t%f\n", n, timeElapsedSeconds); // seconds - should be a very small number, but should show something...
            //if (tracerFlag == 1) printf("%d\t%f\n", n, totalTimeElapsedSeconds);   
            n = n + n_initial; // increment the amount of elements in the array
        }
        //printf("%f\n", totalTimeElapsedSeconds/numberOfRuns); // average
        
   // }
    return 0;
}




int alg1_Enumeration(int A[], int n)
{
    int i,j,k;
    int sum = 0;
    int maxSum = 0;
    for (i = 0 ; i < n; i++) {      // beginning index
        for (j = i; j < n; j++) {   // ending index
            sum = 0;
            for (k = i; k <= j; k++) {  // compute sum from i, j
                sum += A[k];
                if (sum > maxSum) {
                    maxSum = sum;
                }
            }
        }
    }
	return maxSum;
}



int alg2_BetterEnumeration(int A[], int n)
{
    int i,j;
    int sum = 0;
    int maxSum = 0;
    for (i = 0 ; i < n; i++) {      // beginning index
        sum = 0;
        for (j = i; j < n; j++) {   // ending index
            sum += A[j];
            if (sum > maxSum) {
                maxSum = sum;
            }
        }
    }
    return maxSum;
}

// this function is called by recursiveMSS()
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



int alg4_LinearTime(int A[], int n)
{
    int maxSoFar = -1,
        maxEndingHere = 0,
        startIndex = 0,
        endIndex = 0,
        s = 0,
        maxSum = 0;

    for(int i = 0; i < n; i++) {
        maxEndingHere += A[i];
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
    maxSum = maxSoFar;
    return maxSum;
}

