#ifndef ORDER_H
#define ORDER_H

#include <string>

struct Order {
    std::string ClientOderID;
    std::string Instrument;
    int Side;
    double Price;
    int Quantity;
};

#endif // ORDER_H
