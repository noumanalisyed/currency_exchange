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

std::ostream &operator<<(std::ostream &os, const SearchObject &object) {
    os << "_currentTimeStampIndex: " << object._currentTimeStampIndex << " _previousTimeStampIndex: "
       << object._previousTimeStampIndex << " _strCurrentTimeStamp: " << object._strCurrentTimeStamp
       << " _strPreviousTimeStamp: " << object._strPreviousTimeStamp;
    return os;
}
