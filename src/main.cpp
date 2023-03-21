#include <Arduino.h>
#include <ArduinoJson.h>
#include "models/logic.h"
#include "models/rsi.h"
#include "models/ta.h"
#include "api.h"
#include "models/trade.h"
void setup()
{
  Serial.begin(115200);
  Client_::init();
  TA::init();
}

void loop()
{
  Trade::swing_trade_leveraged("QQQ", "TQQQ", "SQQQ", 0.5);
  delay(60000);
}