#include "SearchObjectTimeStamp.h"

//
// Created by nouman on 7/14/2023.
//
SearchObjectTimeStamp::SearchObjectTimeStamp(){
    _currentTimeStampIndex = 0;
    _previousTimeStampIndex = 0;
    _strCurrentTimeStamp = "";
    _strPreviousTimeStamp = "";
}
SearchObjectTimeStamp::SearchObjectTimeStamp(const std::string &currentTimeStamp, const std::string &previousTimeStamp,
             const int currentTimeStampIndex, const int previousTimeStampIndex){
    _currentTimeStampIndex = currentTimeStampIndex;
    _previousTimeStampIndex = previousTimeStampIndex;
    _strCurrentTimeStamp = currentTimeStamp;
    _strPreviousTimeStamp = previousTimeStamp;
}
SearchObjectTimeStamp::~SearchObjectTimeStamp(){

}

void SearchObjectTimeStamp::setCurrentTimeStampIndex(int currentTimeStampIndex) {
    _currentTimeStampIndex = currentTimeStampIndex;
}

int SearchObjectTimeStamp::getCurrentTimeStampIndex()  const {
    return _currentTimeStampIndex;
}

int SearchObjectTimeStamp::getPreviousTimeStampIndex() const {
    return _previousTimeStampIndex;
}

void SearchObjectTimeStamp::setPreviousTimeStampIndex(int previousTimeStampIndex) {
    _previousTimeStampIndex = previousTimeStampIndex;
}

const std::string &SearchObjectTimeStamp::getStrCurrentTimeStamp() const {
    return _strCurrentTimeStamp;
}

void SearchObjectTimeStamp::setStrCurrentTimeStamp(const std::string &strCurrentTimeStamp) {
    _strCurrentTimeStamp = strCurrentTimeStamp;
}

const std::string &SearchObjectTimeStamp::getStrPreviousTimeStamp() const {
    return _strPreviousTimeStamp;
}

void SearchObjectTimeStamp::setStrPreviousTimeStamp(const std::string &strPreviousTimeStamp) {
    _strPreviousTimeStamp = strPreviousTimeStamp;
}


std::ostream &operator<<(std::ostream &os, const SearchObjectTimeStamp &object) {
    os << "_currentTimeStampIndex: " << object._currentTimeStampIndex << " _previousTimeStampIndex: "
       << object._previousTimeStampIndex << " _strCurrentTimeStamp: " << object._strCurrentTimeStamp
       << " _strPreviousTimeStamp: " << object._strPreviousTimeStamp ;
    return os;
}
