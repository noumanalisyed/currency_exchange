#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <set>
#include <unordered_map>
#include <algorithm>

bool MerkelMain::comp(const std::pair<std::string, int> &a,
               const std::pair<std::string, int> &b)
{
    return (a.second < b.second);
}

void MerkelMain::sort_map(std::unordered_map<std::string, int> unorderedMap) {
    sortedData = new std::vector<std::pair<std::string , int>>(unorderedMap.begin(), unorderedMap.end());
    std::sort(sortedData->begin(), sortedData->end(), comp);
}


MerkelMain::MerkelMain()
{
    std::cout<<"MerkelMain -- Default Constructor "<<std::endl;

    orderBook = new OrderBook("E:\\c-workspace\\currency_exchange\\20200601.csv");
    entries = orderBook->getAllOrders();
    splitTimeStampByUniqueValues(entries);
    splitProductsByUniqueValues(entries);
    std::cout<<"Unique Time Stamps : "<<uniqueTimeStampValues.size()<<std::endl;
    searchObject = new SearchObject* [uniqueTimeStampValues.size()];
    candlestick = new Candlestick * [uniqueTimeStampValues.size()];

    std::cout<<"Unique Products  : "<<uniqueProductValues.size()<<std::endl;
    std::string sample;
    sort_map(uniqueTimeStampValues);
    int objectIndex =0;
    int count =1;
    for (const auto& i : *(sortedData)) {
        std::cout <<count++<<".  "<< i.first << "    " << i.second << std::endl;
        int index = getCurrentTimeStampIndex(i.first);
        int indexPrevious = getPreviousTimeStampIndex(i.first);
        std::string strCurrentTimeStamp = getCurrentTimeStamp(i.first);
        std::string strPreviousTimeStamp = getPreviousTimeStamp(i.first);
        searchObject[objectIndex] = new SearchObject(strCurrentTimeStamp,strPreviousTimeStamp,index,indexPrevious);
        std::cout<<"Time Stamp  "<< i.first<<", index : "<<index<<", Previous Index : "<<indexPrevious
        <<", Current Time Stamp : "<<strCurrentTimeStamp<<",  Previous Time Stamp : "<<strPreviousTimeStamp<<std::endl;
    }

    createCandelStick();

    for (int i = 0, j = 0; i < 5; j++, i++) {
        std::cout<<candlestick[i][j];
    }

}
int MerkelMain::getCurrentTimeStampIndex(std::string timeStamp){
    int count =1;
    int index = 0;
    for (const auto& i : *(sortedData)) {
        index = i.second;
        if(timeStamp == i.first)
            break;
        count++;
    }
    return index;
}

int MerkelMain::getPreviousTimeStampIndex(std::string timeStamp){
    int count =1;
    int index = 0;
    int prevIndex = -1;
    for (const auto& i : *(sortedData)) {
        prevIndex = index;
        index = i.second;
        if(timeStamp == i.first)
            break;
        count++;
    }
    return prevIndex;
}
std::string MerkelMain::getCurrentTimeStamp(std::string timeStamp){
    int count =1;
    int index = 0;
    std::string strCurrentTimeStamp;
    for (const auto& i : *(sortedData)) {
        index = i.second;
        strCurrentTimeStamp = i.first;
        if(timeStamp == i.first)
            break;
        count++;
    }
    return strCurrentTimeStamp;
}

std::string MerkelMain::getPreviousTimeStamp(std::string timeStamp){
    int count =1;
    int index = 0;
    int prevIndex = -1;
    std::string strPreviousTimeStamp;
    std::string strCurrentTimeStamp;
    for (const auto& i : *(sortedData)) {
        prevIndex = index;
        index = i.second;
        strPreviousTimeStamp = strCurrentTimeStamp;
        strCurrentTimeStamp = i.first;
        if(timeStamp == i.first)
            break;
        count++;
    }
    return strPreviousTimeStamp;
}

void MerkelMain::createCandelStick(){

    int size = uniqueProductValues.size();
    std::string strProducts[size];
    int z = 0;
    for (auto const& element : uniqueProductValues)
    {
        strProducts[z++] = element.first;  // Write to file or whatever you want to do
    }
    int i = 0;
    while (i < size) {
        int j = 0;
        while (j < sortedData->size()) {
            double open = getAverageFromFilterProductAsk(entries, searchObject[i]->getStrPreviousTimeStamp(),
                                                      strProducts[i], OrderBookType::ask);
            double close = getAverageFromFilterProductAsk(entries, searchObject[i]->getStrCurrentTimeStamp(),
                                                       strProducts[i], OrderBookType::ask);
            double low = getLowFromFilterProductsAsk(entries,strProducts[i],
                                                     searchObject[i]->getStrCurrentTimeStamp(),OrderBookType::ask);
            double high = getHighFromFilterProductsAsk(entries,strProducts[i],
                                                      searchObject[i]->getStrCurrentTimeStamp(),OrderBookType::ask);
            candlestick[i][j].setClose(close);
            candlestick[i][j].setHigh(high);
            candlestick[i][j].setLow(low);
            candlestick[i][j].setOpen(open);
            candlestick[i][j].setProduct(strProducts[i]);
            candlestick[i][j].setType(OrderBookType::ask);

            j++;
        }
        i++;
    }
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

void MerkelMain::printMenu(){
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
  std::cout << "Type 1 - 7" << std::endl;
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

double MerkelMain::getAverageFromFilterProductAsk(std::vector<OrderBookEntry> entries, std::string timestamp,
                                               std::string product,enum OrderBookType type){
    double total_price = 0;
    double total_amount = 0;
    double open_current_instance = 0;
    for (OrderBookEntry &p : entries)
    {
        if ((p.product == product) && (p.timestamp == timestamp) && (type == OrderBookType::ask)) {
                total_price += p.price;
                total_amount += p.amount;
        }
    }
    open_current_instance = total_amount /total_price;
    return open_current_instance;
}

double getAverageFromFilterProductBid(std::vector<OrderBookEntry> entries, std::string timestamp,
                                      std::string product,enum OrderBookType type)
{
    double total_price = 0;
    double total_amount = 0;
    double open_current_instance = 0;
    for (OrderBookEntry &p : entries)
    {
            if ((p.product == product) && (p.timestamp == timestamp) && (type == OrderBookType::bid)) {
                total_price += p.price;
                total_amount += p.amount;
            }
            else{
                break;
            }
    }
    open_current_instance = total_amount /total_price;
    return open_current_instance;
}


double MerkelMain :: getOpenFromFilterProducts(std::vector<OrderBookEntry> entries){
   double total_price = 0;
   double total_amount = 0;
   double open_current_instance = 0;
    for (OrderBookEntry &p : entries)
    {
        total_price += p.price;
        total_amount += p.amount;
    }
    open_current_instance = total_amount /total_price;
    return open_current_instance;

}

double MerkelMain :: getCloseFromFilterProducts(std::vector<OrderBookEntry> entries){

    double total_price = 0;
    double total_amount = 0;
    double close_current_instance = 0;
    for (OrderBookEntry &p : entries)
    {
        total_price += p.price;
        total_amount += p.amount;
    }
    close_current_instance = total_amount /total_price;
    return close_current_instance;

}

double MerkelMain :: getLowFromFilterProductsAsk(std::vector<OrderBookEntry> entries, std::string product,
                                                 std::string timestamp,OrderBookType type){
    double low_current_instance = orderBook->getHighPrice(entries);
    for (OrderBookEntry &p : entries)
    {
        if ((p.product == product) && (p.timestamp == timestamp) && (type == OrderBookType::ask)) {
            if( low_current_instance > p.price)
                low_current_instance = p.price;
        }
        else{
            break;
        }
    }
    return low_current_instance;
}

double MerkelMain :: getLowFromFilterProductsBid(std::vector<OrderBookEntry> entries, std::string product,
                                              std::string timestamp,OrderBookType type){
    double low_current_instance = orderBook->getHighPrice(entries);
    for (OrderBookEntry &p : entries)
    {
        if ((p.product == product) && (p.timestamp == timestamp) && (type == OrderBookType::bid)) {
            if( low_current_instance > p.price)
                low_current_instance = p.price;
        }
        else{
            break;
        }
    }
    return low_current_instance;
}

double MerkelMain :: getHighFromFilterProductsAsk(std::vector<OrderBookEntry> entries, std::string product,
                                               std::string timestamp,OrderBookType type){
    double high_current_instance = orderBook->getLowPrice(entries);
    for (OrderBookEntry &p : entries)
    {
        if ((p.product == product) && (p.timestamp == timestamp) && (type == OrderBookType::ask)) {
            if( high_current_instance < p.price)
                high_current_instance = p.price;
        }
        else{
            break;
        }
    }
    return high_current_instance;
}
double MerkelMain :: getHighFromFilterProductsBid(std::vector<OrderBookEntry> entries, std::string product,
                                                  std::string timestamp,OrderBookType type){
    double high_current_instance = orderBook->getLowPrice(entries);
    for (OrderBookEntry &p : entries)
    {
        if ((p.product == product) && (p.timestamp == timestamp) && (type == OrderBookType::bid)) {
            if( high_current_instance < p.price)
                high_current_instance = p.price;
        }
        else{
            break;
        }
    }
    return high_current_instance;
}
void MerkelMain :: printFilterProducts(std::vector<OrderBookEntry> entries){

    std::cout << "Time Stamp\t\t\t Product\t Type\t Price\t\t Amount" << std::endl;
    for (OrderBookEntry &p : entries)
    {
        std::cout <<p.timestamp<<"\t"<<p.product<<"\t\t"<<"ASK"<<"\t"<<p.price<<"\t"<<p.amount << std::endl;
    }
    std::cout<<std::endl<<std::endl;
    std::cout<<"Open : "<<getOpenFromFilterProducts(entries)<<std::endl;
    std::cout<<"Close : "<<getCloseFromFilterProducts(entries)<<std::endl;
    /*std::cout<<"High : "<<getHighFromFilterProducts(entries)<<std::endl;
    std::cout<<"Low : "<<getLowFromFilterProducts(entries)<<std::endl;*/
}

void MerkelMain::printMarketStats()
{

  for (std::string const &p : orderBook->getKnownProducts())
  {
    std::cout << "Product: " << p << std::endl;
    std::vector<OrderBookEntry> entries = orderBook->getOrders(OrderBookType::ask,
                                                              p, currentTime);
    std::cout << "Asks seen: " << entries.size() << std::endl;
    std::cout << "Max ask: " << orderBook->getHighPrice(entries) << std::endl;
    std::cout << "Min ask: " << orderBook->getLowPrice(entries) << std::endl;
  }
};

std::vector<OrderBookEntry>  MerkelMain::getProductFilter(const std::string& product_name, const std::string& time_stamp, const std::string& order_type)
{
    std::vector<OrderBookEntry> entries;
    if(order_type=="ASK"){
        entries =  orderBook->getOrders(OrderBookType::ask,product_name,time_stamp);
    }else{
        entries =  orderBook->getOrders(OrderBookType::bid,product_name,time_stamp);
    }
    printFilterProducts(entries);
    return entries;
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


// Function to split the CSV file based on unique values
void MerkelMain::splitTimeStampByUniqueValues(std::vector<OrderBookEntry> entries ) {

    int i = 1;
    //std::unordered_set<std::string> uniqueValues;
    for (OrderBookEntry &p : entries){
        std::string tokens = p.timestamp;
        uniqueTimeStampValues.insert(std::pair<std::string,int>(tokens,i++));
    }
}
void MerkelMain::splitProductsByUniqueValues(std::vector<OrderBookEntry> entries ) {

    //std::unordered_set<std::string> uniqueValues;
    int i = 1;
    for (OrderBookEntry &p : entries)
    {
        //std::cout <<p.timestamp<<"\t"<<p.product<<"\t\t"<<"ASK"<<"\t"<<p.price<<"\t"<<p.amount << std::endl;
        std::string tokens = p.product;
        uniqueProductValues.insert(std::pair<std::string,int>(tokens,i++));
    }
}