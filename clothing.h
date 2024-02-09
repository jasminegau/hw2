#include "product.h"
#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include "util.h"

class Clothing :public Product {
public:
    std::string size;
    std::string brand;
    Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand);
    virtual std::set<std::string> keywords() const;
    virtual std::string displayString() const;
    virtual void dump(std::ostream& os) const;
};
#endif
