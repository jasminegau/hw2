#include "datastore.h"
#ifndef myDataStore_H
#define myDataStore_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <queue>

class myDataStore :public DataStore {
public:
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    std::set<Product*> productset;
    std::set<User*> userset;
    std::map<std::string, User*> usermap;
    std::map<std::string, std::set<Product*>> pmap;
    std::map<std::string, std::queue<Product*>> umap;
    void addCart(std::string s, Product* p);
    bool userIncluded(std::string s);
    void viewCart(std::string s);
    void buyCart(std::string s);
    ~myDataStore();
};
#endif