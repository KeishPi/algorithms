//
//  naiveChange.cpp
//  coinChangeAlgs
//
//  Created by Jacob Karcz on 4/29/17.
//  Copyright © 2017 Jacob Karcz. All rights reserved.
//

#include <stdio.h>
#include "coinChange.hpp"

/*
 To make change for A cents, start by letting K = A
 If there is a K-cent coin, then that one coin is the minimum
 Otherwise, for each value i < K,
 1) Find the minimum number of coins needed to make i cents
 2) Find the minimum number of coins needed to make K - i cents
 3) Choose the i that minimizes the sum of 1) and 2)
*/
struct coinChange changeNaive(int V[], int numCoins, int A) {
    int k = A; //the Kth value == Amount sought
    int i, j;
    //int solution_A[numCoins], solution_B[numCoins];
    struct coinChange change, change_A, change_B;
    
    change.minNumberOfCoins = INT_MAX;
    change.coinArray = (int*)std::calloc(0,(sizeof(int) * numCoins));
    //for (i = 0; i < numCoins; i++) { change.coinArray[i] = 0;}
    
    change_A.minNumberOfCoins = INT_MAX;
    change_A.coinArray =  (int*)std::calloc(0,(sizeof(int) * numCoins));
    //for (i = 0; i < numCoins; i++) { change_A.coinArray[i] = 0;}
    
    change_B.minNumberOfCoins = INT_MAX;
    change_B.coinArray =  (int*)std::calloc(0,(sizeof(int) * numCoins));
    //for (i = 0; i < numCoins; i++) { change_B.coinArray[i] = 0;}
    
    
    //base
    // if a coin is worth A, return
    for (i = 0; i < numCoins; i++) {
        if (V[i] == k) {
            change.minNumberOfCoins = 1;
            change.coinArray[i] = 1;
            return change;
        }
    }
    // else try all combinations of i and k - i coins
    for (i = 1; i < k; i++) {
        //find min # of coins to make "i" cents
        change_A = changeNaive(V, numCoins, i);
        //find min # of coins to make "k - i" cents
        change_B = changeNaive(V, numCoins, k-i);
        //choose the i that minimizes the sum of [min # of coins to make "i" cents] + [min # of coins to make "k - i" cents]
        int newCoinCount = change_A.minNumberOfCoins + change_B.minNumberOfCoins;
        if (newCoinCount < change.minNumberOfCoins) {
            change.minNumberOfCoins = newCoinCount;
            for (j = 0; j < numCoins; j++) {
                change.coinArray[j] = change_A.coinArray[j] + change_B.coinArray[j];
            }
        }
    }
    free(change_A.coinArray);
    free(change_B.coinArray);
    return change;
}
