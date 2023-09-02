#ifndef OUTPUT_H
#define OUTPUT_H

#include <vector>
#include <string>
#include <iomanip>
#include "ExecutionReport.h"

using namespace std;

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
             << std::fixed << std::setprecision(2) << report.Price << ","
             << report.Reason << ","
             << report.TransactionTime << std::endl;
    }

    file.close();
    
}

#endif // !OUTPUT_H