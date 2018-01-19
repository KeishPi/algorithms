//
//  main.cpp
//  MaxSubArrayAlgs
//
//  Created by Jacob Karcz on 4/19/17.
//  Copyright © 2017 Jacob Karcz. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <limits.h>    /* INT_MIN / INT_MAX */
#include <ctime>      /* clock  */
#include <chrono>     /* precision clock */ //c++ 11+
#include "coinChange.hpp"


using std::cin;
using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::istringstream;
using std::ios;

#define SIZE 100
#define MODE 1	    //0 == analysis, 1 == changeOutput, 2 == debug
#define TESTING 0 //1 == Amt of 1-50, 2 == Amt of 2000-2200

/*
 #define TRACERS 1
 then later use 
 #if TRACERS ==1
    stuff
 #endif
 */

int main(int argc, const char * argv[]) {
    
    //variables
    int array[SIZE], coins[SIZE];
    int n, i, j, k, x,
        Amin, Amax,
        amt, length = 0;
    ifstream input;
    ofstream output;
    string inputFile;
    string inputName;
    string outputExtension = "change.txt";
    string outputFile; //change to [input filename]change.txt from [input filename].txt
    string strng;
    stringstream strm;
    struct coinChange slow, greedy, dynamic;
    
    if(TESTING == 0) { //wildCard for testing other ranges (doesn't run naiveChange)
        Amin = 1;
        Amax = 200;
    }
    
    if(TESTING == 1) { //test algorithms 1-3
        Amin = 1;
        Amax = 19; //bc 19 was the biggest flip allowed and 18 is my lucky #
    }
    else if (TESTING == 2) {
        Amin = 2000;
        Amax = 2201;
    }
    
    //check for input file
    if(!argv[1]) {    //test algorithms 2-3
        cout << "usage: coinChange <input file name> or coinChange <path\\to\\your\\file.ext>\n\n";
        exit(1);
    }
    else inputFile = argv[1];
    
    //open the input & output files and read/process in the array(s)
    input.open(inputFile);
    inputName = inputFile.substr( 0, inputFile.find_last_of( "." ) ); //remove extension
    outputFile = inputName + outputExtension;
    output.open(outputFile.c_str(), ios::out | ios::app);
    if (input.good()) { //good method checks if the stream is ready to be read from.
        k = 1;
        i = 0;

        while(!input.eof()) {
            getline(input, strng);
            //int size = strng.length();
            
            istringstream input(strng);
            string num;
            
            while(getline(input, num, ' ')) {
                istringstream strm(num);
                strm >> n;
                array[i] = n;
                i++;
            }
            strm.clear();

            if (k % 2 != 0) {//save the coin values in a separate array
                length = i; //save arrSize for later
                //int coins[length] //save a new array each time?
                for (j = 0; j < i; j++) {
                    coins[j] = array[j];
                }
                if (MODE == 2) {
                    output << "array: ";
                    for (j = 0; j < i; j++) {
                        output << coins[j] << " ";
                    }
                    output << std::endl;
                    output << "coins: ";
                    for (j = 0; j < i; j++) {
                        output << array[j] << " ";
                    }
                    output << std::endl;
                }
                k++;
            }

            
            else {
                amt = array[0];
                if (MODE == 2) {output << "Amount: " << amt << std::endl; }
                
                //output algorithm results
                if (MODE == 1 || MODE == 2) {
                    //slowChange
                    output << "\nBrute Force Algorithm: \n";
                    output << "coin denominations: ";
                    for (j = 0; j < length; j++) {
                        output << coins[j] << " ";
                    }
                    output << std::endl;
                    //slow = changeslow(coins, length, amt);    //run alg
                    slow = changeNaive(coins, length, amt);
                    output << "change  quantities: ";
                    for (j = 0; j < length; j++) {
                        output << slow.coinArray[j] << " ";
                    }
                    output << std::endl;
                    output << "min. number of coins: " << slow.minNumberOfCoins << std::endl;
                    output << "total amount of change: " << amt << std::endl;

                    //greedy
                    output << "\nGreedy Algorithm: \n";
                    output << "coin denominations: ";
                    for (j = 0; j < length; j++) {
                        output << coins[j] << " ";
                    }
                    output << std::endl;
                    greedy = changegreedy(coins, length, amt); //run alg
                    output << "change  quantities: ";
                    for (j = 0; j < length; j++) {
                        output << greedy.coinArray[j] << " ";
                    }
                    output << std::endl;
                    output << "min. number of coins: " << greedy.minNumberOfCoins << std::endl;
                    output << "total amount of change: " << amt << std::endl;

                    
                    //dynamic
                    output << "\nDynamic Programming Algorithm: \n";
                    output << "coin denominations: ";
                    for (j = 0; j < length; j++) {
                        output << coins[j] << " ";
                    }
                    output << std::endl;
                    dynamic = changedp(coins, length, amt); //run alg
                    output << "change  quantities: ";
                    for (j = 0; j < length; j++) {
                        output << dynamic.coinArray[j] << " ";
                    }
                    output << std::endl;
                    output << "min. number of coins: " << dynamic.minNumberOfCoins << std::endl;
                    output << "total amount of change: " << amt << std::endl;

                }
                
                //output algorithm analysis data
                else if (MODE == 0) {
                    std::chrono::time_point<std::chrono::system_clock> start, end; //declare timer
                    std::chrono::duration<double> elapsed_seconds;
                    std::time_t end_time;// exact endTime
                    double totalTime = 0;
                    double timeSum = 0;
                    double avgTime = 0;
                    double coinSum = 0;
                    double avgCoins = 0;
                    output << "ALGORITHM EXECUTION TIMES IN SECONDS for: ";
                    for (j = 0; j < length; j++) {
                        output << coins[j] << ", ";
                    }
                    output << std::endl;
                    output << "Alg \tAmount \ttime1 \ttime2 \ttime3 \ttime4 \ttime5 \ttime6 \ttime7 \ttime8 \ttime9 \ttime10 \tAvgTime (ms) \tAvgCoins\n";
                    
                    //Divide & Conquer Algorithm
                    if(TESTING == 1) {
                        for (j = Amin; j < Amax; j++) {
                            amt = j;
                            timeSum = 0;
                            avgTime = 0;
                            coinSum = 0;
                            avgCoins = 0;
                            output << "naive\t" << amt << "\t";
                            for (x = 0; x < 10; x++) {
                                start = std::chrono::system_clock::now(); //start precision timer
                                    //run alg
                                //slow = changeslow(coins, length, amt);    //run alg
                                slow = changeNaive(coins, length, amt);
                                end = std::chrono::system_clock::now(); //stop precision timer
                                elapsed_seconds = end - start;          //calc time
                                end_time = std::chrono::system_clock::to_time_t(end);// exact endTime
                                output << std::fixed << elapsed_seconds.count() << "\t"; //total time -> stream
                                totalTime = elapsed_seconds.count(); //save results to a variable
                                totalTime *= 1000; //convert s to ms for avg
                                timeSum += totalTime;
                                coinSum += slow.minNumberOfCoins;
                            }
                            avgTime = timeSum / 10;
                            output << avgTime << "\t";
                            avgCoins = coinSum / 10;
                            output << avgCoins << std::endl;
                        }
                    }
                    
                    //greedy
                    for (j = Amin; j < Amax; j++) {
                        amt = j;
                        timeSum = 0;
                        avgTime = 0;
                        coinSum = 0;
                        avgCoins = 0;
                        output << "greedy\t" << amt << "\t";
                        for (x = 0; x < 10; x++) {
                            start = std::chrono::system_clock::now(); //start precision timer
                            greedy = changegreedy(coins, length, amt); //run alg
                            end = std::chrono::system_clock::now(); //stop precision timer
                            elapsed_seconds = end - start;          //calc time
                            end_time = std::chrono::system_clock::to_time_t(end);// exact endTime
                            output << std::fixed << elapsed_seconds.count() << "\t"; //total time -> stream
                            totalTime = elapsed_seconds.count(); //save results to a variable
                            totalTime *= 1000; //convert s to ms for avg
                            timeSum += totalTime;
                            coinSum += greedy.minNumberOfCoins;
                        }
                        avgTime = timeSum / 10;
                        output << avgTime << "\t";
                        avgCoins = coinSum / 10;
                        output << avgCoins << std::endl;
                    }
                        
                    //dynamic
                    for (j = Amin; j < Amax; j++) {
                        amt = j;
                        timeSum = 0;
                        avgTime = 0;
                        coinSum = 0;
                        avgCoins = 0;
                        output << "dynamic\t" << amt << "\t";
                        for (x = 0; x < 10; x++) {
                            start = std::chrono::system_clock::now(); //start precision timer
                            dynamic = changedp(coins, length, amt);   //run alg
                            end = std::chrono::system_clock::now(); //stop precision timer
                            elapsed_seconds = end - start;          //calc time
                            end_time = std::chrono::system_clock::to_time_t(end);// exact endTime
                            output << std::fixed << elapsed_seconds.count() << "\t"; //total time -> stream
                            totalTime = elapsed_seconds.count(); //save results to a variable
                            totalTime *= 1000; //convert s to ms for avg
                            timeSum += totalTime;
                            coinSum += dynamic.minNumberOfCoins;
                        }
                        avgTime = timeSum / 10;
                        output << avgTime << "\t";
                        avgCoins = coinSum / 10;
                        output << avgCoins << std::endl;
                    }
                } //end else if (MODE...)
                k++; //next!
                output << "\n\n";
            } //end else
            i = 0;
        }
    }
    else {
        cout << "Unable to open file.\n Check for correct file name, extension, or path and try again.\n\n";
        exit(1);
    }
    
    input.close();
    output.close();
    
    return 0;
}
