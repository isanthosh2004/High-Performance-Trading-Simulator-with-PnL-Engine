#pragma once
#include <cstdint>
#include <vector>
#include <string>

struct TickRecord {
    uint64_t ts_ns;
    double price;
    uint32_t size;
    uint8_t type;
    uint8_t side;
};

std::vector<TickRecord> loadCsv(const std::string& path);
std::vector<TickRecord> loadBin(const std::string& path);
