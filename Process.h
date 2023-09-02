#ifndef PROCESS_H
#define PROCESS_H

#include "Order.h"
#include "ExecutionReport.h"
#include "Book.h"
#include "MakeBook.h"
#include "AddToBook.h"
#include "getCurrentTransactionTime.h"
#include <vector>
#include <string>
using namespace std;

vector<Book> RoseSell;
vector<Book> LavenderSell;
vector<Book> LotusSell;
vector<Book> TulipSell;
vector<Book> OrchidSell;

vector<Book> RoseBuy;
vector<Book> LavenderBuy;
vector<Book> LotusBuy;
vector<Book> TulipBuy;
vector<Book> OrchidBuy;
    

void Process(vector<Order>& orders, vector<ExecutionReport>& reports) {
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
}

#endif // PROCESS_H