# ESP32 Paper Trader
This is a paper trader for an ESP32. I made it to test out trading models without any emotional component to it. <br>
It uses [AlphaVantage](https://www.alphavantage.co) to get informatin and [Alpaca](https://alpaca.markets) to make the trades.

The api is kind of coded to be Alpaca and AlphaVantage, my  trading model doesn't go over the API limits for either but they do come pretty close(if you recompile within a certain window, it will go over). They can be improved by fetching the data once and passing it into the trading models.

Uses TALib and ArduinoJson