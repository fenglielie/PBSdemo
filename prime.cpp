#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

bool isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

std::vector<int> generatePrimes(int limit) {
    std::vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (isPrime(i)) { primes.push_back(i); }
    }
    return primes;
}

void writePrimesToFile(const std::vector<int> &primes, int fileIndex) {
    std::ofstream outFile("primes_output_" + std::to_string(fileIndex)
                          + ".txt");
    if (outFile.is_open()) {
        int count = 0;
        for (const int &prime : primes) {
            outFile << prime << " ";
            if (++count % 10 == 0) { outFile << "\n"; }
        }
        if (count % 10 != 0) { outFile << "\n"; }
        outFile.close();
    }
    else {
        std::cerr << "Unable to open file primes_output_" << fileIndex
                  << ".txt\n";
    }
}

int main(int argc, char *argv[]) {
    int defaultLimit = 1e8;
    int limit = defaultLimit;

    if (argc > 1) {
        try {
            limit = std::stoi(argv[1]);
            if (limit < 2) {
                std::cerr << "Limit too small, using default value of "
                          << defaultLimit << ".\n";
                limit = defaultLimit;
            }
        }
        catch (std::exception &e) {
            std::cerr << "Invalid input, using default value of "
                      << defaultLimit << ".\n";
            limit = defaultLimit;
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> primes = generatePrimes(limit);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    int primesPerFile = 500000;
    int fileIndex = 0;
    for (size_t i = 0; i < primes.size(); i += primesPerFile) {
        std::vector<int> chunk(
            primes.begin() + i,
            primes.begin() + std::min(primes.size(), i + primesPerFile));
        writePrimesToFile(chunk, fileIndex++);
    }

    std::cout << "Number of primes up to " << limit << ": " << primes.size()
              << "\n";
    std::cout << "Calculation time: " << std::fixed << std::setprecision(2)
              << duration.count() << " seconds\n";
    std::cout << "Primes are written into " << fileIndex << " files.\n";

    return 0;
}
