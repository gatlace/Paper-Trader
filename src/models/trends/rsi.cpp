#include "models/logic.h"
#include "models/base.h"
#include "models/ta.h"
#include "api.h"
#include "models/rsi.h"

#define RSI_FLAT_BUFFER 0.25
#define RSI_PERIOD 14
#define RSI_SLOPE_PERIOD 7
#define RSI_OVERSOLD 30
#define RSI_OVERBOUGHT 70

namespace RSI
{

    Logic::Trend hourly_rsi_look(const char *symbol)
    {
        std::vector<AlphaVantage::TimeSeries> ts = AlphaVantage::hourly(symbol);

        std::vector<float> prices{Base::typical_prices(ts)};

        std::vector<float> RSI;
        TA::RSI(prices, RSI_PERIOD, RSI);

        std::vector<float> RSI_EMA;
        TA::EMA(RSI, RSI_PERIOD, RSI_EMA);

        float rsi_slope{Base::slope_from_prices(RSI, RSI_SLOPE_PERIOD)};
        float rsi_ema_slope{Base::slope_from_prices(RSI_EMA, RSI_SLOPE_PERIOD)};

        float current_rsi{RSI[RSI.size() - 1]};
        float current_rsi_ema{RSI_EMA[RSI_EMA.size() - 1]};

        bool rsi_overbought{current_rsi >= RSI_OVERBOUGHT};
        bool rsi_oversold{current_rsi < RSI_OVERSOLD};

        bool rsi_ema_overbought{current_rsi_ema >= RSI_OVERBOUGHT};
        bool rsi_ema_oversold{current_rsi_ema < RSI_OVERSOLD};

        if (rsi_overbought && rsi_ema_overbought)
        {
            return Logic::Trend::DOWN;
        }
        else if (rsi_oversold && rsi_ema_oversold)
        {
            return Logic::Trend::UP;
        }
        else if (current_rsi > current_rsi_ema)
        {
            if (rsi_slope > rsi_ema_slope + RSI_FLAT_BUFFER)
            {
                return Logic::Trend::UP;
            }
            else if (rsi_slope < rsi_ema_slope - RSI_FLAT_BUFFER)
            {
                return Logic::Trend::FLAT;
            }
            else
            {
                return Logic::Trend::UP;
            }
        }
        else if (current_rsi < current_rsi_ema)
        {
            if (rsi_slope > rsi_ema_slope + RSI_FLAT_BUFFER)
            {
                return Logic::Trend::FLAT;
            }
            else if (rsi_slope < rsi_ema_slope - RSI_FLAT_BUFFER)
            {
                return Logic::Trend::DOWN;
            }
            else
            {
                return Logic::Trend::DOWN;
            }
        }
        else if (current_rsi == current_rsi_ema)
        {
            if (rsi_slope > rsi_ema_slope + RSI_FLAT_BUFFER)
            {
                return Logic::Trend::UP;
            }
            else if (rsi_slope < rsi_ema_slope - RSI_FLAT_BUFFER)
            {
                return Logic::Trend::DOWN;
            }
            else
            {
                return Logic::Trend::FLAT;
            }
        }
    }

    Logic::Trend daily_rsi_look(const char *symbol)
    {
        std::vector<AlphaVantage::TimeSeries> ts = AlphaVantage::daily(symbol);

        std::vector<float> prices{Base::typical_prices(ts)};

        std::vector<float> RSI;
        TA::RSI(prices, RSI_PERIOD, RSI);

        std::vector<float> RSI_EMA;
        TA::EMA(RSI, RSI_PERIOD, RSI_EMA);

        float rsi_slope{Base::slope_from_prices(RSI, RSI_SLOPE_PERIOD)};
        float rsi_ema_slope{Base::slope_from_prices(RSI_EMA, RSI_SLOPE_PERIOD)};

        float current_rsi{RSI[RSI.size() - 1]};
        float current_rsi_ema{RSI_EMA[RSI_EMA.size() - 1]};

        bool rsi_overbought{current_rsi >= RSI_OVERBOUGHT};
        bool rsi_oversold{current_rsi <= RSI_OVERSOLD};

        bool rsi_ema_overbought{current_rsi_ema > RSI_OVERBOUGHT};
        bool rsi_ema_oversold{current_rsi_ema < RSI_OVERSOLD};

        if (rsi_overbought && rsi_ema_overbought)
        {
            return Logic::Trend::DOWN;
        }
        else if (rsi_oversold && rsi_ema_oversold)
        {
            return Logic::Trend::UP;
        }
        else if (current_rsi > current_rsi_ema)
        {
            if (rsi_slope > rsi_ema_slope + RSI_FLAT_BUFFER)
            {
                return Logic::Trend::UP;
            }
            else if (rsi_slope < rsi_ema_slope - RSI_FLAT_BUFFER)
            {
                return Logic::Trend::FLAT;
            }
            else
            {
                return Logic::Trend::UP;
            }
        }
        else if (current_rsi < current_rsi_ema)
        {
            if (rsi_slope > rsi_ema_slope + RSI_FLAT_BUFFER)
            {
                return Logic::Trend::FLAT;
            }
            else if (rsi_slope < rsi_ema_slope - RSI_FLAT_BUFFER)
            {
                return Logic::Trend::DOWN;
            }
            else
            {
                return Logic::Trend::DOWN;
            }
        }
        else if (current_rsi == current_rsi_ema)
        {
            if (rsi_slope > rsi_ema_slope + RSI_FLAT_BUFFER)
            {
                return Logic::Trend::UP;
            }
            else if (rsi_slope < rsi_ema_slope - RSI_FLAT_BUFFER)
            {
                return Logic::Trend::DOWN;
            }
            else
            {
                return Logic::Trend::FLAT;
            }
        }
    }

    Logic::Trend trend(const char *symbol)
    {
        Logic::Trend hourly{hourly_rsi_look(symbol)};
        Logic::Trend daily{daily_rsi_look(symbol)};

        return Logic::combine_trends(std::vector<Logic::Trend>{hourly, daily});
    }
}