#include "position.h"
#include <cmath>
#include <algorithm>
#include <iostream>

PositionManager::PositionManager()
    : position_(0), avgPrice_(0.0), realizedPnL_(0.0) {}

void PositionManager::onFill(const Trade& t) {
    trades_.push_back(t);

    int qty = t.isBuy ? (int)t.qty : -(int)t.qty;

    // Same-direction trade (increasing position)
    if ((position_ >= 0 && qty > 0) || (position_ <= 0 && qty < 0)) {
        int newPos = position_ + qty;
        if (newPos != 0) {
             avgPrice_ = (avgPrice_ * std::abs(position_) + t.price * std::abs(qty)) / std::abs(newPos);
        } else {
             avgPrice_ = 0;
        }
        position_ = newPos;
        return;
    }

    // Opposite-direction trade (reducing or flipping)
    int closingQty = std::min(std::abs(position_), std::abs(qty));
    
    realizedPnL_ += closingQty * (t.price - avgPrice_) * (position_ > 0 ? 1 : -1);

    position_ += qty;

    if (position_ == 0) {
        avgPrice_ = 0;
    }
}

double PositionManager::calcUnrealizedPnL(double mark) const {
    if (position_ == 0) return 0.0;
    return (mark - avgPrice_) * position_;
}
