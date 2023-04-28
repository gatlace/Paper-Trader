#include "models/rsi.h"
#include "models/macd.h"
#include "api/alpaca.h"

namespace Trade
{
    void swing_trade_leveraged(const char *symbol, const char *up_stock, const char *down_stock, float percentage)
    {
        Logic::Trend rsi_trend{RSI::trend(symbol)};
        Logic::Trend macd_trend{MACD::trend(symbol)};

        Logic::Trend final_trend{Logic::combine_trends(std::vector<Logic::Trend>{rsi_trend, macd_trend})};

        Logic::Decision final_decision;

        switch (final_trend)
        {
        case Logic::Trend::UP:
            final_decision = Logic::Decision::BUY;
            break;
        case Logic::Trend::DOWN:
            final_decision = Logic::Decision::SELL;
            break;
        case Logic::Trend::FLAT:
            final_decision = Logic::Decision::HOLD;
            break;
        }

        switch (final_decision)
        {
        case Logic::Decision::BUY:
            Serial.println(F("Final decision: BUY"));
            if (Alpaca::has_position_in(down_stock) || Alpaca::has_order_for(down_stock))
            {
                Serial.println(F("Selling short position..."));
                Alpaca::close_position(down_stock);
                Alpaca::cancel_orders_for(down_stock);
            }
            else
            {
                Serial.println(F("No short position to close!"));
            }

            if (!Alpaca::has_position_in(up_stock) && !Alpaca::has_order_for(up_stock))
            {
                Serial.println(F("Buying long position..."));
                float buying_power{Alpaca::buying_power()};
                float buying_amount{buying_power * percentage};
                Alpaca::order_market(up_stock, buying_amount, "buy");
                Serial.println(F("Long position bought!"));
            }
            else
            {
                Serial.println(F("Already have a long position!"));
            }
            break;
        case Logic::Decision::SELL:
            Serial.println(F("Final decision: SELL"));
            if (Alpaca::has_position_in(up_stock) || Alpaca::has_order_for(up_stock))
            {
                Serial.println(F("Closing long position..."));
                Alpaca::close_position(up_stock);
            }
            else
            {
                Serial.println(F("No long position to close!"));
            }

            if (!Alpaca::has_position_in(down_stock) && !Alpaca::has_order_for(down_stock))
            {
                Serial.println(F("Opening short position..."));
                float buying_power{Alpaca::buying_power()};
                float buying_amount{buying_power * (percentage / 100)};
                Alpaca::order_market(down_stock, buying_amount, "sell");
                Serial.println(F("Short position opened!"));
            }
            else
            {
                Serial.println(F("Already have a short position!"));
            }
            break;
        case Logic::Decision::HOLD:
            Serial.println(F("Final decision: HOLD"));
            if (Alpaca::has_position_in(up_stock) || Alpaca::has_order_for(up_stock))
            {
                Serial.println(F("Closing long position..."));
                Alpaca::close_position(up_stock);
                Alpaca::cancel_orders_for(up_stock);
            }
            else
            {
                Serial.println(F("No long position to close!"));
            }

            if (Alpaca::has_position_in(down_stock) || Alpaca::has_order_for(down_stock))
            {
                Serial.println(F("Closing short position..."));
                Alpaca::close_position(down_stock);
                Alpaca::cancel_orders_for(down_stock);
            }
            else
            {
                Serial.println(F("No short position to close!"));
            }

            break;
        default:
            break;
        }
        Serial.println("======================================");
    }
}