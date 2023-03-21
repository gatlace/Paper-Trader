#pragma once
#include <ArduinoJson.h>
namespace JSON
{
    DynamicJsonDocument parse(const char *json, int size);
    String stringify(DynamicJsonDocument doc);
}