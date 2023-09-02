#ifndef ADDTOBOOK_H
#define ADDTOBOOK_H

#include "Book.h"
#include <vector>
using namespace std;

void AddToBook(vector<Book>& BookToAdd, Book flower){
    // Function to add order to the relevant side of the book in the relevant order according to the price
    int n = BookToAdd.size();
    if (n == 0) {
        // If the relevent side of the book is empty, just add the order
        BookToAdd.push_back(flower);
    } else {
        // If the relevant side of the book is not empty, find the correct position to insert the order using Binary Search
        int left = 0;
        int right = n - 1;
        int insertionPoint = n; 
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