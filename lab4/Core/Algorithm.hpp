#include <cstdint>
#include <math.h>

#ifndef LAB4_ALGORITHM_HPP
#define LAB4_ALGORITHM_HPP

class Algorithm {
public:
    virtual uint64_t getFactor(uint64_t number) = 0;
    bool isPrime(uint64_t number);
};

bool Algorithm::isPrime(uint64_t number) {
    for(uint64_t i = 2; (i * i) <= number; i++) {
        if(number % i == 0)
            return false;
    }
    return true;
}

#endif //LAB4_ALGORITHM_HPP
