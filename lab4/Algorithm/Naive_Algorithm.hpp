#include "../Core/Algorithm.hpp"
#include <algorithm>
#include <cmath>

#ifndef LAB4_NAIVE_ALGORITHM_HPP
#define LAB4_NAIVE_ALGORITHM_HPP
class Naive_Algorithm : public Algorithm {
public:
    uint64_t getFactor(uint64_t number) override {
        auto radical = static_cast<uint64_t>(sqrt(number));
        for(uint64_t i = 2; i <= radical; i++) {
            uint64_t temp = number / i;
            if(temp * i == number)
                return i;
        }
    }
};
#endif //LAB4_NAIVE_ALGORITHM_HPP
