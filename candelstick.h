//
// Created by nouman on 7/11/2023.
//
/*
#include "colors.h"
#include "params.h"
#include "position.h"
#include <SFML/Graphics.hpp>
*/
#include <cmath>
#include <string>
#include <vector>
#include <ostream>
#include "OrderBookEntry.h"

#ifndef CURRENCY_EXCHANGE_CANDELSTICK_H
#define CURRENCY_EXCHANGE_CANDELSTICK_H


class Candlestick {
public:
    Candlestick();

    ~Candlestick();

    Candlestick(double open, double high, double low, double close, OrderBookType type, const std::string &product);

    double getOpen() const;

    void setOpen(double open);

    double getHigh() const;

    void setHigh(double high);

    double getLow() const;

    void setLow(double low);

    double getClose() const;

    void setClose(double close);

    friend std::ostream &operator<<(std::ostream &os, const Candlestick &candlestick);

    void setType(OrderBookType type);

    const std::string &getProduct() const;

    void setProduct(const std::string &product);

private:
    double _open;
    double _high;
    double _low;
    double _close;
    OrderBookType _type;
    std::string product;
    std::string _x;

};
#endif //CURRENCY_EXCHANGE_CANDELSTICK_H
