all : prime

prime : prime.cpp
	/usr/bin/g++ -std=c++11 prime.cpp -o prime
