#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "Order.h"
#include "ExecutionReport.h"
#include "Book.h"
#include "MakeBook.h"
#include "AddToBook.h"
#include "getCurrentTransactionTime.h"
#include "Process.h"
using namespace std;

/*vector<Book> RoseSell;
vector<Book> LavenderSell;
vector<Book> LotusSell;
vector<Book> TulipSell;
vector<Book> OrchidSell;

vector<Book> RoseBuy;
vector<Book> LavenderBuy;
vector<Book> LotusBuy;
vector<Book> TulipBuy;
vector<Book> OrchidBuy;*/
    
/*string getCurrentTransactionTime() {
    // Function to get current time in the format of YYYYMMDD-HHMMSS.mmm
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    auto milliseconds = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()) % 1000;

    ostringstream oss;
    oss << put_time(std::localtime(&time), "%Y%m%d-%H%M%S") << "." << setfill('0') << setw(3) << milliseconds.count();
    return oss.str();
}*/

/*void AddToBook(vector<Book>& BookToAdd, Book flower){
    // Function to add order to the relevent side of the book in relevent order according to the price
    int n = BookToAdd.size();
    if (n==0){
        BookToAdd.push_back(flower);
    }
    else{
        BookToAdd.push_back(flower);
        for (int j=n-1;j>=0;j--){
            if (BookToAdd[j].Price>=flower.Price){
                BookToAdd[j+1]=flower;
            }else{
                BookToAdd[j+1]=BookToAdd[j];
                if (j==0){
                    BookToAdd[j]=flower;
                }
            }
        }
    }
 
}
*/

/*void MakeBook(int side, ExecutionReport& report, vector<ExecutionReport>& reports, Book flower, vector<Book>& SideToAdd, vector<Book>& OtherSide){
    // Function to make book for each flower type

    if (OtherSide.size() == 0){
        // If the other side is empty, add the order to the book directly
        AddToBook(SideToAdd,flower);
        report.Status = 0; //New
        report.Quantity = flower.Quantity;
        report.Price = flower.Price;
        report.TransactionTime = getCurrentTransactionTime();
        reports.push_back(report);
    }else {
        // If the other side is not empty, check whether the order can be filled
        bool filled=false;
        int limit = OtherSide.size();
        int j =0;
        while (j<limit){
            if ((OtherSide[j].Price<=flower.Price && side==1) || (OtherSide[j].Price>=flower.Price && side==2) ){
                // If the order can be filled, add the order to the book and generate execution reports
                filled = true;
                if (OtherSide[j].Quantity>=flower.Quantity){
                    // If the order can be completly filled, generate execution reports without adding to the book
                    report.Price = OtherSide[j].Price;
                    report.Quantity = flower.Quantity;
                    report.Status = 2; //fill
                    report.TransactionTime = getCurrentTransactionTime();
                    reports.push_back(report);
                    ExecutionReport updated;
                    for (int k=reports.size()-1;k>=0;k--){
                        if (reports[k].OderID == OtherSide[j].OderID){
                            updated = reports[k];
                            break;
                        }
                    }

                    // update the status of the filled or partially filled order in the book           
                    updated.Status = (OtherSide[j].Quantity=flower.Quantity) ? 2 : 3;
                    int temp = OtherSide[j].Quantity;
                    updated.Quantity = flower.Quantity ;
                    updated.Price = OtherSide[j].Price;
                    report.TransactionTime = getCurrentTransactionTime();
                    reports.push_back(updated);
                    if (temp - flower.Quantity==0){
                        // If the order is completely filled, remove the order from the book
                        OtherSide.erase(OtherSide.begin() + j);
                    }else{
                        // If the order is partially filled, update the quantity of the order in the book
                        OtherSide[j].Quantity-=flower.Quantity;
                    }
                    break;
                }else{
                    // If the order is partially filled, calculate the remaining order to be entered to the book and generate execution reports
                    report.Price = OtherSide[j].Price;
                    report.Quantity = OtherSide[j].Quantity;
                    report.Status = 3; //partially filled
                    report.TransactionTime = getCurrentTransactionTime();
                    reports.push_back(report);
                    ExecutionReport updated;
                    for (int k=reports.size()-1;k>=0;k--){
                         if (reports[k].OderID == OtherSide[j].OderID){
                            updated = reports[k];
                            break;
                        }
                    };
                    // update the status of the completly filled  order in the book
                    updated.Status = 2;
                    updated.Quantity = OtherSide[j].Quantity;
                    report.TransactionTime = getCurrentTransactionTime();
                    reports.push_back(updated);
                    // update the quantity of the partially filled order
                    flower.Quantity-=OtherSide[j].Quantity;
                    OtherSide.erase(OtherSide.begin() + j);
                    limit-=1;   
                }
            }else{
                j++;
            }
        }
        if (filled==false){
            // If the order cannot be filled, add the order to the book directly
            report.Status = 0; //New
            report.Quantity = flower.Quantity;
            report.Price = flower.Price;
            report.TransactionTime = getCurrentTransactionTime();
            reports.push_back(report);
        }
        if (flower.Quantity>0){
            // If the order is partially filled, add the remaining order to the book directly
            AddToBook(SideToAdd,flower);
        }
                        
    }   

    
                
}*/

vector<Order> ReadOder(const string& filename) {
    // Function to read orders from CSV file
    std::ifstream file;
    file.open(filename);
   
    if( !file.is_open()) {
        cout << "File "<< filename <<" not found." << endl;
        exit(-1);
    }

    vector<Order> orders;
    // Skip the first line (header)
    string header;
    getline(file, header);
    
    // Read each line from the file and store in the vector of orders
    string line;
    while (getline(file, line)) {


        Order order;
        istringstream iss(line);
        string clientId, instrument, side, price, quantity;

        getline(iss, clientId, ',');
        getline(iss, instrument, ',');
        getline(iss, side, ',');
        getline(iss, quantity, ',');
        getline(iss, price, ',');
        

        order.ClientOderID = clientId;
        order.Instrument = instrument;
        order.Side = stoi(side);
        order.Price = stod(price);
        order.Quantity = stoi(quantity);
        orders.push_back(order);
    }
    
    file.close();
    return orders;
}

/*void Process(vector<Order>& orders, vector<ExecutionReport>& reports) {
    // Function to process and execute orders to generate Execution Reports

    int orderid = 0;
    int OrderSize = orders.size();
    for (int i = 0; i<OrderSize; i++){
        orderid++;
        ExecutionReport report;
        report.OderID = "ord"+to_string(orderid);
        report.ClientOderID = orders[i].ClientOderID;
        report.Instrument = orders[i].Instrument;
        report.Side = orders[i].Side;

        // Check for invalid orders

        // Check whether the Price > 0.0
        if (orders[i].Price<=0){
            report.Price = orders[i].Price;
            report.Quantity = orders[i].Quantity;
            report.Status = 1; //Reject
            report.Reason = "Invalid price";
            report.TransactionTime = getCurrentTransactionTime();
            reports.push_back(report);
        }
        
        // Check whether the Side is Buy(1) or Sell(2)
        else if (report.Side!=1 && report.Side!=2){
            report.Price = orders[i].Price;
            report.Quantity = orders[i].Quantity;
            report.Status = 1; //Reject
            report.Reason = "Invalid side";
            report.TransactionTime = getCurrentTransactionTime();
            reports.push_back(report);
        }
        
        // Check whether the Client Order ID is maximum 7 characters long
        else if (report.ClientOderID.size()>7){
            report.Price = orders[i].Price;
            report.Quantity = orders[i].Quantity;
            report.Status = 1; //Reject
            report.Reason = "Invalid ID";
            report.TransactionTime = getCurrentTransactionTime();
            reports.push_back(report);
        }
        
        // Check whether the Order size is a multiple of 10 and within 10 to 1000
        else if (orders[i].Quantity<0 || orders[i].Quantity>1000 || orders[i].Quantity%10!=0){
            report.Price = orders[i].Price;
            report.Quantity = orders[i].Quantity;
            report.Status = 1; //Reject
            report.Reason = "Invalid size";
            report.TransactionTime = getCurrentTransactionTime();
            reports.push_back(report);
        }
        
        else{
            // Execute valid orders
            Book flower;
            flower.OderID = report.OderID;
            flower.Price = orders[i].Price;
            flower.Quantity = orders[i].Quantity;
            
            string flowertype = report.Instrument;
            if (flowertype=="Rose"){
                if(report.Side==1){
                    MakeBook(1, report, reports, flower, RoseBuy, RoseSell);
                }else{
                    MakeBook(2, report, reports, flower, RoseSell, RoseBuy);
                }
                
            }else if (flowertype=="Lavender"){
                if(report.Side==1){
                    MakeBook(1, report, reports, flower, LavenderBuy, LavenderSell);
                }else{
                    MakeBook(2, report, reports, flower, LavenderSell, LavenderBuy);
                }
                
            }else if (flowertype=="Lotus"){
                if(report.Side==1){
                    MakeBook(1, report, reports, flower, LotusBuy, LotusSell);
                }else{
                    MakeBook(2, report, reports, flower, LotusSell, LotusBuy);
                }
            
            }else if (flowertype=="Tulip"){
                if(report.Side==1){
                    MakeBook(1, report, reports, flower, TulipBuy, TulipSell);
                }else{
                    MakeBook(2, report, reports, flower, TulipSell, TulipBuy);
                }
                
            }else if (flowertype=="Orchid"){
                if(report.Side==1){
                    MakeBook(1, report, reports, flower, OrchidBuy, OrchidSell);
                }else{
                    MakeBook(2, report, reports, flower, OrchidSell, OrchidBuy);
                }
                    
            }
            
            else{
                    // Check whether the flower tyoe is valid
                    report.Price = orders[i].Price;
                    report.Quantity = orders[i].Quantity;
                    report.Status = 1; //Reject
                    report.Reason = "Invalid instrument";
                    report.TransactionTime = getCurrentTransactionTime();
                    reports.push_back(report);
            }
        } 
        
    }
}*/

void Output(const vector<ExecutionReport>& reports, const string& filename) {
    // Function to write execution reports to CSV file
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file " << filename << std::endl;
        return;
    }

    // Write the CSV header (column names)
    file << "OrderID,ClientOrderID,Instrument,Side,Status,Quantity,Price,Reason,TransitionTime" << std::endl;

    
    // Write each ExecutionReport to the file as a new line in CSV format
    for (const auto& report : reports) {
        file << report.OderID << ","
             << report.ClientOderID << ","
             << report.Instrument << ","
             << report.Side << ","
             << report.Status << ","
             << report.Quantity << ","
             << report.Price << ","
             << report.Reason << ","
             << report.TransactionTime << std::endl;
    }

    file.close();
    
}

int main() {
    cout<<0;
    // Read orders from Trader Application's CSV file
    string inputFilename = "trader_orders.csv";
    cout<<1;
    vector<Order> orders = ReadOder(inputFilename);
    cout<<2;
    // Process and execute orders to generate Execution Reports
    vector<ExecutionReport> reports;
    cout<<3;
    Process(orders, reports);
    cout<<4;
    // Write Execution Reports to the output CSV file
    string outputFilename = "execution_reports.csv";
    cout<<5;
    Output(reports, outputFilename);

    return 0;
    

    
}