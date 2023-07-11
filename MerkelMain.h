#pragma once
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

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

  std::string currentTime;
  OrderBook * orderBook;

  Wallet wallet;

    void getProductFilter(const std::string& product_name, const std::string& time_stamp, const std::string& order_type);

    void printFilterProducts(std::vector<OrderBookEntry> entries);

    double getOpenFromFilterProducts(std::vector<OrderBookEntry> entries);

    double getCloseFromFilterProducts(std::vector<OrderBookEntry> entries);

    double getHighFromFilterProducts(std::vector<OrderBookEntry> entries);

    double getLowFromFilterProducts(std::vector<OrderBookEntry> entries);
};