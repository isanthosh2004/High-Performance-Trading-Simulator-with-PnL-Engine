#pragma once
#include "loader.h"
#include "trade.h"
#include "position.h"

class ExecutionEngine {
public:
    ExecutionEngine(PositionManager* pm);

    Trade sendMarketOrder(bool isBuy, uint32_t qty, const TickRecord& tick);

    Trade sendLimitOrder(bool isBuy, uint32_t qty, double limitPrice, const TickRecord& tick);

private:
    int nextOrderId_;
    PositionManager* pos_;
};
