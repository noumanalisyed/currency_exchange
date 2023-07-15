//
// Created by nouman on 7/11/2023.
//
#include <string>
#include <utility>
#include <vector>
#include "candelstick.h"

Candlestick::Candlestick() {}

Candlestick::Candlestick(double open, double high, double low, double close, OrderBookType type,
                         const std::string &product) : _open(open), _high(high), _low(low), _close(close), _type(type),
                                                       _product(product) {}

double Candlestick::getOpen() const {
    return _open;
}

void Candlestick::setOpen(double open) {
    _open = open;
}

double Candlestick::getHigh() const {
    return _high;
}

void Candlestick::setHigh(double high) {
    _high = high;
}

double Candlestick::getLow() const {
    return _low;
}

void Candlestick::setLow(double low) {
    _low = low;
}

double Candlestick::getClose() const {
    return _close;
}

void Candlestick::setClose(double close) {
    _close = close;
}

OrderBookType Candlestick::getType() const {
    return _type;
}

void Candlestick::setType(OrderBookType type) {
    _type = type;
}

const std::string &Candlestick::getProduct() const {
    return _product;
}

void Candlestick::setProduct(const std::string &product) {
    _product = product;
}

std::ostream &operator<<(std::ostream &os, const Candlestick &candlestick) {
    os << "_open: " << candlestick._open << " _high: " << candlestick._high << " _low: " << candlestick._low
       << " _close: " << candlestick._close << " _product: " << candlestick._product<<std::endl;
    return os;
}





