#pragma once
#include "loader.h"
#include <vector>

class BacktestEngine; 

struct IStrategy {
    virtual ~IStrategy() = default;
    virtual void onStart() {}
    virtual void onTick(const TickRecord& t, BacktestEngine* engine) = 0;
    virtual void onEnd() {}
};
