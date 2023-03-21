#include "api/client.h"
#include "api/keys.h"
#include "api/json.h"
#include <string>
#include <map>
#include <vector>

const char *alphavantage_base_url PROGMEM = "https://www.alphavantage.co/query?";

String build_url(const char *extension)
{
    String url = String(alphavantage_base_url) + String(extension);
    url += String("&apikey=") + String(ALPHAVANTAGE_API_KEY);

    return url;
}

String build_query(const std::map<const char *, const char *> &args)
{
    String url = "";
    for (auto const &x : args)
    {
        url += String("&") + x.first + String("=") + x.second;
    }
    return url;
}

namespace AlphaVantage
{

    const char *rootCACertificate PROGMEM =
        "-----BEGIN CERTIFICATE-----\n"
        "MIIDzTCCArWgAwIBAgIQCjeHZF5ftIwiTv0b7RQMPDANBgkqhkiG9w0BAQsFADBa\n"
        "MQswCQYDVQQGEwJJRTESMBAGA1UEChMJQmFsdGltb3JlMRMwEQYDVQQLEwpDeWJl\n"
        "clRydXN0MSIwIAYDVQQDExlCYWx0aW1vcmUgQ3liZXJUcnVzdCBSb290MB4XDTIw\n"
        "MDEyNzEyNDgwOFoXDTI0MTIzMTIzNTk1OVowSjELMAkGA1UEBhMCVVMxGTAXBgNV\n"
        "BAoTEENsb3VkZmxhcmUsIEluYy4xIDAeBgNVBAMTF0Nsb3VkZmxhcmUgSW5jIEVD\n"
        "QyBDQS0zMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEua1NZpkUC0bsH4HRKlAe\n"
        "nQMVLzQSfS2WuIg4m4Vfj7+7Te9hRsTJc9QkT+DuHM5ss1FxL2ruTAUJd9NyYqSb\n"
        "16OCAWgwggFkMB0GA1UdDgQWBBSlzjfq67B1DpRniLRF+tkkEIeWHzAfBgNVHSME\n"
        "GDAWgBTlnVkwgkdYzKz6CFQ2hns6tQRN8DAOBgNVHQ8BAf8EBAMCAYYwHQYDVR0l\n"
        "BBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMBIGA1UdEwEB/wQIMAYBAf8CAQAwNAYI\n"
        "KwYBBQUHAQEEKDAmMCQGCCsGAQUFBzABhhhodHRwOi8vb2NzcC5kaWdpY2VydC5j\n"
        "b20wOgYDVR0fBDMwMTAvoC2gK4YpaHR0cDovL2NybDMuZGlnaWNlcnQuY29tL09t\n"
        "bmlyb290MjAyNS5jcmwwbQYDVR0gBGYwZDA3BglghkgBhv1sAQEwKjAoBggrBgEF\n"
        "BQcCARYcaHR0cHM6Ly93d3cuZGlnaWNlcnQuY29tL0NQUzALBglghkgBhv1sAQIw\n"
        "CAYGZ4EMAQIBMAgGBmeBDAECAjAIBgZngQwBAgMwDQYJKoZIhvcNAQELBQADggEB\n"
        "AAUkHd0bsCrrmNaF4zlNXmtXnYJX/OvoMaJXkGUFvhZEOFp3ArnPEELG4ZKk40Un\n"
        "+ABHLGioVplTVI+tnkDB0A+21w0LOEhsUCxJkAZbZB2LzEgwLt4I4ptJIsCSDBFe\n"
        "lpKU1fwg3FZs5ZKTv3ocwDfjhUkV+ivhdDkYD7fa86JXWGBPzI6UAPxGezQxPk1H\n"
        "goE6y/SJXQ7vTQ1unBuCJN0yJV0ReFEQPaA1IwQvZW+cwdFD19Ae8zFnWSfda9J1\n"
        "CZMRJCQUzym+5iPDuI9yP+kHyCREU3qzuWFloUwOxkgAyXVjBYdwRVKD05WdRerw\n"
        "6DEdfgkfCv4+3ao8XnTSrLE=\n"
        "-----END CERTIFICATE-----\n"
        "";

    struct TimeSeries
    {
        String symbol;
        float open;
        float high;
        float low;
        float close;
        float volume;
    };

    DynamicJsonDocument
    get(const char *extension)
    {
        String url{build_url(extension)};

        std::map<const char *, const char *> headers;

        return Client_::get(url.c_str(), rootCACertificate, headers);
    }

    int post(const char *extension, const char *body)
    {
        String url{build_url(extension)};

        std::map<const char *, const char *> headers;
        headers["Content-Type"] = "application/json";

        return Client_::post(url.c_str(), rootCACertificate, headers, body);
    }

    DynamicJsonDocument quote(const char *symbol)
    {
        String extension = String(F("function=GLOBAL_QUOTE&symbol=")) + String(symbol);
        return get(extension.c_str());
    }

    std::vector<TimeSeries> hourly(const char *symbol)
    {
        std::map<const char *, const char *> args;
        args["function"] = "TIME_SERIES_INTRADAY";
        args["symbol"] = symbol;
        args["interval"] = "60min";
        args["outputsize"] = "compact";

        String extension{build_query(args)};
        String url{build_url(extension.c_str())};
        DynamicJsonDocument response{get(url.c_str())};

        if (response["Meta Data"] == nullptr)
        {
            Serial.println(F("AlphaVantage rate limit exceeded."));
            delay(60000);
            return hourly(symbol);
        }

        JsonObject time_series{response[F("Time Series (60min)")]};

        std::vector<TimeSeries> time_series_vector;
        for (auto time_series_entry : time_series)
        {
            TimeSeries time_series;
            time_series.symbol = symbol;
            time_series.open = time_series_entry.value()[F("1. open")];
            time_series.high = time_series_entry.value()[F("2. high")];
            time_series.low = time_series_entry.value()[F("3. low")];
            time_series.close = time_series_entry.value()[F("4. close")];
            time_series.volume = time_series_entry.value()[F("5. volume")];

            time_series_vector.push_back(time_series);
        }

        std::reverse(time_series_vector.begin(), time_series_vector.end());

        return time_series_vector;
    }

    std::vector<TimeSeries> daily(const char *symbol)
    {
        std::map<const char *, const char *> args;
        args["function"] = "TIME_SERIES_DAILY_ADJUSTED";
        args["symbol"] = symbol;
        args["outputsize"] = "compact";

        String extension{build_query(args)};
        String url{build_url(extension.c_str())};
        DynamicJsonDocument response{get(url.c_str())};

        if (response[F("Meta Data")] == nullptr)
        {
            Serial.println(F("AlphaVantage rate limit exceeded."));
            delay(60000);
            return daily(symbol);
        }

        JsonObject time_series{response[F("Time Series (Daily)")]};

        std::vector<TimeSeries> time_series_vector;
        for (auto time_series_entry : time_series)
        {
            TimeSeries time_series;
            time_series.symbol = symbol;
            time_series.open = time_series_entry.value()[F("1. open")];
            time_series.high = time_series_entry.value()[F("2. high")];
            time_series.low = time_series_entry.value()[F("3. low")];
            time_series.close = time_series_entry.value()[F("5. adjusted close")];
            time_series.volume = time_series_entry.value()[F("6. volume")];

            time_series_vector.push_back(time_series);
        }

        std::reverse(time_series_vector.begin(), time_series_vector.end());

        return time_series_vector;
    }

    bool market_open()
    {
        DynamicJsonDocument doc{get("function=MARKET_STATUS")};

        JsonArray markets{doc[F("markets")]};

        StaticJsonDocument<256> us_market;
        for (auto market : markets)
        {
            if (market[F("region")] == F("United States"))
            {
                us_market = market;
            }
        }

        if (us_market[F("current_status")] == F("open"))
        {
            return true;
        }

        return false;
    }
}