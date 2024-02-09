#include "myDataStore.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include "util.h"

void myDataStore::addProduct(Product* p){
    if(productset.find(p)!=productset.end()){return;}
    std::set<std::string> current = p->keywords();

    std::set<std::string>::iterator it;
    for(it = current.begin(); it != current.end(); ++it){
      if(pmap.find(*it) == pmap.end()){
        std::set<Product*> currProdSet;
        currProdSet.insert(p);
        pmap.insert(std::make_pair(*it, currProdSet));
      } else {
        pmap[*it].insert(p);
      }
    }
    productset.insert(p);
}
    
void myDataStore::addUser(User* u) {
  if(userset.find(u)!=userset.end()){return;}
    std::queue<Product*> userq;
    umap[convToLower(u->getName())] = userq; 
    usermap[convToLower(u->getName())] = u;
    userset.insert(u);
}

std::vector<Product*> myDataStore::search(std::vector<std::string>& terms, int type){
    if (type == 0) {
      std::set<Product*> pset;
      std::vector<Product*> endset;

      for (std::vector<std::string>::iterator i = terms.begin(); i != terms.end(); ++i) {
          if (pmap.find(*i) != pmap.end()) {
              // Initialize pset with the first set of products
              if (pset.empty()) {
                  pset = pmap[*i];
              } else {
                  // Intersect pset with the set of products for the current term
                  std::set<Product*> intersection;
                  std::set_intersection(pset.begin(), pset.end(), pmap[*i].begin(), pmap[*i].end(),
                                        std::inserter(intersection, intersection.begin()));
                  pset = intersection;
              }
          }
      }
      // Now pset contains the intersection of products for all terms
      // Add them to endset
      for (std::set<Product*>::iterator it = pset.begin(); it != pset.end(); ++it) {
          endset.push_back(*it);
      }

      return endset;
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
  std::set<Product*>::iterator it1;
  for(it1 = productset.begin(); it1 != productset.end(); ++it1){
    (*it1)->dump(ofile);
  }
  ofile << "</products>" << std::endl;
  ofile << "<users>" << std::endl;
  std::set<User*>::iterator it2;
  for(it2 = userset.begin(); it2 != userset.end(); ++it2){
    (*it2)->dump(ofile);
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
    while (!p.empty()) {
        std::cout << p.front()->displayString();
        p.pop();
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

myDataStore::~myDataStore() {
    for (std::set<Product*>::iterator it = productset.begin(); it != productset.end(); ++it) {
        delete *it;
    }

    for (std::set<User*>::iterator it = userset.begin(); it != userset.end(); ++it) {
        delete *it;
    }
}