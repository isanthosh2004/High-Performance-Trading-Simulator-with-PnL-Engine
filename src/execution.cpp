#include "execution.h"
#include <iostream>

ExecutionEngine::ExecutionEngine(PositionManager* pm)
    : nextOrderId_(1), pos_(pm) {}

Trade ExecutionEngine::sendMarketOrder(bool isBuy, uint32_t qty, const TickRecord& tick) {
    Trade t{ nextOrderId_++, isBuy, tick.price, qty, tick.ts_ns };
    pos_->onFill(t);
    return t;
}

Trade ExecutionEngine::sendLimitOrder(bool isBuy, uint32_t qty, double limitPrice, const TickRecord& tick) {
    bool shouldFill =
        (isBuy  && tick.price <= limitPrice) ||
        (!isBuy && tick.price >= limitPrice);

    if (!shouldFill) {
        return Trade{ -1, isBuy, limitPrice, 0, tick.ts_ns };  // not filled
    }

    Trade t{ nextOrderId_++, isBuy, limitPrice, qty, tick.ts_ns };
    pos_->onFill(t);
    return t;
}
