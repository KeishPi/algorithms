
main.cpp contains all the pertinent source code. 
A makefile is provided for convenience.
When entering the input file, include the extension. 
If the file is in a separate directory, include the path as part of the name:
	../fileDir/testing/inputfile.txt

*to run with 3 minute limit, see command line 2 of “to run:” bellow.

to compile:
	make
	make ftp
	g++ -std=c++11 main.cpp -o tsp

to run:
	tsp inputfile.txt -u
		Program will run TSP algorithm on inputfile.txt and give the 
		best possible solution, without any time constraint (-u == unlimited).

	tsp inputfile.txt <int>
		Program will run TSP algorithm and report the best solution it can 
		find for inputfile.txt within the constraint of the time limit imposed
		(in minutes, represented as whole numbers)

		In either case, the algorithm results will be printed to 	
		inputfile.txt.tour, within the original file’s directory.
		The first line of the file is the best path length, and the subsequent 
		lines represent the city IDs in the order that they should be visited. 

to remove executable:
	make clean