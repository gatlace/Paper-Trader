#pragma once
#include "models/logic.h"

namespace MACD
{
    Logic::Trend hourly_macd_look(const char *symbol);
    Logic::Trend daily_macd_look(const char *symbol);
    Logic::Trend trend(const char *symbol);
}