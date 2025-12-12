#include "loader.h"
#include "engine.h"
#include "strategy.h"
#include <iostream>

struct SimpleStrategy : IStrategy {

    void onTick(const TickRecord& t, BacktestEngine* engine) override {
        auto exec = engine->getExec();
        auto pos  = engine->getPos();

        // BUY if price < 100.7
        if (t.price < 100.7) {
            auto fill = exec->sendMarketOrder(true, 1, t);
            if (fill.qty > 0)
                std::cout << "BUY @ " << fill.price << "\n";
        }

        // SELL if price > 100.8
        if (t.price > 100.8) {
            auto fill = exec->sendMarketOrder(false, 1, t);
            if (fill.qty > 0)
                std::cout << "SELL @ " << fill.price << "\n";
        }

        double unreal = pos->calcUnrealizedPnL(t.price);
        std::cout << "Pos=" << pos->getPosition()
                  << " Avg=" << pos->getAvgPrice()
                  << " RealPNL=" << pos->getRealizedPnL()
                  << " UnRealPNL=" << unreal
                  << "\n";
    }
};

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "usage: ./backtest data/ticks.csv\n";
        return 1;
    }

    auto data = loadCsv(argv[1]);

    SimpleStrategy strat;
    BacktestEngine engine(&strat);

    engine.setData(&data);

    std::cout << "Running backtest ASAP...\n";
    engine.runAsFastAsPossible();

    return 0;
}
