#all: coinChange

CXX = main.cpp
CXX += coinChange.hpp
CXX += greedyChange.cpp
CXX += DynaChange.cpp
CXX += naiveChange.cpp

coinChange: main.cpp coinChange.hpp greedyChange.cpp DynaChange.cpp naiveChange.cpp
	g++ -std=c++0x main.cpp greedyChange.cpp DynaChange.cpp naiveChange.cpp -o coinChange


clean:
	rm coinChange


