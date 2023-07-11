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

#ifndef CURRENCY_EXCHANGE_SIMULATOR_CANDELSTICK_H
#define CURRENCY_EXCHANGE_SIMULATOR_CANDELSTICK_H


class Candlestick {
public:
    Candlestick(const std::string &x, const std::vector<double> &y);
    ~Candlestick();



private:
    double _open;
    double _high;
    double _low;
    double _close;
    double _bodyHeight;
    std::string _x;
};





#endif //CURRENCY_EXCHANGE_SIMULATOR_CANDELSTICK_H
