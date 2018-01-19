
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

#include "MSS.hpp"

using std::cin;
using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::istringstream;
using std::ios;

#define MAX_N 1000

int main(int argc, const char * argv[]) {
    
    //variables
    int array[MAX_N];
    int success = -18;
    int n, i, j, k;
    char c;
    ifstream input;
    ofstream output;
    string inputFile;
    string outputFile = "MSS_Results.txt";
    string strng;
    stringstream strm;
    struct Mss cube, square, nlgn, linear;
    
    
    //check for input file
    if(!argv[1]) {
        cout << "usage: mss <input file name> or mss <path\\to\\your\\file.ext>\n\n";
        exit(1);
    }
    else inputFile = argv[1];
    
    //open the input & output files and read/process in the array(s)
    input.open(inputFile);
    output.open(outputFile.c_str(), ios::out | ios::app);
    if (input.good()) { //good method checks if the stream is ready to be read from.
        k = 1;
        i = 0;
        while(!input.eof()) {
            getline(input, strng);
            int size = strng.length();
            
            istringstream input(strng);
            string num;
            
            while(getline(input, num, ' ')) {
                istringstream strm(num);
                strm >> n;
                array[i] = n;
                i++;
            }
            strm.clear();
            output << "MSS Results for array " << k++ <<": ";
            for (j = 0; j < i; j++) {
                output << array[j] << " ";
            }
            //pass the array to alg 1
            cube = cubicMSS(array, i);
            output << "\n\tEnumerative Algorithm v1 \n\t\tMax Sum: " << cube.maxMss;
            output << "\n\t\tMax Subarray: ";
            for (j = 0; j < cube.subArrSize; j++) {
                output << cube.subA[j] << " ";
            }
            output << std::endl;
            
            //pass the array to alg 2
            square = quadMSS(array, i);
            output << "\n\tEnumerative Algorithm v2 \n\t\tMax Sum: "  << square.maxMss;
            output << "\n\t\tMax Subarray: ";
            for (j = 0; j < square.subArrSize; j++) {
                output << square.subA[j] << " ";
            }
            output << std::endl;
            
            //pass the array to alg 3
            nlgn = recursiveMSS(array, 0, i-1);
            output << "\n\tRecursive Algorithm \n\t\tMax Sum: "  << nlgn.maxMss;
            output << "\n\t\tMax Subarray: ";
            for (j = 0; j < nlgn.subArrSize; j++) {
                output << nlgn.subA[j] << " ";
            }
            output << std::endl;
            
            //pass the array to alg 4
            linear = linearMSS(array, i);
            output << "\n\tLinear-Time Algorithm \n\t\tMax Sum: "  << linear.maxMss;
            output << "\n\t\tMax Subarray: ";
            for (j = 0; j < linear.subArrSize; j++) {
                output << linear.subA[j] << " ";
            }
            output << std::endl;
            
            //process the next array
            //output << "\narray size: " << size << "\n";
            //output << "high index: " << i << "\n";
            output << "\n\n";
            i = 0;
        }
    }
    else {
        cout << "Unable to open file.\n Check for correct file name, extension, or path and try again./n/n";
        exit(1);
    }
    
    return 0;
}
