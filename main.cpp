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
    // Read orders from Trader Application's CSV file
    string inputFilename = "trader_orders.csv";
    vector<Order> orders = ReadOder(inputFilename);
    // Process and execute orders to generate Execution Reports
    vector<ExecutionReport> reports;
    Process(orders, reports);
    // Write Execution Reports to the output CSV file
    string outputFilename = "execution_reports.csv";
    Output(reports, outputFilename);

    return 0;
    
}