#pragma once
#include <ArduinoJson.h>

namespace Alpaca
{
    DynamicJsonDocument get_orders();
    int cancel_orders();
    int cancel_order(const char *id);
    float buying_power();
    DynamicJsonDocument get_positions();
    int close_position(const char *symbol);
    int close_all_positions();
    int order_market(const char *symbol, float notional, const char *side);
    int order_limit(const char *symbol, int qty, float limit_price, const char *side);
    bool has_position_in(const char *symbol);
    bool has_order_for(const char *symbol);
    int cancel_orders_for(const char *symbol);
}