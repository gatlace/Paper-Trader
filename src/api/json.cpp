#include <ArduinoJson.h>
namespace JSON
{
    DynamicJsonDocument parse(const char *json, int size)
    {
        DynamicJsonDocument doc(size);
        deserializeJson(doc, json);
        return doc;
    }
    String stringify(DynamicJsonDocument doc)
    {
        String output;
        serializeJson(doc, output);
        return output;
    }
}