#pragma once
#include <cstdint>
#include <string>

struct Trade {
    int orderId;
    bool isBuy;
    double price;
    uint32_t qty;
    uint64_t ts_ns;

    std::string toString() const {
        return "Trade(orderId=" + std::to_string(orderId)
            + ", side=" + (isBuy ? "BUY" : "SELL")
            + ", price=" + std::to_string(price)
            + ", qty=" + std::to_string(qty)
            + ", ts=" + std::to_string(ts_ns) + ")";
    }
};
