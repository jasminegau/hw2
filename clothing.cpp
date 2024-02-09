#include "clothing.h"
#include <iostream>
#include <string>
#include <sstream>
#include "util.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string size, std::string brand)
    : Product(category, name, price, qty), size(size), brand(brand) {}

std::set<std::string> Clothing::keywords() const{
    std::set<std::string> keyClothing;
    std::set<std::string> a = parseStringToWords(brand);
    std::set<std::string> n = parseStringToWords(name_);
    keyClothing = setUnion(n, a);
    return keyClothing;
}

std::string Clothing::displayString() const {
    return name_ + "\n"
         + "Size: " + size + " Brand: " + brand + "\n"
         + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Clothing::dump(std::ostream& os) const{
    os << category_ << std::endl << name_ << std::endl << 
    price_ << std::endl << qty_ << std::endl << size << std::endl << brand << std::endl;
}
