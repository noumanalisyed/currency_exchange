cmake_minimum_required(VERSION 3.25)
project(currency_exchange)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(currency_exchange
        CSVReader.cpp
        CSVReader.h
        main.cpp
        MerkelMain.cpp
        MerkelMain.h
        OrderBook.cpp
        OrderBook.h
        OrderBookEntry.cpp
        OrderBookEntry.h
        Wallet.cpp
        Wallet.h
        candlestick.cpp SearchObject.h SearchObject.h SearchObject.cpp)
