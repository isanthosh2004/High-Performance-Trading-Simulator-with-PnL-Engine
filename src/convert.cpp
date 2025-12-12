#include <iostream>
#include <fstream>
#include "loader.h"

int main(int argc, char** argv) {
    std::cout << "csv2bin START\n";

    if (argc < 3) {
        std::cerr << "usage: csv2bin input.csv output.bin\n";
        return 1;
    }

    auto data = loadCsv(argv[1]);

    std::ofstream out(argv[2], std::ios::binary);
    if (!out) {
        std::cerr << "ERROR: cannot open output file\n";
        return 1;
    }

    uint64_t n = data.size();
    out.write((char*)&n, sizeof(n));
    out.write((char*)data.data(), n * sizeof(TickRecord));

    std::cout << "Wrote " << n << " records.\n";
    return 0;
}
