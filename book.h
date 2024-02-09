#include "product.h"
#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include "util.h"

class Book :public Product {
public:
    std::string ISBN;
    std::string author;
    Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author);
    virtual std::set<std::string> keywords() const;
    virtual std::string displayString() const;
    virtual void dump(std::ostream& os) const;
};
#endif
