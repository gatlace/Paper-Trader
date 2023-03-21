#include "models/base.h"
#include "models/logic.h"

namespace Base
{
    float typical_price(float high, float low, float close)
    {
        return (high + low + close) / 3;
    }

    std::vector<float> typical_prices(std::vector<AlphaVantage::TimeSeries> ts)
    {
        std::vector<float> prices;
        for (int i = 0; i < ts.size(); i++)
        {
            prices.push_back(typical_price(ts[i].high, ts[i].low, ts[i].close));
        }
        return prices;
    }

    float slope_from_prices(std::vector<float> &prices, int period)
    {
        float slope = 0;
        for (int i = 0; i < period; i++)
        {
            slope += prices[prices.size() - 1 - i] - prices[prices.size() - 2 - i];
        }
        return slope / period;
    }

    Logic::Decision decision_with_position(Logic::Decision decision, Logic::Position position)
    {
        if (position == Logic::Position::LONG)
        {
            if (decision == Logic::Decision::BUY)
            {
                return Logic::Decision::HOLD;
            }
            else if (decision == Logic::Decision::SELL)
            {
                return Logic::Decision::SELL;
            }
            else
            {
                return Logic::Decision::HOLD;
            }
        }
        else if (position == Logic::Position::SHORT)
        {
            if (decision == Logic::Decision::BUY)
            {
                return Logic::Decision::BUY;
            }
            else if (decision == Logic::Decision::SELL)
            {
                return Logic::Decision::HOLD;
            }
            else
            {
                return Logic::Decision::HOLD;
            }
        }
        else
        {
            return decision;
        }
    }
}
