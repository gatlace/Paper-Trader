#pragma once
#include <ArduinoJson.h>
#include <vector>
namespace AlphaVantage
{

    struct TimeSeries
    {
        String symbol;
        float open;
        float high;
        float low;
        float close;
        float volume;
    };

    DynamicJsonDocument quote(const char *symbol);
    DynamicJsonDocument sma(const char *symbol, const char *interval, const char *time_period, const char *series_type);
    DynamicJsonDocument market_open();
    std::vector<TimeSeries> hourly(const char *symbol);
    std::vector<TimeSeries> daily(const char *symbol);
}