#include "loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdio>

std::vector<TickRecord> loadCsv(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Cannot open CSV: " + path);

    std::vector<TickRecord> out;
    std::string line;

    // skip header
    std::getline(in, line);

    while (std::getline(in, line)) {
        std::istringstream ss(line);
        std::string token;

        TickRecord t{};
        std::getline(ss, token, ','); t.ts_ns = std::stoull(token);
        std::getline(ss, token, ','); t.price = std::stod(token);
        std::getline(ss, token, ','); t.size = std::stoul(token);
        std::getline(ss, token, ','); t.type = std::stoi(token);
        std::getline(ss, token, ','); t.side = std::stoi(token);

        out.push_back(t);
    }

    return out;
}

std::vector<TickRecord> loadBin(const std::string& path) {
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) throw std::runtime_error("Cannot open BIN: " + path);

    uint64_t n;
    fread(&n, sizeof(n), 1, f);

    std::vector<TickRecord> out(n);
    fread(out.data(), sizeof(TickRecord), n, f);
    fclose(f);

    return out;
}
