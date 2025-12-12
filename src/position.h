#pragma once
#include <vector>
#include "trade.h"

class PositionManager {
public:
    PositionManager();

    void onFill(const Trade& t);

    int getPosition() const { return position_; }
    double getAvgPrice() const { return avgPrice_; }
    double getRealizedPnL() const { return realizedPnL_; }
    double calcUnrealizedPnL(double mark) const;

    const std::vector<Trade>& getTradeLog() const { return trades_; }

private:
    int position_;            // positive = long, negative = short
    double avgPrice_;
    double realizedPnL_;
    std::vector<Trade> trades_;
};
