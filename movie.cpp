#include "movie.h"
#include <iostream>
#include <string>
#include <sstream>
#include "util.h"

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating)
    : Product(category, name, price, qty), genre(genre), rating(rating) {}

std::set<std::string> Movie::keywords() const{
    std::set<std::string> keyMovie;
    std::set<std::string> a = parseStringToWords(genre);
    std::set<std::string> n = parseStringToWords(name_);
    keyMovie = setUnion(n, a);
    return keyMovie;
}

std::string Movie::displayString() const {
    return name_ + "\n"
         + "Genre: " + genre + " Rating: " + rating + "\n"
         + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Movie::dump(std::ostream& os) const{
    os << category_ << std::endl << name_ << std::endl << 
    price_ << std::endl << qty_ << std::endl << genre << std::endl << rating << std::endl;
}
