//
//  slowChange.cpp
//  MaxSubArrayAlgs
//
//  Created by Keisha Arnolds on 4/28/17.
//  Copyright © 2017 Keisha Arnolds. All rights reserved.
//

#include <limits.h>
#include "coinChange.hpp"

using std::cout;

struct coinChange changedp(int V[], int numCoins, int A) {
    int i, j;
    int T[A + 1];	// keep track of min # of coins
    int R[A + 1];	// keep track of which coins were used
    int coinsLen = numCoins; //sizeof(V)/sizeof(int);	// length of coin array V[]
    struct coinChange coinsUsed;
    //int coinsUsed[coinsLen] = {};			// used to return # of coins of V[i], init to 0
    int totalCoins;							// number of coins used to make total
    
    T[0] = 0;		// it takes 0 coins to form a total of 0
    
    
    for(i = 1; i <= A; i++) {	// initialize the arrays
        T[i] = INT_MAX;
        R[i] = -1;
    }
    
    for(j = 0; j < coinsLen; j++) {		// iterates through the coins in V
        for(i = 1; i <= A; i++) {		// iterates from 1 through A
            if(i >= V[j]) {
                if(T[i - V[j]] + 1 < T[i]) {			// pick the jth coin
                    T[i] = 1 + T[i - V[j]];			// # of jth coins
                    R[i] = j;				// keep track of jth coin in R[i]
                }
            }
        }
    }
    
    coinsUsed.minNumberOfCoins = T[A];
    
    coinsUsed.coinArray = (int*)malloc(sizeof(int) * coinsLen);
    for(int i = 0; i < coinsLen; i++) {	// initialize all elements to 0
        coinsUsed.coinArray[i] = 0;
    }
    
    if(R[A] == -1) {
        cout << "No solution possible\n";
        }
        int start = A;		// start at end of R array (see #2 in project report for explanation)
        //cout << "Coins used to form total\n";
        while (start != 0) {
            int j = R[start];
            //cout << V[j] + " ";
            coinsUsed.coinArray[j] = coinsUsed.coinArray[j] + 1;	// Add 1 to that coin
            start = start - V[j];
        }
        //cout << "\n";
        
    return coinsUsed;
}
