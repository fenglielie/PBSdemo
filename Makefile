all : prime

prime : prime.cpp
	g++ -std=c++11 prime.cpp -o prime
