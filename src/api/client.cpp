#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "api/json.h"
#include <map>
#include "api/client.h"

void connect_to_server(HTTPClient &https, WiFiClientSecure &client, const char *url)
{
    Serial.println(F("Connecting to server..."));
    if (!https.begin(client, url))
    {
        Serial.println(F("Connection failed!"));
        return;
    }
    Serial.println(F("Connected to server"));
}

void add_headers(HTTPClient &https, std::map<const char *, const char *> headers)
{
    for (auto const &header : headers)
    {
        https.addHeader(header.first, header.second);
    }
}

namespace Client_
{
    WiFiClient client;
    WiFiClientSecure client_secure;
    void init()
    {
        Serial.println(F("Connecting to WiFi"));
        WiFi.begin("._.", "Maximus3000");
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(F("."));
        }
        Serial.println(F("WiFi connected, IP address: "));
        Serial.println(WiFi.localIP());
    }

    DynamicJsonDocument get(const char *url, const char *ca_cert, std::map<const char *, const char *> headers)
    {
        client_secure.setCACert(ca_cert);
        HTTPClient https;

        connect_to_server(https, client_secure, url);
        if (headers.size() > 0)
        {
            add_headers(https, headers);
        }

        Serial.println(F("Sending GET request..."));
        int httpCode = https.GET();

        if (httpCode <= 0)
        {
            Serial.print(F("GET request failed, error: "));
            Serial.println(https.errorToString(httpCode));

            https.end();

            return DynamicJsonDocument(0);
        }

        Serial.println(F("GET request successful\n"));

        String payload = https.getString();
        https.end();

        DynamicJsonDocument doc = JSON::parse(payload.c_str(), payload.length());

        return doc;
    }

    int post(const char *url, const char *ca_cert, std::map<const char *, const char *> headers, const char *body)
    {
        client_secure.setCACert(ca_cert);
        HTTPClient https;

        connect_to_server(https, client_secure, url);
        add_headers(https, headers);
        https.addHeader(F("Content-Type"), F("application/json"));

        Serial.println(F("Sending POST request..."));
        // get the response payload
        int httpCode = https.POST(body);

        String payload = https.getString();
        DynamicJsonDocument doc = JSON::parse(payload.c_str(), payload.length());

        if (httpCode <= 0)
        {
            Serial.print(F("POST request failed, error: "));
            Serial.println(https.errorToString(httpCode));

            https.end();

            return 0;
        }

        Serial.println(F("POST request successful\n"));

        https.end();

        return httpCode;
    }

    int delete_(const char *url, const char *ca_cert, std::map<const char *, const char *> headers)
    {
        client_secure.setCACert(ca_cert);
        HTTPClient https;

        connect_to_server(https, client_secure, url);
        add_headers(https, headers);

        Serial.println(F("Sending DELETE request..."));
        int httpCode = https.sendRequest("DELETE");

        if (httpCode <= 0)
        {
            Serial.print(F("DELETE request failed, error: "));
            Serial.println(https.errorToString(httpCode));

            https.end();

            return 0;
        }

        Serial.println(F("DELETE request successful"));

        https.end();

        return httpCode;
    }

}