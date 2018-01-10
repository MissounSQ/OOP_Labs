#ifndef LAB4_INPUT_HPP
#define LAB4_INPUT_HPP

#include <cstdint>
#include <iosfwd>
#include <istream>
#include "Threadpool.hpp"
#include "ConcurrentQueue.hpp"

class Input {
public:
    bool done;
    explicit Input(std::istream& stream) : contentStream(stream), done(false) {};
    ~Input() = default;
    template <typename T>
    void readStream(ConcurrentQueue<T>& queue) {
        if(!contentStream.good())
            throw std::runtime_error("Stream error");
        T number;
        while (contentStream >> number && !done) {
            std::cout << "Num add in que" << std::endl;
            queue.push(number);
        }
        std::cout << "File done" << std::endl;
        done = true;
    }
private:
    std::istream& contentStream;
};
#endif //LAB4_INPUT_HPP
