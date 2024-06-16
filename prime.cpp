#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using LongInt = long long;

bool isPrime(LongInt num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (LongInt i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

std::vector<LongInt> generatePrimes(LongInt limit) {
    std::vector<LongInt> primes;
    for (LongInt i = 2; i <= limit; ++i) {
        if (isPrime(i)) { primes.push_back(i); }
    }
    return primes;
}

void writePrimesToFile(const std::vector<LongInt> &primes, LongInt fileIndex) {
    std::ofstream outFile("primes_output_" + std::to_string(fileIndex) + ".txt");
    if (outFile.is_open()) {
        LongInt count = 0;
        for (const LongInt &prime : primes) {
            outFile << prime << " ";
            if (++count % 10 == 0) { outFile << "\n"; }
        }
        if (count % 10 != 0) { outFile << "\n"; }
        outFile.close();
    } else {
        std::cerr << "Unable to open file primes_output_" << fileIndex << ".txt\n";
    }
}

int main(int argc, char *argv[]) {
    LongInt defaultLimit = 1e8;
    LongInt limit = defaultLimit;

    if (argc > 1) {
        try {
            limit = std::stoll(argv[1]);
            if (limit < 2) {
                std::cerr << "Limit too small, using default value of " << defaultLimit << ".\n";
                limit = defaultLimit;
            }
        } catch (std::exception &e) {
            std::cerr << "Invalid input, using default value of " << defaultLimit << ".\n";
            limit = defaultLimit;
        }
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<LongInt> primes = generatePrimes(limit);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    size_t primesPerFile = 500000;
    size_t fileIndex = 0;
    for (size_t i = 0; i < primes.size(); i += primesPerFile) {
        std::vector<LongInt> chunk(
            primes.begin() + i,
            primes.begin() + std::min(primes.size(), i + primesPerFile));
        writePrimesToFile(chunk, fileIndex++);
    }

    std::cout << "Number of primes up to " << limit << ": " << primes.size() << "\n";
    std::cout << "Calculation time: " << std::fixed << std::setprecision(2) << duration.count() << " seconds\n";
    std::cout << "Primes are written into " << fileIndex << " files.\n";

    return 0;
}
