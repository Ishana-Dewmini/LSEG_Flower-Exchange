#ifndef MAKEBOOK_H
#define MAKEBOOK_H

#include "Order.h"
#include "Book.h"
#include "AddToBook.h"
#include <vector>
#include <string>
#include "ExecutionReport.h"
#include "getCurrentTransactionTime.h"
using namespace std;

void MakeBook(int side, ExecutionReport& report, vector<ExecutionReport>& reports, Book flower, vector<Book>& SideToAdd, vector<Book>& OtherSide){
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

    
                
}

#endif // MAKEBOOK_H