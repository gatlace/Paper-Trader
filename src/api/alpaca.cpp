#include "api/alpaca.h"
#include "api/client.h"
#include "config.h"
#include "api/json.h"
#include <string>
#include <map>

const std::map<const char *, const char *> headers PROGMEM = {{"APCA-API-KEY-ID", ALPACA_API_KEY}, {"APCA-API-SECRET-KEY", ALPACA_API_SECRET}};

const char *base_url PROGMEM = "https://paper-api.alpaca.markets";

namespace Alpaca
{

    const char *rootCACertificate PROGMEM =
        "-----BEGIN CERTIFICATE-----\n"
        "MIIFYDCCBEigAwIBAgIQQAF3ITfU6UK47naqPGQKtzANBgkqhkiG9w0BAQsFADA/\n"
        "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n"
        "DkRTVCBSb290IENBIFgzMB4XDTIxMDEyMDE5MTQwM1oXDTI0MDkzMDE4MTQwM1ow\n"
        "TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n"
        "cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwggIiMA0GCSqGSIb3DQEB\n"
        "AQUAA4ICDwAwggIKAoICAQCt6CRz9BQ385ueK1coHIe+3LffOJCMbjzmV6B493XC\n"
        "ov71am72AE8o295ohmxEk7axY/0UEmu/H9LqMZshftEzPLpI9d1537O4/xLxIZpL\n"
        "wYqGcWlKZmZsj348cL+tKSIG8+TA5oCu4kuPt5l+lAOf00eXfJlII1PoOK5PCm+D\n"
        "LtFJV4yAdLbaL9A4jXsDcCEbdfIwPPqPrt3aY6vrFk/CjhFLfs8L6P+1dy70sntK\n"
        "4EwSJQxwjQMpoOFTJOwT2e4ZvxCzSow/iaNhUd6shweU9GNx7C7ib1uYgeGJXDR5\n"
        "bHbvO5BieebbpJovJsXQEOEO3tkQjhb7t/eo98flAgeYjzYIlefiN5YNNnWe+w5y\n"
        "sR2bvAP5SQXYgd0FtCrWQemsAXaVCg/Y39W9Eh81LygXbNKYwagJZHduRze6zqxZ\n"
        "Xmidf3LWicUGQSk+WT7dJvUkyRGnWqNMQB9GoZm1pzpRboY7nn1ypxIFeFntPlF4\n"
        "FQsDj43QLwWyPntKHEtzBRL8xurgUBN8Q5N0s8p0544fAQjQMNRbcTa0B7rBMDBc\n"
        "SLeCO5imfWCKoqMpgsy6vYMEG6KDA0Gh1gXxG8K28Kh8hjtGqEgqiNx2mna/H2ql\n"
        "PRmP6zjzZN7IKw0KKP/32+IVQtQi0Cdd4Xn+GOdwiK1O5tmLOsbdJ1Fu/7xk9TND\n"
        "TwIDAQABo4IBRjCCAUIwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAQYw\n"
        "SwYIKwYBBQUHAQEEPzA9MDsGCCsGAQUFBzAChi9odHRwOi8vYXBwcy5pZGVudHJ1\n"
        "c3QuY29tL3Jvb3RzL2RzdHJvb3RjYXgzLnA3YzAfBgNVHSMEGDAWgBTEp7Gkeyxx\n"
        "+tvhS5B1/8QVYIWJEDBUBgNVHSAETTBLMAgGBmeBDAECATA/BgsrBgEEAYLfEwEB\n"
        "ATAwMC4GCCsGAQUFBwIBFiJodHRwOi8vY3BzLnJvb3QteDEubGV0c2VuY3J5cHQu\n"
        "b3JnMDwGA1UdHwQ1MDMwMaAvoC2GK2h0dHA6Ly9jcmwuaWRlbnRydXN0LmNvbS9E\n"
        "U1RST09UQ0FYM0NSTC5jcmwwHQYDVR0OBBYEFHm0WeZ7tuXkAXOACIjIGlj26Ztu\n"
        "MA0GCSqGSIb3DQEBCwUAA4IBAQAKcwBslm7/DlLQrt2M51oGrS+o44+/yQoDFVDC\n"
        "5WxCu2+b9LRPwkSICHXM6webFGJueN7sJ7o5XPWioW5WlHAQU7G75K/QosMrAdSW\n"
        "9MUgNTP52GE24HGNtLi1qoJFlcDyqSMo59ahy2cI2qBDLKobkx/J3vWraV0T9VuG\n"
        "WCLKTVXkcGdtwlfFRjlBz4pYg1htmf5X6DYO8A4jqv2Il9DjXA6USbW1FzXSLr9O\n"
        "he8Y4IWS6wY7bCkjCWDcRQJMEhg76fsO3txE+FiYruq9RUWhiF1myv4Q6W+CyBFC\n"
        "Dfvp7OOGAN6dEOM4+qR9sdjoSYKEBpsr6GtPAQw4dy753ec5\n"
        "-----END CERTIFICATE-----\n"
        "";

    DynamicJsonDocument get(const char *extension)
    {
        String url{base_url};
        url += extension;

        std::map<const char *, const char *> headers;
        headers["APCA-API-KEY-ID"] = ALPACA_API_KEY;
        headers["APCA-API-SECRET-KEY"] = ALPACA_API_SECRET;

        return Client_::get(url.c_str(), rootCACertificate, headers);
    }

    int post(const char *extension, const char *body)
    {
        String url{base_url};
        url += extension;

        std::map<const char *, const char *> headers;
        headers["APCA-API-KEY-ID"] = ALPACA_API_KEY;
        headers["APCA-API-SECRET-KEY"] = ALPACA_API_SECRET;
        headers["Content-Type"] = "application/json";

        return Client_::post(url.c_str(), rootCACertificate, headers, body);
    }

    int delete_(const char *extension)
    {
        String url{base_url};
        url += extension;

        return Client_::delete_(url.c_str(), rootCACertificate, headers);
    }

    DynamicJsonDocument account_info()
    {
        return get("/v2/account");
    }

    DynamicJsonDocument get_orders()
    {
        return get("/v2/orders");
    }

    int order_market(const char *symbol, float notional, const char *side)
    {
        StaticJsonDocument<200> doc;
        doc[F("symbol")] = symbol;
        doc[F("notional")] = String(notional, 2);
        doc[F("side")] = side;
        doc[F("type")] = F("market");
        doc[F("time_in_force")] = F("day");

        char body[200];
        serializeJson(doc, body);

        return post("/v2/orders", body);
    }

    int order_limit(const char *symbol, int qty, float limit_price, const char *side)
    {
        StaticJsonDocument<200> doc;
        doc[F("symbol")] = symbol;
        doc[F("qty")] = qty;
        doc[F("side")] = side;
        doc[F("type")] = "limit";
        doc[F("limit_price")] = limit_price;

        char body[200];
        serializeJson(doc, body);

        return post("/v2/orders", body);
    }

    int cancel_order(const char *id)
    {
        String extension{"/v2/orders/" + String(id)};
        return delete_(extension.c_str());
    }

    int cancel_orders()
    {
        return delete_("/v2/orders");
    }

    float buying_power()
    {
        DynamicJsonDocument doc = account_info();
        return doc[F("buying_power")];
    }

    DynamicJsonDocument get_positions()
    {
        return get("/v2/positions");
    }

    int close_position(const char *symbol)
    {
        String extension{"/v2/positions/" + String(symbol)};
        return delete_(extension.c_str());
    }

    int close_all_positions()
    {
        return delete_("/v2/positions");
    }

    bool has_position_in(const char *symbol)
    {
        DynamicJsonDocument doc{get_positions()};

        JsonArray positions{doc.as<JsonArray>()};

        for (JsonObject position : positions)
        {
            if (position[F("symbol")] == symbol)
            {
                return true;
            }
        }

        return false;
    }

    bool has_order_for(const char *symbol)
    {
        DynamicJsonDocument doc{get_orders()};

        JsonArray orders{doc.as<JsonArray>()};

        for (JsonObject order : orders)
        {
            if (order[F("symbol")] == symbol)
            {
                return true;
            }
        }

        return false;
    }

    int cancel_orders_for(const char *symbol)

    {
        DynamicJsonDocument doc{get_orders()};

        JsonArray orders{doc.as<JsonArray>()};

        for (JsonObject order : orders)
        {
            if (order[F("symbol")] == symbol)
            {
                cancel_order(order[F("id")]);
            }
        }

        return 0;
    }
}
