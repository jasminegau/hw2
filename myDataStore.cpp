#include "myDataStore.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include "util.h"

void myDataStore::addProduct(Product* p) {
    std::set<std::string>::iterator it;
    for (it = p->keywords().begin(); it != p->keywords().end(); ++it) {
        if (pmap.find(*it) == pmap.end()) {
            std::set<Product*> kset;
            kset.insert(p);
            pmap[(*it)] = kset;
        } else {
            pmap[(*it)].insert(p);
        }
    }
    productset.insert(p);
}
    
void myDataStore::addUser(User* u) {
    std::queue<Product*> userq;
    umap[convToLower(u->getName())] = userq; 
    usermap[convToLower(u->getName())] = u;
}

std::vector<Product*> myDataStore::search(std::vector<std::string>& terms, int type){
    if(type == 0){
        std::set<Product*> pset;
        std::vector<Product*> endset;
        if(pmap.find(terms[0]) != pmap.end()){
            pset = pmap[terms[0]];
            for(std::set<Product*>::iterator it = pset.begin(); it != pset.end(); ++it) {
                bool check = true;
                for (std::vector<std::string>::iterator i = terms.begin(); i != terms.end(); ++i) {
                    if ((*it)->keywords().find(*i) == (*it)->keywords().end())
                        check = false;
                }
                if(check){
                    endset.push_back(*it);
                }
            }
            return endset;
        } else {
            std::vector<Product*> endset;
            return endset;
        }
    } else if (type == 1){
        std::vector<Product*> pset;
        for(std::vector<std::string>::iterator i = terms.begin(); i != terms.end(); ++i) {
            if(pmap.find(*i) != pmap.end()){
                for(std::set<Product*>::iterator it = pmap[(*i)].begin(); it != pmap[(*i)].end(); ++it){
                    pset.push_back(*it);
                }
            }
        }
        return pset;
    }
    std::vector<Product*> endset;
    return endset;
}

void myDataStore::dump(std::ostream& ofile){
    ofile << "<products>" << std::endl;
    for (std::set<Product*>::iterator it = productset.begin(); it != productset.end(); ++it) {
        (*it)->dump(ofile);
    }
    ofile << "</products>" << std::endl;
    ofile << "<users>" << std::endl;
    for (std::map<std::string, User*>::iterator it = usermap.begin(); it != usermap.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

void myDataStore::addCart(std::string s, Product* p) {
    if (umap.find(s) != umap.end()) {
        umap[s].push(p);
    }
}

bool myDataStore::userIncluded(std::string s) {
    return umap.find(s) != umap.end();
}

void myDataStore::viewCart(std::string s) {
    if (umap.find(s) == umap.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    std::queue<Product*> p = umap[s];
    int count = 1;
    while (!p.empty()) {
        std::cout << count << ": " << p.front() << std::endl;
        p.pop();
        count++;
    }
}

void myDataStore::buyCart(std::string s) {
    if (usermap.find(s) != usermap.end()) {
        User* u = usermap[s];
        std::queue<Product*> newq;
        while (!umap[s].empty()) {
            double amt = umap[s].front()->getPrice();
            if (umap[s].front()->getQty() >= 1 && u->getBalance() >= amt) {
                u->deductAmount(amt);
                umap[s].front()->subtractQty(1);
                if(umap[s].front()->getQty()==0){
                  delete umap[s].front();
                }
                umap[s].pop();
            } else {
                newq.push(umap[s].front());
                umap[s].pop();
            }
        }
        umap[s] = newq;
    } else {
        std::cout << "Invalid username" << std::endl;
    }
}