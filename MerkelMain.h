#pragma once
#include <vector>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include "SearchObject.h"
#include "candelstick.h"

class MerkelMain
{
public:
  MerkelMain();
  /** call this to start the sim*/
  void init();

private:
  void printMenu();
  int getUserOption();
  void printHelp();
  void printMarketStats();
  void enterAsk();
  void enterBid();
  void printWallet();
  void goToNextTimeFrame();
  void processUserOption(int userOption);

  void createCandelStick();

  std::string currentTime;
  OrderBook * orderBook;
  std::vector<OrderBookEntry> entries;
  std::unordered_map<std::string , int> uniqueTimeStampValues;
  std::unordered_map<std::string, int> uniqueProductValues;
  std::vector<OrderBookEntry> vectorAsk[10];
  std::vector<OrderBookEntry> vectorBid[10];
  std::vector<std::pair<std::string , int>> *sortedData;
  Wallet wallet;
  SearchObject **searchObject;
  Candlestick **candlestick;
    int sizeTimeStamps = 0;
    int sizeProducts = 0;
    std::vector<std::string> vectorProducts;

    std::vector<OrderBookEntry> getProductFilter(const std::string& product_name,
                                                 const std::string& time_stamp,
                                                 const std::string& order_type);

    void printFilterProducts(std::vector<OrderBookEntry> entries);

    double getOpenFromFilterProducts(std::vector<OrderBookEntry> entries);

    double getCloseFromFilterProducts(std::vector<OrderBookEntry> entries);

    double getHighFromFilterProductsBid(std::vector<OrderBookEntry> entries, std::string product,
                                                      std::string timestamp,OrderBookType type);

    double getHighFromFilterProductsAsk(std::vector<OrderBookEntry> entries, std::string product,
                                        std::string timestamp,OrderBookType type);

    double getLowFromFilterProductsBid(std::vector<OrderBookEntry> entries, std::string product,
                                        std::string timestamp,OrderBookType type);

    double getLowFromFilterProductsAsk(std::vector<OrderBookEntry> entries, std::string product,
                                        std::string timestamp,OrderBookType type);


    void splitTimeStampByUniqueValues();

    void splitProductsByUniqueValues();

    int getPreviousTimeStampIndex(std::string timeStamp);

    void sort_map(std::unordered_map<std::string, int> unorderedMap);

    bool static comp(const std::pair<std::string ,int>& a, const std::pair<std::string,int>& b);

    int getCurrentTimeStampIndex(std::string timeStamp);

    std::string getCurrentTimeStamp(std::string timeStamp);
    std::string getPreviousTimeStamp(std::string timeStamp);

    double getAverageFromFilterProductBid(std::string timestamp,
                                          std::string product,enum OrderBookType type);

    void initCandleStick();

    double getAverageFromFilterProductAsk(std::string timestamp, std::string product, OrderBookType type);
};