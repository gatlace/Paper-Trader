#include "models/base.h"
#include "models/ta.h"

namespace TA
{
    void init()
    {
        int retCode = TA_Initialize();
        if (retCode != TA_SUCCESS)
        {
            Serial.println("TA_Initialize failed");
        }
    }

    TA_RetCode EMA(std::vector<float> &prices, int period, std::vector<float> &outReal)
    {
        int startIdx = 0;
        int endIdx = prices.size() - 1;
        int outBegIdx = 0;
        int outNbElement = 0;
        double *outReal_ = new double[prices.size()];
        double *inReal = new double[prices.size()];
        for (int i = 0; i < prices.size(); i++)
        {
            inReal[i] = prices[i];
        }

        TA_RetCode retCode = TA_EMA(startIdx, endIdx, inReal, period, &outBegIdx, &outNbElement, outReal_);

        if (retCode != TA_SUCCESS)
        {
            Serial.println("TA_EMA failed");
        }
        else
        {
            for (int i = 0; i < outNbElement; i++)
            {
                outReal.push_back(outReal_[i]);
            }
        }

        return retCode;
    }

    TA_RetCode RSI(std::vector<float> &prices, int period, std::vector<float> &outReal)
    {
        int startIdx = 0;
        int endIdx = prices.size() - 1;
        int outBegIdx = 0;
        int outNbElement = 0;
        double *outReal_ = new double[prices.size()];
        double *inReal = new double[prices.size()];
        for (int i = 0; i < prices.size(); i++)
        {
            inReal[i] = prices[i];
        }

        TA_RetCode retCode = TA_RSI(startIdx, endIdx, inReal, period, &outBegIdx, &outNbElement, outReal_);

        if (retCode != TA_SUCCESS)
        {
            Serial.println("TA_RSI failed");
        }
        else
        {
            for (int i = 0; i < outNbElement; i++)
            {
                outReal.push_back(outReal_[i]);
            }
        }

        return retCode;
    }

    TA_RetCode MACD(std::vector<float> &prices, int fastPeriod, int slowPeriod, int signalPeriod, std::vector<float> &outMACD, std::vector<float> &outMACDSignal, std::vector<float> &outMACDHist)
    {
        int startIdx = 0;
        int endIdx = prices.size() - 1;
        int outBegIdx = 0;
        int outNbElement = 0;
        double *outMACD_ = new double[prices.size()];
        double *outMACDSignal_ = new double[prices.size()];
        double *outMACDHist_ = new double[prices.size()];
        double *inReal = new double[prices.size()];
        for (int i = 0; i < prices.size(); i++)
        {
            inReal[i] = prices[i];
        }

        TA_RetCode retCode = TA_MACD(startIdx, endIdx, inReal, fastPeriod, slowPeriod, signalPeriod, &outBegIdx, &outNbElement, outMACD_, outMACDSignal_, outMACDHist_);

        if (retCode != TA_SUCCESS)
        {
            Serial.println("TA_MACD failed");
        }
        else
        {
            for (int i = 0; i < outNbElement; i++)
            {
                outMACD.push_back(outMACD_[i]);
                outMACDSignal.push_back(outMACDSignal_[i]);
                outMACDHist.push_back(outMACDHist_[i]);
            }
        }

        return retCode;
    }
}