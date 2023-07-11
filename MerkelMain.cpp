#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include <limits>
#include "OrderBookEntry.h"
#include "CSVReader.h"

MerkelMain::MerkelMain()
{
    std::cout<<"MerkelMain -- Default Constructor "<<std::endl;
    orderBook = new OrderBook("E:\\c-workspace\\currency-exchange-simulator\\20200601.csv");
}

void MerkelMain::init()
{
  int input;
  std::cout<<"MerkelMain -- init() "<<std::endl;
  currentTime = orderBook->getEarliestTime();
  std::cout<<"MerkelMain -- After get Earliest Time "<<std::endl;
  wallet.insertCurrency("BTC", 10);

  while (true)
  {
    printMenu();
    input = getUserOption();
    processUserOption(input);
  }
};

void MerkelMain::printMenu()
{
  // 1 print help
  std::cout << "1: print help " << std::endl;
  // 2 print exchange stats
  std::cout << "2: print exchange stats " << std::endl;
  // 3 make an offer
  std::cout << "3: make an ask " << std::endl;
  // 4 make a bid
  std::cout << "4: make a bid " << std::endl;
  // 5 print wallet
  std::cout << "5: print wallet " << std::endl;
  // 6 continue
  std::cout << "6: continue " << std::endl;

  std::cout << "7: Product Filter " << std::endl;

  std::cout << "============== " << std::endl;
  std::cout << "Type in 1-7" << std::endl;

  std::cout << "Current time is " << currentTime << std::endl;
}

int MerkelMain::getUserOption()
{
  int userOption = 0;
  std::string line;
  std::cout << "Type 1-6" << std::endl;
  std::getline(std::cin, line);
  try
  {
    /* code */
    userOption = std::stoi(line);
  }
  catch (const std::exception &e)
  {
  }

  std::cout << "You chose " << userOption << std::endl;
  return userOption;
}

void MerkelMain::printHelp()
{
  std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers" << std::endl;
}

void MerkelMain :: printAllProducts(std::vector<OrderBookEntry> entries){

    std::cout << "Time Stamp\t\t\t Product\t Type\t Price\t\t Amount" << std::endl;
    for (OrderBookEntry &p : entries)
    {
        std::cout <<p.timestamp<<"\t"<<p.product<<"\t\t"<<"ASK"<<"\t"<<p.price<<"\t"<<p.amount << std::endl;
    }
}
void MerkelMain::printMarketStats()
{

  for (std::string const &p : orderBook->getKnownProducts())
  {
    std::cout << "Product: " << p << std::endl;
    std::vector<OrderBookEntry> entries = orderBook->getOrders(OrderBookType::ask,
                                                              p, currentTime);
    std::cout << "Asks seen: " << entries.size() << std::endl;
    std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
    std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
  }


  for (std::string const &p : orderBook->getKnownProducts())
  {
    std::cout << "Product: " << p << std::endl;
    std::vector<OrderBookEntry> entries = orderBook->getOrders(OrderBookType::ask,
                                                              p, currentTime);
    std::cout << "Asks seen: " << entries.size() << std::endl;
    std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
    std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
  }

};
void MerkelMain::getProductFilter(const std::string& product_name, const std::string& time_stamp, const std::string& order_type)
{
    std::vector<OrderBookEntry> entries;
    if(order_type=="ASK"){
        entries =  orderBook->getOrders(OrderBookType::ask,
                                                                    product_name,time_stamp);
    }else{
        entries =  orderBook->getOrders(OrderBookType::bid,
                                                                   product_name,time_stamp);
    }
    printAllProducts(entries);

}
void MerkelMain::enterAsk()
{
  std::cout << "Make an ask - enter the amount: product,price,amount, eg: ETH/BTC,200,0.5" << std::endl;
  std::string input;
  std::getline(std::cin, input);

  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
  if (tokens.size() != 3)
  {
    std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;
  }
  else
  {
    try
    {
      OrderBookEntry obe = CSVReader::stringsToOBE(
          tokens[1],
          tokens[2],
          currentTime,
          tokens[0],
          OrderBookType::ask);

          obe.username = "simuser";
          
      if (wallet.canFulfillOrder(obe))
      {
        std::cout << "Wallet looks good. " << std::endl;
        orderBook->insertOrder(obe);
      }
      else
      {
        std::cout << "Wallet has insufficient funds. " << std::endl;
      }
    }
    catch (const std::exception &e)
    {
      std::cout << "MerkelMain::enterAsk Bad input " << std::endl;
    }
  };
}

void MerkelMain::enterBid()
{
  std::cout << "Make a bid - enter the amount: product,price,amount, eg: ETH/BTC,200,0.5" << std::endl;
  std::string input;
  std::getline(std::cin, input);

  std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
  if (tokens.size() != 3)
  {
    std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
  }
  else
  {
    try
    {
      OrderBookEntry obe = CSVReader::stringsToOBE(
          tokens[1],
          tokens[2],
          currentTime,
          tokens[0],
          OrderBookType::bid);

          obe.username = "simuser";

      if (wallet.canFulfillOrder(obe))
      {
        std::cout << "Wallet looks good. " << std::endl;
        orderBook->insertOrder(obe);
      }
      else
      {
        std::cout << "Wallet has insufficient funds. " << std::endl;
      }
    }
    catch (const std::exception &e)
    {
      std::cout << "MerkelMain::enterBid Bad input " << std::endl;
    }
  };
}
void MerkelMain::printWallet()
{
  std::cout << "Your wallet is empty" << std::endl;
  std::cout << wallet.toString() << std::endl;
}

void MerkelMain::goToNextTimeFrame()
{
  std::cout << "Going to next time frame" << std::endl;
  std::vector<OrderBookEntry> sales = orderBook->matchAsksToBids("ETH/BTC", currentTime);
  std::cout << "Sales: " << sales.size() << std::endl;
  for (OrderBookEntry &sale : sales)
  {
    std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
    if (sale.username == "simuser")
    {
      // update the wallet
      wallet.processSale(sale);
    }
  }
  currentTime = orderBook->getNextTime(currentTime);
}

void MerkelMain::processUserOption(int userOption)
{
  if (userOption == 0) // bad input
  {
    std::cout << "Invalid choice. choose 1-6" << std::endl;
  }
  if (userOption == 1) // bad input
  {
    printHelp();
  }
  if (userOption == 2) // bad input
  {
    printMarketStats();
  }
  if (userOption == 3) // bad input
  {
    enterAsk();
  }
  if (userOption == 4) // bad input
  {
    enterBid();
  }
  if (userOption == 5) // bad input
  {
    printWallet();
  }
  if (userOption == 6) // bad input
  {
    goToNextTimeFrame();
  }
  if (userOption == 7) // bad input
  {
      getProductFilter("ETH/BTC","2020/06/01 11:57:30.328127","ASK");
  }
}