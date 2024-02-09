#include "clothing.h"
#include <iostream>
#include <string>
#include <sstream>
#include "util.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand)
    : Product(category, name, price, qty), size(size), brand(brand) {}

std::set<std::string> Clothing::keywords() const{
    std::set<std::string> a = parseStringToWords(brand);
    std::set<std::string> n = parseStringToWords(name_);
    a.insert(n.begin(), n.end());
    return a;
}

std::string Clothing::displayString() const{
    std::string s = name_ + "/n" + "Size: " + size + " Brand: " + brand + "/n" 
    + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return s;
}

void Clothing::dump(std::ostream& os) const{
    std::cout << category_ << std::endl << name_ << std::endl << 
    price_ << std::endl << qty_ << std::endl << size << std::endl << brand << std::endl;
}
