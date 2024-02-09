#include "book.h"
#include <iostream>
#include <string>
#include <sstream>
#include "util.h"

Book::Book(const std::string category, const std::string name, double price, int qty, std::string ISBN, std::string author)
    :Product(category, name, price, qty), ISBN(ISBN), author(author){}

std::set<std::string> Book::keywords() const{
    std::set<std::string> a = parseStringToWords(author);
    std::set<std::string> n = parseStringToWords(name_);
    a.insert(n.begin(), n.end());
    a.insert(ISBN);
    return a;
}

std::string Book::displayString() const{
    std::string s = name_ + "\n" + "Author: " + author + " ISBN: " + ISBN + "\n" 
    + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    
    return s; 
}

void Book::dump(std::ostream& os) const{
    std::cout << category_ << std::endl << name_ << std::endl << 
    price_ << std::endl << qty_ << std::endl << ISBN << std::endl << author << std::endl;
}

