#pragma once
#include <ArduinoJson.h>
#include <map>
#include "WiFiClientSecure.h"

namespace Client_
{
    void init();
    DynamicJsonDocument get(const char *url, const char *ca_cert, std::map<const char *, const char *> headers);
    int post(const char *url, const char *ca_cert, std::map<const char *, const char *> headers, const char *body);
    int delete_(const char *url, const char *ca_cert, std::map<const char *, const char *> headers);
    extern WiFiClient client;
}