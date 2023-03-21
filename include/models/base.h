#pragma once
#include "api.h"
#include <vector>
#include "models/logic.h"

namespace Base
{

    float typical_price(float high, float low, float close);
    std::vector<float> typical_prices(std::vector<AlphaVantage::TimeSeries> ts);
    float slope_from_prices(std::vector<float> &prices, int period);
    Logic::Decision decision_with_position(Logic::Decision decision, Logic::Position position);
}