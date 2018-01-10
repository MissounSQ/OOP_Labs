#include <iostream>
#include "wav_core.hpp"

int main() {
    try {
        WavCore test("0.wav");
        test.printInfo();
        test.makeMono();
        test.cutSecondsFromEnd(5.0);
        test.cutSecondsFromBegin(2.0);
        test.printInfo();
        test.makeWavFile("1.wav");
    }
    catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
    std::getchar();
    return 0;
}