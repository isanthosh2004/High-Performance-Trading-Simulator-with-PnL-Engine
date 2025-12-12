#pragma once
#include <vector>
#include "loader.h"
#include "strategy.h"
#include "execution.h"
#include "position.h"

class BacktestEngine {
public:
    BacktestEngine(IStrategy* strat);

    void setData(const std::vector<TickRecord>* d);
    void runAsFastAsPossible();
    void runReplay(double speedFactor);

    ExecutionEngine* getExec() { return &exec_; }
    PositionManager* getPos() { return &pos_; }

private:
    IStrategy* strat_;
    const std::vector<TickRecord>* data_;

    PositionManager pos_;
    ExecutionEngine exec_;
};
