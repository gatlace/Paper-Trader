#pragma once
#include <map>
#include <Arduino.h>
#include <vector>

namespace Logic
{
    enum class Trend
    {
        UP = 1,
        DOWN = -1,
        FLAT = 0
    };

    enum class Position
    {
        LONG,
        SHORT,
        OUT,
    };

    enum class Decision
    {
        BUY,
        SELL,
        HOLD
    };

    const std::map<Trend, String> trend_to_string{
        {Trend::UP, "UP"},
        {Trend::DOWN, "DOWN"},
        {Trend::FLAT, "FLAT"},
    };

    const std::map<Position, String> position_to_string{
        {Position::LONG, "LONG"},
        {Position::SHORT, "SHORT"},
        {Position::OUT, "OUT"},
    };

    const std::map<Decision, String> decision_to_string{
        {Decision::BUY, "BUY"},
        {Decision::SELL, "SELL"},
        {Decision::HOLD, "HOLD"},
    };

    Trend combine_trends(std::vector<Trend> trends);
}