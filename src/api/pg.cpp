#include <WiFi.h>
#include <SimplePgSQL.h>
#include "api/client.h"
#include "config.h"
#include <vector>

namespace PG
{
    PGconnection conn(&Client_::client);
    std::vector<String> queries{};

    IPAddress ip_from_aws_url()
    {
        IPAddress ip;
        WiFi.hostByName(AWS_DB_URL, ip);
        return ip;
    }

    bool db_available()
    {
        return conn.status() == CONNECTION_OK;
    }

    bool can_connect{false};

    int connect()
    {
        conn.setDbLogin(ip_from_aws_url(), AWS_DB_USER, AWS_DB_PASSWORD, AWS_DB_NAME);
        while (conn.status() != CONNECTION_OK && conn.status() != CONNECTION_BAD)
        {
            switch (conn.status())
            {
            case CONNECTION_NEEDED:
                conn.setDbLogin(ip_from_aws_url(), AWS_DB_USER, AWS_DB_PASSWORD, AWS_DB_NAME);
                break;
            case CONNECTION_BAD:
                Serial.println("Connection bad");
                break;
            case CONNECTION_AWAITING_RESPONSE:
            case CONNECTION_AUTH_OK:
            default:
                break;
            }
        }

        if (conn.status() == CONNECTION_BAD)
        {
            Serial.println("Connection bad");
            conn.close();
            can_connect = false;
            return 1;
        }
        else
        {
            Serial.println("Connection good");
            can_connect = true;
            return 0;
        }
    }

    void add_query(String query)
    {
        if (can_connect)
        {
            queries.push_back(query);
        }
    }

    void insert_queries()
    {
        if (!can_connect)
        {
            Serial.println("Cannot connect");
            return;
        }

        if (queries.size() == 0)
        {
            Serial.println("No queries to insert");
            return;
        }

        if (!db_available())
        {
            Serial.println("DB not available");
            return;
        }

        String query;
        for (int i = 0; i < queries.size(); i++)
        {
            query += queries[i];
            if (queries[i][queries[i].length() - 1] != ';')
            {
                query += ";";
            }
        }

        if (conn.execute(query.c_str()))
        {
            Serial.println("Error executing query");
            conn.getData();
            Serial.println(conn.getMessage());
        }
        else
        {
            Serial.println("Query executed");
        }
    }
}