//
//  main.cpp
//
//  Created by Jacob Karcz, Keisha Arnold, and David Haskell on 6/9/17.
//  Copyright © 2017 Jacob Karcz. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <fcntl.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>    /* INT_MIN / INT_MAX */
#include <ctime>      /* clock  */
#include <chrono>     /* precision clock */ //c++ 11+
#include <vector>
#include <math.h>	//sqrt
#include <cstring>


using std::cin;
using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::istringstream;
using std::ios;
using std::vector;

#define SIZE 100
#define TESTING 0
#define TEST_RESULTS 0 // this displays (to console) the results of each iteration within the TSP_NN_PRIMS alg

//Since we use rounding extensively and time is critical we found a fast rounding method here (very interesting!!):
//https://stackoverflow.com/questions/17035464/a-fast-method-to-round-a-double-to-a-32-bit-int-explained
#define double2int(i, d) \
{double t = ((d) + 6755399441055744.0); i = *((int *)(&t));}

/*
 #define TESTING 1

 #if TESTING ==1
    stuff
 #endif
 */

struct city{
    int id;
    int x;
    int y;
};

struct TSPSolution {
    int* routeArray; // array of id's of cities in order of travel
    int pathLength;
};

vector<city> parseCities(string inFileName, int numCities) {
    ifstream input;
    string location; // line: id x-coord y-cord
    int id=0, x=1, y=2;
    //struct city map[numCities];
    int i = 0;
    vector<city> map;
    
    input.open(inFileName);
    while(getline(input, location)) {
        istringstream input(location);
        //istringstream iss(location);
        input >> id >> x >> y;
        //iss >> id >> x >> y;
        struct city town = {id, x, y};
        map.push_back(town);
        i++;
    }
    input.close();
    return map;
}

void printCities(vector<city> map, int size) {
    for (int i = 0; i < size; i++) {
        cout << map[i].id << " " << map[i].x << " " << map[i].y << "\n";
    }
}

int countLines(string fileName) {
    //FILE* fd;
    //fd = fopen(fileName, "r");
    ifstream fd;
    fd.open(fileName);
    int lines = 0;
    string line;
    while(getline(fd, line)) {
        lines++;
    }
    //lines--; //bc printing extra city
    fd.close();
    return lines;
}

//calculates the distance between two cities
//double getDistance(struct city& p, struct city& q) {
int getDistance(struct city& p, struct city& q) {
	double dDistance;	//double var needed to save distance
	int distance;		//exact distance (dDistance) rounded to an int
	
	double xDist = p.x - q.x;
	double yDist = p.y - q.y;
	dDistance = sqrt(xDist * xDist + yDist * yDist);
	
	double2int(distance, dDistance);	//round to nearest int
	
	//distance to itself is INF
	if(distance == 0) {
		distance = INT_MAX;
	}
	
	return distance;
}

//returns a 2D array of distances between cities in our map
//double** TSP_map(vector<city> map, int size) {
int** TSP_map(vector<city> map, int size) {
	int** distMap;
	// allocate size # of rows in our 2D array
	distMap = (int**)malloc(size * (sizeof(int*)));
	// allocate size # of cols in our 2D array
	for(int i = 0; i < size; i++) {
		distMap[i] = (int*)malloc(size * (sizeof(int)));
	}
	
	// calculate distances between cities
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			distMap[i][j] = getDistance(map[i], map[j]);
		}
	}
	// return 2d array of distances
	return distMap;
}

// free the dyn memory for distMap
void freeMap(int** distMap, int size) {
	//free each row
	for(int i = 0; i < size; i++) {
		free(distMap[i]);
	}
	//free the memory of the pointers to the rows
	free(distMap);
}

struct TSPSolution TSP_NN_Prims(int **distanceMatrix, int n, std::chrono::time_point<std::chrono::system_clock> start, int timeLimit) 
{
    // initialize struct
    struct TSPSolution NN_Soln;
    NN_Soln.routeArray = (int*)malloc(sizeof(int) * n); 
    memset(NN_Soln.routeArray, 0, sizeof(int) * n);
    NN_Soln.pathLength = 0;

    struct TSPSolution NN_Soln_Best;
    NN_Soln_Best.routeArray = (int*)malloc(sizeof(int) * n); 
    memset(NN_Soln_Best.routeArray, 0, sizeof(int) * n);
    NN_Soln_Best.pathLength = INT_MAX;

    //declare timer vars
    std::chrono::time_point<std::chrono::system_clock>  iteration_end;
    std::chrono::duration<double> iteration_elapsed_seconds;
    std::time_t iteration_end_time;// exact endTime
    double iterationTime = 0;


    int numberOfDifferentStartingCitiesThatWeWouldLikeToTest = n; // change this to (1...n) for the worst/fastest to best/slowest overall solution
    int currentCity;
    int minDistance = INT_MAX;
    int NNCity; // id of Nearest Neighbor city
    int routeArrayIndex = 0;
    int i,j,k,l;

    // loop for testing different starting cities (each loop finds a completed approx solution - they are compared to find the best overall solution)
    for (i = 0; i < numberOfDifferentStartingCitiesThatWeWouldLikeToTest; ++i) 
    {
        // put all cities in Q[]
        int Q[n];
        for (j = 0; j < n; ++j)
        {
            Q[j] = 0; // 0 = not yet visited, 1 = visited
        }

        //put home city as first city in routeArray. Each iteration of (loop for overall NN_Soln_Best) starts at a different home city
        memset(NN_Soln.routeArray, 0, sizeof(int) * n);
        currentCity = i;
        routeArrayIndex = 0;
        NN_Soln.pathLength = 0;
        NN_Soln.routeArray[routeArrayIndex] = i;  // home city appears at the beginning of the routeArray

        // mark home city as visited
        Q[currentCity] = 1;
        #if TESTING == 1
        printf("n: %d\n", n);
            printf("Initial Q[%d]: ", n);
            for (int t = 0; t < n; ++t)
            {
                printf("%d ", Q[t]);
            }
            printf("\n");
        #endif
        
        do //travel to each other city once
        {
            minDistance = INT_MAX; // reset before each search (this is the ONE LINE that took me two hours to figure out)
            for (j = 0; j < n; ++j)
            {
                //find the NN of current city
                if (Q[j] == 0) // only checking unvisited cities
                {
                    if (distanceMatrix[currentCity][j] < minDistance)
                    {
                        NNCity = j; // nearest neighbor so far
                        minDistance = distanceMatrix[currentCity][j]; // minDistance so far
                    }
                }
            }
            routeArrayIndex++; 
            NN_Soln.routeArray[routeArrayIndex] =  NNCity; //add NN city to routeArray
            NN_Soln.pathLength += minDistance; // add distance to pathLength
            #if TESTING == 1
                printf("NNCity found:\tcurrentCity: %d\tNNCity: %d\tminDistance: %d\n", currentCity, NNCity, minDistance);
                printf("NN_Soln.pathLength: %d\n", NN_Soln.pathLength);
            #endif
            #if TESTING == 1
                printf("Partial NN_Soln from starting city id: %d\n", i);
                cout << NN_Soln.pathLength << std::endl;
                for(int t = 0; t < n; t++) {
                    cout << NN_Soln.routeArray[t] << "\n";
                }
            #endif
            currentCity = NNCity; //reassign current city
            Q[currentCity] = 1; // currentCity has been visited
            #if TESTING == 1
                printf("updated after finding city: %d. Q[%d]: ", currentCity, n);
                for (int t = 0; t < n; ++t)
                {
                    printf("%d ", Q[t]);
                }
                printf("\n");
            #endif

        } while (routeArrayIndex < n-1); // every city has been visited

        //travel back to home city.  NOTE: home city does NOT appear at the end of the routeArray; only at the beginning (as per specs)
        NN_Soln.pathLength += distanceMatrix[currentCity][i];

        #if TEST_RESULTS == 1
            printf("NN_Soln from starting city id: %d\n", i);
            cout << NN_Soln.pathLength << std::endl;
            /*for(int t = 0; t < n; t++) {
                cout << NN_Soln.routeArray[t] << "\n";
            }*/
        #endif

        //compare NN_Soln to NN_Soln_Best
        if (NN_Soln.pathLength < NN_Soln_Best.pathLength)
        {
            NN_Soln_Best.pathLength = NN_Soln.pathLength;
            for (k = 0; k < n; ++k)  
            {
                NN_Soln_Best.routeArray[k] = NN_Soln.routeArray[k];
            }
        }
        if (timeLimit != INT_MAX) // no timing concerns for "unlimited" time
        {
            //read precision timer at the end of each iteration
            iteration_end = std::chrono::system_clock::now();
            iteration_elapsed_seconds = iteration_end - start;                              //calc time
            iteration_end_time = std::chrono::system_clock::to_time_t(iteration_end);       //exact endTime
            iterationTime = iteration_elapsed_seconds.count();                        //save results to a variable
            iterationTime *= 1000;                                          //convert s to ms for avg
            if (iterationTime > (timeLimit - 200)) // allows 200 ms to end process
            {
                i = numberOfDifferentStartingCitiesThatWeWouldLikeToTest; // this will cause the exit of this forloop
            }
            #if TEST_RESULTS == 1
                printf("Cumulative time elapsed: %f\n", iterationTime);
            #endif
        }
    } //end forloop for testing different starting cities
    return NN_Soln_Best;
} // end TSP_NN_Prims function

void writeToFile(string fileName, struct TSPSolution tspSol, int numCities) {
   ofstream output;
   output.open(fileName);
   //int cities = sizeof(tspSol.routeArray)/sizeof(int);

   output << tspSol.pathLength << "\n";
   for (int i = 0; i < numCities; i++) {
       output << tspSol.routeArray[i] << "\n";
   }
   output.close();
}

int main(int argc, const char * argv[]) {
    
    int numCities;
    ofstream output;
    string inputFile;
    string outputExtension = ".tour";
    string outputFile;
    vector<city> map;
	int** mapMatrix;	//2d array with distances betweeen each city in our map
    struct TSPSolution soln;
    int timeLimit;
    
    //check for command line args
    if(!argv[2]) {    
        cout << "usage: " << argv[0] << " <input file name> <time limit (ms) | unlimited> or " << argv[0] << " <path\\to\\your\\file.ext> <time limit (mins) | -u (unlimited time)>\n\n";
        exit(1);
    }
    else if ( (strcmp(argv[2], "-u") != 0)  && (atoi(argv[2]) < 0) ) { cout << "command " << argv[2] << " not recognized\n"; exit(1); }

    else {
        inputFile = argv[1];
        if (strcmp(argv[2], "-u") == 0)
        {
            timeLimit = INT_MAX;
        } else{
            timeLimit = atoi(argv[2]); //mins (int)
            cout << "time limit: " << timeLimit << " min = ";
            timeLimit *= 60; //secs
            timeLimit *= 1000; // ms
            cout << timeLimit << " ms\n";
        }
    }

    //declare timer
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    std::time_t end_time;// exact endTime
    double totalTime = 0;
    double timeSum = 0;
    
    //start precision timer
    start = std::chrono::system_clock::now();
    
    //open the input & output files and read cities into array of cities
    outputFile = inputFile + outputExtension;
    numCities = countLines(inputFile);
    #if TESTING == 1
        cout << numCities << std::endl;
    #endif
    if (numCities >=0 ) {
        map = parseCities(inputFile, numCities);
        #if TESTING == 1
            printCities(map, numCities);
        #endif
    }
    else {
        cout << "Unable to open file.\n Check for correct file name, extension, or path and try again.\n\n";
        exit(1);
    }
	
	//calculate distances between cities and save in a 2d array
	mapMatrix = TSP_map(map, numCities);

	
	#if TESTING == 1
    	cout << "MAP MATRIX" << std::endl;
    	for(int i = 0; i < numCities; i++) {
    		for(int j = 0; j < numCities; j++) {
    			cout << mapMatrix[i][j] << "\t";
    		}
    		cout << "\n" << std::endl;
    	}
	#endif
	
    //find approx solution using NN Prims

    soln = TSP_NN_Prims(mapMatrix, numCities, start, timeLimit);


	//stop precision timer
	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;								//calc time
	end_time = std::chrono::system_clock::to_time_t(end);		//exact endTime
	//cout << std::fixed << elapsed_seconds.count();			//total time
	totalTime = elapsed_seconds.count();						//save results to a variable
	totalTime *= 1000;											//convert s to ms for avg
	cout << "\nTSP algorithm execution time: " << totalTime << " ms" << std::endl;
	
    #if TEST_RESULTS == 1
        cout << "NN_Soln_Best from TSP_NN_Prims:" << std::endl;
        cout << "Starting city id: " << soln.routeArray[0] << std::endl;
        cout << soln.pathLength << std::endl;
        for(int i = 0; i < numCities; i++) {
            cout << soln.routeArray[i] << "\n";
        }
        cout << "\n" << std::endl;
    #endif

    //output to file
    writeToFile(outputFile, soln, numCities);
	
	//free dyn memory!
	freeMap(mapMatrix, numCities);
    
    return 0;
}
