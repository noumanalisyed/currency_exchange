//
// Created by nouman on 7/14/2023.
//

#ifndef CURRENCY_EXCHANGE_SEARCHOBJECT_H
#define CURRENCY_EXCHANGE_SEARCHOBJECT_H

#include <string>
#include <ostream>

class SearchObject {
public:
    SearchObject();
    SearchObject(const std::string &currentTimeStamp, const std::string &previousTimeStamp,
                 const int currentTimeStampIndex, const int previousTimeStampIndex);
    ~SearchObject();

    int getCurrentTimeStampIndex();

    void setCurrentTimeStampIndex(int currentTimeStampIndex);

    int getPreviousTimeStampIndex() const;

    void setPreviousTimeStampIndex(int previousTimeStampIndex);

    const std::string &getStrCurrentTimeStamp() const;

    void setStrCurrentTimeStamp(const std::string &strCurrentTimeStamp);

    const std::string &getStrPreviousTimeStamp() const;

    void setStrPreviousTimeStamp(const std::string &strPreviousTimeStamp);

    friend std::ostream &operator<<(std::ostream &os, const SearchObject &object);

private:
    int _currentTimeStampIndex;
    int _previousTimeStampIndex;
    std::string  _strCurrentTimeStamp;
    std::string  _strPreviousTimeStamp;
};
#endif //CURRENCY_EXCHANGE_SEARCHOBJECT_H
