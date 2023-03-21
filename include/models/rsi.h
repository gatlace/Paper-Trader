#pragma once
#include "logic.h"

namespace RSI
{
    Logic::Trend hourly_rsi_look(const char *symbol);
    Logic::Trend daily_rsi_look(const char *symbol);
    Logic::Trend trend(const char *symbol);
}