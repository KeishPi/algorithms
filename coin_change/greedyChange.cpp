//
//  enum2.cpp
//  MaxSubArrayAlgs
//
//  Created by Keisha Arnolds on 4/19/17.
//  Copyright © 2017 Jacob Karcz. All rights reserved.
//

#include "coinChange.hpp"

struct coinChange changegreedy(int V[], int n, int A){
    // initialize struct
    struct coinChange g;
    g.coinArray = (int*)malloc(sizeof(int) * n); // same size as V[]
    //memset(g.coinArray, 0, sizeof(int) * n);
    for (int i = 0; i < n; i++) { g.coinArray[i] = 0; }
    g.minNumberOfCoins = 0;
    
    // This is the actual algoirthm - 5 lines of code...
    for(int i = (n-1); i >= 0; i--) { 	//start with the largest denomination
        while (A >= V[i]) { 	// while amount is greater than the current coin denomination
            A = A - V[i];	// subtract that denomination from our total amount
            g.coinArray[i]++; // increments the coinArray at the index of the coin denomination that was used
            g.minNumberOfCoins++; // increment for each coin used
        }
    }
    return g;
}
