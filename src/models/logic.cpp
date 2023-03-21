#include "models/logic.h"
#include "models/ta.h"
#include "models/base.h"
#include <vector>

namespace Logic
{
    Trend combine_trends(std::vector<Trend> trends)
    {
        int trend_sum{0};
        for (Trend trend : trends)
        {
            trend_sum += static_cast<int>(trend);
        }

        if (trend_sum > 0)
        {
            return Trend::UP;
        }
        else if (trend_sum < 0)
        {
            return Trend::DOWN;
        }
        else
        {
            return Trend::FLAT;
        }
    }
}