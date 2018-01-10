#include <iostream>
#include <fstream>
#include <vector>
#include "Algorithm.hpp"
#include "../Algorithm/Naive_Algorithm.hpp"

#ifndef LAB4_FACTORIZATOR_HPP
#define LAB4_FACTORIZATOR_HPP

class Factorizator {
public:
    template <class T>
    static std::vector<uint64_t> factorize(uint64_t number);
    uint64_t calculate(std::vector<uint64_t>& numbers);
};

template<class T>
std::vector<uint64_t> Factorizator::factorize(uint64_t number) {
    T algorithm;
    std::vector<uint64_t> result;
    while (!algorithm.isPrime(number)) {
        uint64_t temp = algorithm.getFactor(number);
        if(!algorithm.isPrime(temp)) {
            number /= temp;
            std::vector<uint64_t> tempVec = factorize<T>(temp);
            result.insert(result.end(), tempVec.begin(), tempVec.end());
        } else {
            result.push_back(temp);
            number /= temp;
        }
    }
    if(number != 1)
        result.push_back(number);
    return result;
}

uint64_t Factorizator::calculate(std::vector<uint64_t>& numbers) {
    if(numbers.empty()) {
        throw std::runtime_error("Factor mass is empty");
    }
    uint64_t result = 1;
    for(auto& it : numbers)
        result *= it;
    return result;
}



#endif //LAB4_FACTORIZATOR_HPP
