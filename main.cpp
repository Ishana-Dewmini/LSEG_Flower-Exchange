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
#include "ReadOder.h"
#include "Output.h"
using namespace std;

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