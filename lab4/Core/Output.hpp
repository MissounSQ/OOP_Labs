
#ifndef LAB4_OUTPUT_HPP
#define LAB4_OUTPUT_HPP

#include <cstdint>
#include <iosfwd>
#include <istream>
#include "Threadpool.hpp"
#include "ConcurrentQueue.hpp"
#include <vector>
#include <cstdint>
#include <iostream>

class Output {
public:

    explicit Output(std::ofstream &stream) : contentStream(stream) {};

    ~Output() = default;

    template<typename T>
    void writeStream(std::vector<T> numbers) {
        for(auto& it : numbers)
            contentStream << it << " ";
        contentStream << std::endl;
    }


private:
    std::ofstream &contentStream;
};

#endif //LAB4_OUTPUT_HPP
