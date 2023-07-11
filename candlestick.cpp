//
// Created by nouman on 7/11/2023.
//
#include <string>
#include <vector>
#include "candelstick.h"

Candlestick::Candlestick(const std::string &x, const std::vector<double> &y) {
    _open = y[0];
    _high = y[1];
    _low = y[2];
    _close = y[3];
    _x = x;
}
Candlestick::~Candlestick() {}


