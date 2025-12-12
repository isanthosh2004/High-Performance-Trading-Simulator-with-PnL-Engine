#include "engine.h"
#include <chrono>
#include <thread>

BacktestEngine::BacktestEngine(IStrategy* strat)
    : strat_(strat), data_(nullptr), exec_(&pos_) {}

void BacktestEngine::setData(const std::vector<TickRecord>* d) {
    data_ = d;
}

void BacktestEngine::runAsFastAsPossible() {
    if (!data_) return;

    strat_->onStart();
    for (const auto& t : *data_) {
        strat_->onTick(t, this);
    }
    strat_->onEnd();
}

void BacktestEngine::runReplay(double speedFactor) {
    if (!data_ || data_->empty()) return;

    strat_->onStart();

    uint64_t base_ts = (*data_)[0].ts_ns;
    auto wall_start = std::chrono::steady_clock::now();

    for (const auto& t : *data_) {
        uint64_t rel_ns = t.ts_ns - base_ts;
        double target_ms = rel_ns / 1e6 / speedFactor;

        auto target = wall_start + std::chrono::milliseconds((long long)target_ms);
        std::this_thread::sleep_until(target);

        strat_->onTick(t, this);
    }

    strat_->onEnd();
}
