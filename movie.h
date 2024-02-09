#include "product.h"
#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include "util.h"

class Movie :public Product {
public:
    std::string genre;
    std::string rating;
    Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating);
    virtual std::set<std::string> keywords() const;
    virtual std::string displayString() const;
    virtual void dump(std::ostream& os) const;
};
#endif