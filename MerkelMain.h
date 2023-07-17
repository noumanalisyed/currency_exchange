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
#include "SearchObjectTimeStamp.h"



class MerkelMain
{
public:
  MerkelMain();
  /** call this to start the sim*/
  void init();
    std::vector<OrderBookEntry>  getProductWiseFilter(const std::string& product_name);
    void printMenu();
    int getUserOption();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void goToNextTimeFrame();
    void processUserOption(int userOption);
    void drawCandlestickChart(const std::vector<Candlestick>& data);
    void  createCandelStick();

private:


  //void MerkelMain::createCandelStick(std::string product, OrderBookType type)

  std::string currentTime;
  OrderBook * orderBook;
  std::vector<OrderBookEntry> entries;
  std::unordered_map<int, OrderBookEntry> uniqueOrderBookEntry;
  std::unordered_map<std::string, int> uniqueTimeStampValues;
  std::unordered_map<std::string, int> uniqueProductValues;
  std::vector<OrderBookEntry> vectorAsk[10];
  std::vector<OrderBookEntry> vectorBid[10];
  std::vector<std::pair<std::string, int>> *sortedDataTimeStamps;
  std::vector<std::pair<int, OrderBookEntry>> *sortedDataOderBookEntry;

  std::vector<Candlestick> candleStickAsk;
  std::vector< Candlestick> candleStickBid;
  std::string ** graph;

  Wallet wallet;
  std::vector<SearchObject> searchObject;
  std::vector<SearchObjectTimeStamp> searchObjectTimeStamp;
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

    void sort_map(std::unordered_map<std::string,int> unorderedMap);


    void sort_map_orderBookEntry(std::unordered_map<int, OrderBookEntry> unorderedMap);

    bool static comp_orderBookEntry(std::pair<int, OrderBookEntry> &a,
                                         std::pair<int, OrderBookEntry> &b);

    bool static comp(std::pair<std::string , int> & a,std::pair<std::string , int> & b);


    int getCurrentTimeStampIndex(std::string timeStamp);

    std::string getCurrentTimeStamp(std::string timeStamp);
    std::string getPreviousTimeStamp(std::string timeStamp);

    double getAverageFromFilterProductBid(std::string timestamp,
                                          std::string product,enum OrderBookType type);

    void initCandleStick();

    double getAverageFromFilterProductAsk(std::string timestamp, std::string product, OrderBookType type);


};