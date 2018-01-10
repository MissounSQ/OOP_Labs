#include <iostream>
#include <ctime>
#include <cstdint>
#include <boost/random.hpp>
#include "Core/Factorizator.hpp"
#include "Algorithm/Pollard_Rho_Brent.hpp"
#include "Core/ConcurrentFactorizator.hpp"

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    ConcurrentFactorizator<uint64_t> factorizator(fin, fout, 6);
    factorizator.run();

    return 0;
}