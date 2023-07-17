#include "SearchObject.h"

//
// Created by nouman on 7/14/2023.
//
SearchObject::SearchObject(){
    _currentTimeStampIndex = 0;
    _previousTimeStampIndex = 0;
    _strCurrentTimeStamp = "";
    _strPreviousTimeStamp = "";
}
SearchObject::SearchObject(const std::string &currentTimeStamp, const std::string &previousTimeStamp,
             const int currentTimeStampIndex, const int previousTimeStampIndex){
    _currentTimeStampIndex = currentTimeStampIndex;
    _previousTimeStampIndex = previousTimeStampIndex;
    _strCurrentTimeStamp = currentTimeStamp;
    _strPreviousTimeStamp = previousTimeStamp;
}
SearchObject::~SearchObject(){

}

void SearchObject::setCurrentTimeStampIndex(int currentTimeStampIndex) {
    _currentTimeStampIndex = currentTimeStampIndex;
}

int SearchObject::getPreviousTimeStampIndex() const {
    return _previousTimeStampIndex;
}

void SearchObject::setPreviousTimeStampIndex(int previousTimeStampIndex) {
    _previousTimeStampIndex = previousTimeStampIndex;
}

const std::string &SearchObject::getStrCurrentTimeStamp() const {
    return _strCurrentTimeStamp;
}

void SearchObject::setStrCurrentTimeStamp(const std::string &strCurrentTimeStamp) {
    _strCurrentTimeStamp = strCurrentTimeStamp;
}

const std::string &SearchObject::getStrPreviousTimeStamp() const {
    return _strPreviousTimeStamp;
}

void SearchObject::setStrPreviousTimeStamp(const std::string &strPreviousTimeStamp) {
    _strPreviousTimeStamp = strPreviousTimeStamp;
}


SearchObject::SearchObject(int currentTimeStampIndex, int previousTimeStampIndex,
                           const std::string &strCurrentTimeStamp, const std::string &strPreviousTimeStamp,
                           const std::string &product, const std::string &type) : _currentTimeStampIndex(
        currentTimeStampIndex), _previousTimeStampIndex(previousTimeStampIndex), _strCurrentTimeStamp(
        strCurrentTimeStamp), _strPreviousTimeStamp(strPreviousTimeStamp), _product(product), _type(type) {}

const std::string &SearchObject::getProduct() const {
    return _product;
}

void SearchObject::setProduct(const std::string &product) {
    _product = product;
}

const std::string &SearchObject::getType() const {
    return _type;
}

void SearchObject::setType(const std::string &type) {
    _type = type;
}

std::ostream &operator<<(std::ostream &os, const SearchObject &object) {
    os << "_currentTimeStampIndex: " << object._currentTimeStampIndex << " _previousTimeStampIndex: "
       << object._previousTimeStampIndex << " _strCurrentTimeStamp: " << object._strCurrentTimeStamp
       << " _strPreviousTimeStamp: " << object._strPreviousTimeStamp << " _product: " << object._product << " _type: "
       << object._type;
    return os;
}
