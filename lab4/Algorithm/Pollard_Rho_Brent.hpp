#include "../Core/Algorithm.hpp"
#include <algorithm>
#include <boost/random.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/common_factor.hpp>
#include <cmath>

#ifndef LAB4_POLLARD_RHO_ALGORITHM_HPP
#define LAB4_POLLARD_RHO_ALGORITHM_HPP
class Pollard_Brent : public Algorithm {
public:

    uint64_t GCD(uint64_t a, uint64_t b)
    {
        return b ? GCD(b, a % b) : a;
    }
    uint64_t getFactor(uint64_t number) override {
        if(number % 2 == 0)
            return 2;
        boost::random::uniform_int_distribution<uint64_t> dist(1, number - 1);
        uint64_t c = dist(gen), m = dist(gen);
        uint64_t g = 1, r = 1, k = 0;
        int64_t o = 0, y, ys, x, q, jj;
        x = 0;
        ys = 0;
        y = dist(gen);
        while(g == 1) {
            x = y;
            for(uint64_t i = 0; i < r; i++)
                y = ((y * y) % number + c) % number;
            k = 0;
            while(k < r && g == 1) {
                ys = y;
                for(uint64_t i = 0; i < std::min(m, r - k); i++) {
                    y = ((y * y)% number + c) % number;
                    jj = x - y;
                    if(jj < 0)
                        jj *= -1;
                    q = q * jj % number;
                }
                g = GCD(q, number);
                k += m;
            }
            r *= 2;
        }
        if(g == number) {
            while (true) {
                ys = ((ys * ys) % number + c) % number;
                o = abs(reinterpret_cast<int64_t >(x - ys));
                g = GCD(o, number);
                if(g > 1)
                    break;
            }
        }
        return g;

    }

private:
    boost::random::mt19937_64 gen;
};
#endif //LAB4_POLLARD_RHO_ALGORITHM_HPP
