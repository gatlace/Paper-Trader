#pragma once
#include <ta_func.h>
#include <vector>

namespace TA
{
    void init();
    TA_RetCode EMA(std::vector<float> &prices, int period, std::vector<float> &outReal);
    TA_RetCode RSI(std::vector<float> &prices, int period, std::vector<float> &outReal);
    TA_RetCode MACD(std::vector<float> &prices, int fastPeriod, int slowPeriod, int signalPeriod, std::vector<float> &outMACD, std::vector<float> &outMACDSignal, std::vector<float> &outMACDHist);
}