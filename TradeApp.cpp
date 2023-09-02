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
#include "ExchangeApp.h"
#include "ReadOrder.h"
#include "Output.h"
using namespace std;

int main() {
    // Read orders from Trader Application's CSV file
    string inputFilename;
    cout << "Enter the input filename: ";
    cin >> inputFilename;
    inputFilename += ".csv";
    // Ensure that the rest of the input stream is empty
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    vector<Order> orders = ReadOrder(inputFilename);
    // Process and execute orders to generate Execution Reports
    vector<ExecutionReport> reports;
    ExchangeApp(orders, reports);
    // Write Execution Reports to the output CSV file
    string outputFilename = "execution_reports.csv";
    Output(reports, outputFilename);

    return 0;
    
}