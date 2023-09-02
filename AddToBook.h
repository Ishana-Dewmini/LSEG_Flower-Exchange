#ifndef ADDTOBOOK_H
#define ADDTOBOOK_H

#include "Book.h"
#include <vector>
using namespace std;

void AddToBook(vector<Book>& BookToAdd, Book flower){
    // Function to add order to the relevant side of the book in the relevant order according to the price
    int n = BookToAdd.size();
    if (n == 0) {
        BookToAdd.push_back(flower);
    } else {
        int left = 0;
        int right = n - 1;
        int insertionPoint = n; // Initialize to n in case the element is greater than all existing elements
        int mid = left + (right - left) / 2;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (BookToAdd[mid].Price >= flower.Price) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        insertionPoint = mid;
        BookToAdd.insert(BookToAdd.begin() + insertionPoint, flower);

    }
}

#endif // ADDTOBOOK_H