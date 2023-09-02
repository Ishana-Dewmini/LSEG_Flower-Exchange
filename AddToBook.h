#ifndef ADDTOBOOK_H
#define ADDTOBOOK_H

#include "Book.h"
#include <vector>
using namespace std;

void AddToBook(vector<Book>& BookToAdd, Book flower){
    // Function to add order to the relevent side of the book in relevent order according to the price
    int n = BookToAdd.size();
    if (n==0){
        BookToAdd.push_back(flower);
    }
    else{
        BookToAdd.push_back(flower);
        for (int j=n-1;j>=0;j--){
            if (BookToAdd[j].Price>=flower.Price){
                BookToAdd[j+1]=flower;
            }else{
                BookToAdd[j+1]=BookToAdd[j];
                if (j==0){
                    BookToAdd[j]=flower;
                }
            }
        }
    }
 
}

#endif // ADDTOBOOK_H