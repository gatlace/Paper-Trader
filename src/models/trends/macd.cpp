#include "models/logic.h"
#include "models/base.h"
#include "models/ta.h"
#include "api.h"

#define MACD_FLAT_BUFFER 0.2
#define MACD_FAST_PERIOD 12
#define MACD_FAST_SLOPE_PERIOD 6
#define MACD_SLOW_PERIOD 26
#define MACD_SLOW_SLOPE_PERIOD 13
#define MACD_SIGNAL_PERIOD 9
#define MACD_SIGNAL_SLOPE_PERIOD 4
#define MACD_OVERBOUGHT 2

namespace MACD
{
    Logic::Trend hourly_macd_look(const char *symbol)
    {
        std::vector<AlphaVantage::TimeSeries> ts = AlphaVantage::hourly(symbol);
        std::vector<float> prices{Base::typical_prices(ts)};

        std::vector<float> MACD;
        std::vector<float> MACD_SIGNAL;
        std::vector<float> MACD_HISTOGRAM;

        TA::MACD(prices, MACD_FAST_PERIOD, MACD_SLOW_PERIOD, MACD_SIGNAL_PERIOD, MACD, MACD_SIGNAL, MACD_HISTOGRAM);
        float macd_slope{Base::slope_from_prices(MACD, MACD_FAST_SLOPE_PERIOD)};
        float macd_signal_slope{Base::slope_from_prices(MACD_SIGNAL, MACD_FAST_SLOPE_PERIOD)};
        float macd_histogram_slope{Base::slope_from_prices(MACD_HISTOGRAM, MACD_FAST_SLOPE_PERIOD)};

        float current_macd{MACD[MACD.size() - 1]};
        float current_macd_signal{MACD_SIGNAL[MACD_SIGNAL.size() - 1]};
        float current_macd_histogram{MACD_HISTOGRAM[MACD_HISTOGRAM.size() - 1]};
        Serial.println("Hourly MACD:");
        Serial.print("MACD: ");
        Serial.println(current_macd);
        Serial.print("MACD Signal: ");
        Serial.println(current_macd_signal);
        Serial.print("MACD Histogram: ");
        Serial.println(current_macd_histogram);
        Serial.print("MACD Slope: ");
        Serial.println(macd_slope);
        Serial.print("MACD Signal Slope: ");
        Serial.println(macd_signal_slope);
        Serial.print("MACD Histogram Slope: ");
        Serial.println(macd_histogram_slope);
        if (macd_histogram_slope > MACD_FLAT_BUFFER)
        {
            if (current_macd >= MACD_OVERBOUGHT)
            {
                return Logic::Trend::FLAT;
            }
            else
            {
                return Logic::Trend::UP;
            }
        }
        else if (macd_histogram_slope < -MACD_FLAT_BUFFER)
        {
            if (current_macd <= -MACD_OVERBOUGHT)
            {
                return Logic::Trend::FLAT;
            }
            else
            {
                return Logic::Trend::DOWN;
            }
        }
        else
        {
            if (current_macd > current_macd_signal)
            {
                return Logic::Trend::UP;
            }
            else if (current_macd < current_macd_signal)
            {
                return Logic::Trend::DOWN;
            }
            else
            {
                return Logic::Trend::FLAT;
            }
        }
    }

    Logic::Trend daily_macd_look(const char *symbol)
    {
        std::vector<AlphaVantage::TimeSeries> ts = AlphaVantage::daily(symbol);
        std::vector<float> prices{Base::typical_prices(ts)};

        std::vector<float> MACD;
        std::vector<float> MACD_SIGNAL;
        std::vector<float> MACD_HISTOGRAM;

        TA::MACD(prices, MACD_FAST_PERIOD, MACD_SLOW_PERIOD, MACD_SIGNAL_PERIOD, MACD, MACD_SIGNAL, MACD_HISTOGRAM);
        float macd_slope{Base::slope_from_prices(MACD, 12)};
        float macd_signal_slope{Base::slope_from_prices(MACD_SIGNAL, 12)};
        float macd_histogram_slope{Base::slope_from_prices(MACD_HISTOGRAM, 12)};

        float current_macd{MACD[MACD.size() - 1]};
        float current_macd_signal{MACD_SIGNAL[MACD_SIGNAL.size() - 1]};
        float current_macd_histogram{MACD_HISTOGRAM[MACD_HISTOGRAM.size() - 1]};

        Serial.println("Daily MACD:");
        Serial.print("MACD: ");
        Serial.println(current_macd);
        Serial.print("MACD Signal: ");
        Serial.println(current_macd_signal);
        Serial.print("MACD Histogram: ");
        Serial.println(current_macd_histogram);
        Serial.print("MACD Slope: ");
        Serial.println(macd_slope);
        Serial.print("MACD Signal Slope: ");
        Serial.println(macd_signal_slope);
        Serial.print("MACD Histogram Slope: ");
        Serial.println(macd_histogram_slope);

        if (macd_histogram_slope > MACD_FLAT_BUFFER)
        {
            if (current_macd >= MACD_OVERBOUGHT)
            {
                return Logic::Trend::FLAT;
            }
            else
            {
                return Logic::Trend::UP;
            }
        }
        else if (macd_histogram_slope < -MACD_FLAT_BUFFER)
        {
            if (current_macd <= -MACD_OVERBOUGHT)
            {
                return Logic::Trend::FLAT;
            }
            else
            {
                return Logic::Trend::DOWN;
            }
        }
        else
        {
            if (current_macd > current_macd_signal)
            {
                return Logic::Trend::UP;
            }
            else if (current_macd < current_macd_signal)
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
        Logic::Trend hourly_trend{hourly_macd_look(symbol)};
        Logic::Trend daily_trend{daily_macd_look(symbol)};

        return Logic::combine_trends(std::vector<Logic::Trend>{hourly_trend, daily_trend});
    }

}