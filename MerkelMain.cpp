#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <set>
#include <unordered_map>
#include <algorithm>
#define stringify( name ) #name;

std::vector<std::pair<OrderBookEntry,std::string>> vectorUniqueProduct[5];

bool MerkelMain::comp(std::pair<std::string ,int> &a,
                      std::pair<std::string ,int> &b)
{
    return (a.first < b.first);
}
bool MerkelMain::comp_orderBookEntry(std::pair<int, OrderBookEntry> &a,
                      std::pair<int, OrderBookEntry> &b)
{
    return (a.second.timestamp < b.second.timestamp);
}

void MerkelMain::sort_map(std::unordered_map<std::string , int> unorderedMap) {

    sortedDataTimeStamps = new std::vector<std::pair<std::string ,int>>(unorderedMap.begin(), unorderedMap.end());
    std::sort(sortedDataTimeStamps->begin(), sortedDataTimeStamps->end(), comp);
}
void MerkelMain::sort_map_orderBookEntry(std::unordered_map<int, OrderBookEntry> unorderedMap) {

    sortedDataOderBookEntry = new std::vector<std::pair<int, OrderBookEntry>>(unorderedMap.begin(), unorderedMap.end());
    std::sort(sortedDataOderBookEntry->begin(), sortedDataOderBookEntry->end(), comp_orderBookEntry);
}

void MerkelMain::initCandleStick(){
    for (int i = 0; i < sizeTimeStamps; i++){
        candlestick[i] = new Candlestick();
        std::cout<<*candlestick[i]<<std::endl;
    }
}
MerkelMain::MerkelMain()
{
    std::cout<<"MerkelMain -- Default Constructor "<<std::endl;

    orderBook = new OrderBook("E:\\c-workspace\\currency_exchange\\ETH_BTC.csv");
    entries = orderBook->getAllOrders();
    splitTimeStampByUniqueValues();
    splitProductsByUniqueValues();
    sizeProducts = uniqueProductValues.size();
    sizeTimeStamps = uniqueTimeStampValues.size();


    std::cout<<"Unique Time Stamps : "<<sizeTimeStamps<<std::endl;
    //searchObject = new SearchObject* [sizeTimeStamps];
    //searchObjectTimeStamp = new SearchObjectTimeStamp * [sizeTimeStamps];

    candlestick = new Candlestick * [sizeTimeStamps];
    initCandleStick();
    std::cout<<"Unique Products  : "<<sizeProducts<<std::endl;
    std::string sample;
    sort_map(uniqueTimeStampValues);
    sort_map_orderBookEntry(uniqueOrderBookEntry);

    int objectIndex =0;
    int count =1;
    std::string type;
    int index;
    int indexPrevious;
    std::string strCurrentTimeStamp;
    std::string strPreviousTimeStamp;
    for (const auto& i : *(sortedDataTimeStamps)) {

        std::cout <<count++<<".  "<< i.first << "    " << i.second<<"    "<<std::endl;
        index = getCurrentTimeStampIndex(i.first);
        indexPrevious = getPreviousTimeStampIndex(i.first);
        strCurrentTimeStamp = getCurrentTimeStamp(i.first);
        strPreviousTimeStamp = getPreviousTimeStamp(i.first);
        SearchObjectTimeStamp *sTimeStamp = new SearchObjectTimeStamp(strCurrentTimeStamp,strPreviousTimeStamp,
                                                                       index,indexPrevious);
        searchObjectTimeStamp.push_back(*sTimeStamp);

        std::cout<<"Time Stamp  "<< i.first<<", index : "<<index<<", Previous Index : "<<indexPrevious
                 <<", Current Time Stamp : "<<strCurrentTimeStamp<<",  Previous Time Stamp : "<<strPreviousTimeStamp<<std::endl;
        objectIndex++;
    }


    objectIndex =0;
    count =1;
    index = 0;
    indexPrevious = 0;
    strCurrentTimeStamp = "";
    strPreviousTimeStamp = "";
    for (const auto& i : *(sortedDataOderBookEntry)) {
        if(i.second.orderType == OrderBookType::ask){
            type = "ask";
        }
        else{
            type = "bid";
        }

        std::cout <<count++<<".  "<< i.second.timestamp << "    " << i.second.product<<"    "<< type<< std::endl;
        index = getCurrentTimeStampIndex(i.second.timestamp);
        indexPrevious = getPreviousTimeStampIndex(i.second.timestamp);
        strCurrentTimeStamp = getCurrentTimeStamp(i.second.timestamp);
        strPreviousTimeStamp = getPreviousTimeStamp(i.second.timestamp);
        SearchObject *searchTimeStamp = new SearchObject(index,indexPrevious,
                                                       strCurrentTimeStamp,strPreviousTimeStamp,i.second.product,type);
        searchObject.push_back(*searchTimeStamp);
        std::cout<<"Time Stamp  "<< i.second.timestamp<<", index : "<<index<<", Previous Index : "<<indexPrevious
        <<", Current Time Stamp : "<<strCurrentTimeStamp<<",  Previous Time Stamp : "<<strPreviousTimeStamp<<std::endl;
        objectIndex++;
    }

    createCandelStick();
    Candlestick candlestick2;
    for (int j = 0; j < sizeTimeStamps; j++) {
        //std::cout<<*(candlestick[j]);
        candlestick2 = candleStickAsk[j];
        std::cout<<candlestick2;
        //candlestick2 = candleStickBid[j];
       // std::cout<<candlestick2;
    }

}

void MerkelMain::createCandelStick(){

    std::string product;
    int z = 0;
    for (auto const& element : uniqueProductValues){
        vectorProducts.push_back(element.first);  // Write to file or whatever you want to do
    }
    int i = 0;
    while (i < sizeProducts) {
        product = vectorProducts[i];
        double open = 0, close = 0, low = 0, high =0;
        int j = 0;
        while (j < sortedDataTimeStamps->size()) {
            int searchIndex = searchObjectTimeStamp[j].getCurrentTimeStampIndex();

            std::cout<<"Search Index "<<searchIndex<<std::endl;

            if(searchObject[searchIndex].getType().compare("ask") == 0) {
                open = getAverageFromFilterProductAsk(searchObjectTimeStamp[j].getStrPreviousTimeStamp(),
                                                             product, OrderBookType::ask);
                close = getAverageFromFilterProductAsk(searchObjectTimeStamp[j].getStrCurrentTimeStamp(),
                                                              product, OrderBookType::ask);
                low = getLowFromFilterProductsAsk(entries, product,searchObjectTimeStamp[j].getStrCurrentTimeStamp(),
                                                         OrderBookType::ask);
                high = getHighFromFilterProductsAsk(entries, product,searchObjectTimeStamp[j].getStrCurrentTimeStamp(),
                                                           OrderBookType::ask);

                Candlestick candlestick1(open, high, low, close, OrderBookType::ask, product);
                candlestick[j]->setType(OrderBookType::ask);
                candleStickAsk.push_back(candlestick1);
            }

            else  if(searchObject[searchIndex].getType().compare("bid") == 0) {
                open = getAverageFromFilterProductAsk(searchObjectTimeStamp[j].getStrPreviousTimeStamp(),
                                                             product, OrderBookType::bid);
                close = getAverageFromFilterProductAsk(searchObjectTimeStamp[j].getStrCurrentTimeStamp(),
                                                              product, OrderBookType::bid);
                low = getLowFromFilterProductsAsk(entries, product,searchObjectTimeStamp[j].getStrCurrentTimeStamp(),
                                                         OrderBookType::bid);
                high = getHighFromFilterProductsAsk(entries, product,searchObjectTimeStamp[j].getStrCurrentTimeStamp(),
                                                           OrderBookType::bid);
                Candlestick candlestick1(open, high, low, close, OrderBookType::bid, product);
                candlestick[j]->setType(OrderBookType::bid);
                candleStickBid.push_back(candlestick1);
            }

          /*  candlestick[j]->setClose(close);
            candlestick[j]->setHigh(high);
            candlestick[j]->setLow(low);
            candlestick[j]->setOpen(open);
            candlestick[j]->setProduct(product);*/
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

  std::cout << "7: Draw Candle Chart ETH/BTC " << std::endl;

  std::cout << "============== " << std::endl;
  std::cout << "Type in 1-7" << std::endl;

  std::cout << "Current time is " << currentTime << std::endl;
}


void MerkelMain::drawCandlestickChart(const std::vector<Candlestick>& data) {

    const int chartWidth = 12;
    const int chartHeight = 11;
    graph = new std::string *[chartWidth];
    for (int i = 0; i < chartWidth; ++i) {
        graph[i] = new std::string [chartHeight];
    }

    graph[0][0] =   {"Time Frame"};
    graph[0][1] =   {"11:58:05"};
    graph[0][2] =   {"11:58:10"};
    graph[0][3] =   {"11:58:05"};
    graph[0][4] =   {"11:58:00"};
    graph[0][5] =   {"11:57:55"};
    graph[0][6] =   {"11:57:50"};
    graph[0][7] =   {"11:57:45"};
    graph[0][8] =   {"11:57:40"};
    graph[0][9] =   {"11:57:35"};
    graph[0][10] =  {"11:57:30"};


    graph[1][0] =   {"0.02526501"};
    graph[2][0] =   {"0.02526211"};
    graph[3][0] =   {"0.02494611"};
    graph[4][0] =   {"0.02483911"};
    graph[5][0] =   {"0.02483711"};
    graph[6][0] =   {"0.02483451"};
    graph[7][0] =   {"0.02483202"};
    graph[8][0] =   {"0.02483011"};
    graph[9][0] =   {"0.02482812"};
    graph[10][0] =   {"0.02482611"};
    graph[11][0] =   {"Price"};


    // Find the highest and lowest values in the data
        double minValue = data[0].getLow();
        double maxValue = data[0].getHigh();
        for (const auto &candle: data) {
            if (candle.getLow() < minValue) {
                minValue = candle.getLow();
            }
            if (candle.getHigh() > maxValue) {
                maxValue = candle.getHigh();
            }
        }

        // Calculate the scaling factors
        double valueRange = maxValue - minValue;
        double verticalScale = chartHeight / valueRange;
        double horizontalScale = chartWidth / static_cast<double>(candleStickAsk.size());

        // Draw the chart
        for (int y = chartHeight - 1; y >= 1; --y) {
            for (std::size_t x = 1; x < candleStickAsk.size(); ++x) {
                double currentValue = candleStickAsk[x].getClose();

                // Check if the current pixel is within the candlestick range
                if (currentValue >= minValue + (y / verticalScale) &&
                    currentValue <= minValue + ((y + 1) / verticalScale)) {
                    graph[x][y] = "||";
                    //std::cout << "█"; // ASCII block character
                } else {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }

    for (int i = 0; i < chartWidth; ++i) {
        for (int j = 0; j < chartHeight; ++j) {
            std::cout<<graph[i][j]<<"  ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl<<std::endl;
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

double MerkelMain::getAverageFromFilterProductAsk(std::string timestamp,
                                               std::string product,enum OrderBookType type){
    double total_price = 0;
    double total_amount = 0;
    double open_current_instance = 0;
    int i=0;

     //std::vector<OrderBookEntry> test = vectorUniqueProduct.first[i];
    for (OrderBookEntry &p : entries)
    {
        if ((p.product == product) && (p.timestamp == timestamp) && (type == OrderBookType::ask)) {
                total_price += p.price * p.amount;
                total_amount += p.amount;
        }
    }
    open_current_instance = total_price /total_amount;
    return open_current_instance;
}

double MerkelMain::getAverageFromFilterProductBid(std::string timestamp, std::string product,
                                      enum OrderBookType type)
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
    }
    return low_current_instance;
}

double MerkelMain :: getLowFromFilterProductsBid(std::vector<OrderBookEntry> entries, std::string product,
                                              std::string timestamp,OrderBookType type){
    double low_current_instance = orderBook->getLowPrice(entries);
    for (OrderBookEntry &p : entries)
    {
        if ((p.product == product) && (p.timestamp == timestamp) && (type == OrderBookType::bid)) {
            if( low_current_instance < p.price)
                low_current_instance = p.price;
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
std::vector<OrderBookEntry>  MerkelMain::getProductWiseFilter(const std::string& product_name)
{
    std::vector<OrderBookEntry> entries;
    entries =  orderBook->getOrders(product_name);
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
      drawCandlestickChart(candleStickAsk);
      //getProductFilter("ETH/BTC","2020/06/01 11:57:30.328127","ASK");
  }
}


// Function to split the CSV file based on unique values
void MerkelMain::splitTimeStampByUniqueValues() {

    int i = 1;
    //std::unordered_set<std::string> uniqueValues;
    for (OrderBookEntry &p : entries){
        std::string tokens = p.timestamp;
        uniqueTimeStampValues.insert(std::make_pair(tokens,i++));
    }
    i = 1;
    for (OrderBookEntry &p : entries){
        uniqueOrderBookEntry.insert(std::make_pair(i++,p));
    }
    std::cout<<"Exiting Time Stamp Unique Values "<<std::endl;
}
void MerkelMain::splitProductsByUniqueValues() {

    //std::unordered_set<std::string> uniqueValues;
    int i = 1;
    for (OrderBookEntry &p : entries)
    {
        //std::cout <<p.timestamp<<"\t"<<p.product<<"\t\t"<<"ASK"<<"\t"<<p.price<<"\t"<<p.amount << std::endl;
        std::string tokens = p.product;
        uniqueProductValues.insert(std::pair<std::string,int>(tokens,i++));
    }
    std::cout<<"Exiting Products Unique Values "<<std::endl;
}

int MerkelMain::getCurrentTimeStampIndex(std::string timeStamp){
    int count =1;
    int index = 0;
    for (const auto& i : *(sortedDataTimeStamps)) {
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
    for (const auto& i : *(sortedDataTimeStamps)) {
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
    for (const auto& i : *(sortedDataTimeStamps)) {
        index = i.second;
        strCurrentTimeStamp = i.first;
        if(timeStamp == strCurrentTimeStamp)
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
    for (const auto& i : *(sortedDataTimeStamps)) {
        prevIndex = index;
        index = i.second;
        strPreviousTimeStamp = strCurrentTimeStamp;
        strCurrentTimeStamp = i.first;
        if(timeStamp == strCurrentTimeStamp)
            break;
        count++;
    }
    return strPreviousTimeStamp;
}
