#include <Arduino.h>
#include <ArduinoJson.h>
#include "models/logic.h"
#include "models/rsi.h"
#include "models/ta.h"
#include "models/trade.h"
#include "api/client.h"
#include "SimplePgSQL.h"

int lastRequest = 0;
void setup()
{
  Serial.begin(115200);
  Client_::init();
  TA::init();
}

void loop()
{
  if (millis() - lastRequest > 60000)
  {
    lastRequest = millis();
    Trade::swing_trade_leveraged("QQQ", "TQQQ", "SQQQ", 0.5);
  }
}