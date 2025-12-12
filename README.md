# High-Performance Trading Simulator with PnL Engine (C++)

A fast and modular **tick-level trading simulator** built in **C++17**.  
Designed for *quantitative trading*, *HFT research*, and *strategy prototyping*.

This engine supports:

- Ultra-fast tick replay  
- Market & limit order execution  
- Position management  
- Realized & unrealized PnL  
- Average price computation  
- Trade logging  
- Pluggable strategies  

---

## Features

### Tick-Level Replay Engine
- Processes real or synthetic tick data  
- Nanosecond timestamp support  
- Ultra-fast replay or speed-controlled simulation

### Execution Engine
- Market orders  
- Limit orders (simple fill logic)  
- Trade fill simulation  
- Order lifecycle handling

### PnL Engine
- Position tracking  
- Average price calculation  
- Realized PnL  
- Unrealized PnL (mark-to-market)  
- Trade logs

### Modular Strategy Interface
Define strategies like:

```cpp
exec->sendMarketOrder(true, 1, tick);   // Buy
exec->sendMarketOrder(false, 1, tick);  // Sell
