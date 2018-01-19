#all: mss

CXX = main.cpp
CXX += MSS.hpp
CXX += enum1_MSS.cpp
CXX += enum2_MSS.cpp
CXX += recursiveMSS.cpp
CXX += linearMSS.cpp


mss: main.cpp MSS.hpp enum1_MSS.cpp enum2_MSS.cpp recursiveMSS.cpp linearMSS.cpp
	g++ -std=c++0x main.cpp enum1_MSS.cpp enum2_MSS.cpp recursiveMSS.cpp linearMSS.cpp -o mss


clean:
	rm mss


