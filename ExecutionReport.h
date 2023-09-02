#ifndef EXECUTIONREPORT_H
#define EXECUTIONREPORT_H

#include <string>

// Execution Report structure
struct ExecutionReport {
    std::string ClientOderID;
    std::string OderID;
    std::string Instrument;
    int Side;
    double Price;
    int Quantity;
    int Status;
    std::string Reason;
    std::string TransactionTime;
};

#endif // EXECUTIONREPORT_H
