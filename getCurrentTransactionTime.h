#ifndef GETCURRENTTRANSACTIONTIME_H
#define GETCURRENTTRANSACTIONTIME_H

#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;

string getCurrentTransactionTime() {
    // Function to get current time in the format of YYYYMMDD-HHMMSS.mmm
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    auto milliseconds = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()) % 1000;

    ostringstream oss;
    oss << put_time(std::localtime(&time), "%Y%m%d-%H%M%S") << "." << setfill('0') << setw(3) << milliseconds.count();
    return oss.str();
}

#endif // GETCURRENTTRANSACTIONTIME_H