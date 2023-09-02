#ifndef ORDER_H
#define ORDER_H

#include <string>

// Order structure
struct Order {
    std::string ClientOderID;
    std::string Instrument;
    int Side;
    double Price;
    int Quantity;
};

#endif // ORDER_H
