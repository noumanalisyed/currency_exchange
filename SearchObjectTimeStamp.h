//
// Created by nouman on 7/14/2023.
//

#ifndef CURRENCY_EXCHANGE_SEARCHOBJECTTIMESTAMP_H
#define CURRENCY_EXCHANGE_SEARCHOBJECTTIMESTAMP_H

#include <string>
#include <ostream>

class SearchObjectTimeStamp {
public:
    SearchObjectTimeStamp();
    SearchObjectTimeStamp(const std::string &currentTimeStamp, const std::string &previousTimeStamp,
                 const int currentTimeStampIndex, const int previousTimeStampIndex);


    ~SearchObjectTimeStamp();

    int getCurrentTimeStampIndex()  const;

    void setCurrentTimeStampIndex(int currentTimeStampIndex);

    int getPreviousTimeStampIndex() const;

    void setPreviousTimeStampIndex(int previousTimeStampIndex);

    const std::string &getStrCurrentTimeStamp() const;

    void setStrCurrentTimeStamp(const std::string &strCurrentTimeStamp);

    const std::string &getStrPreviousTimeStamp() const;

    void setStrPreviousTimeStamp(const std::string &strPreviousTimeStamp);

    const std::string &getProduct() const;

    void setProduct(const std::string &product);

    const std::string &getType() const;

    void setType(const std::string &type);

    friend std::ostream &operator<<(std::ostream &os, const SearchObjectTimeStamp &object);

private:
    int _currentTimeStampIndex;
    int _previousTimeStampIndex;
    std::string  _strCurrentTimeStamp;
    std::string  _strPreviousTimeStamp;
};
#endif //CURRENCY_EXCHANGE_SEARCHOBJECTTIMESTAMP_H
