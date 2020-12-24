//
//  source.hpp
//  Sahara
//
//  Created by Suneeth Torke on 12/22/20.
//

#ifndef source_hpp
#define source_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <random>

// length width and height are grabbed from hashing the tracking number
// the UPC will be LLLLBBBBHHHHWWWWPP..
// the tracking will be PPTTTTFFFFCC
// priority, to, from, product_code
class product {
public:
    size_t location;
    uint64_t hash;
    std::string name;
    double price;
    double weight, volume;
    double small, middle, large;

    product(const std::string name, const uint64_t hash, const size_t location);
  
    void info();
    //product (string name, double price, double length, double width, double height, double weight) :
    //length(length), width(width), height(height), weight(weight) {};
    
};

// holds the relevant to and from locations, UPC
struct location {
    size_t to;
    size_t from;
    location();
    location(size_t to, size_t from);
};


// holds the box packaging sizes
class package {
public:
    size_t tracking;
    size_t upc;
    size_t urgency;
    product product;
    location location;
    
    package (class product &product, class location &location);
    
    void display();
    
};



struct sahara {
    const std::vector<product> catalogue {
        {"iPhone XR", 10594029800330069, 48336},
        {"iPhone X",  10006102504500062, 48336},
        {"iPad Pro",  10950073200380230, 51031},
    };
    
    //const std::vector<int>
    //constexpr string hello = "hello";
    
};

class customer {
public:
    // shipping priority
    bool supreme;
    // coordinate pairs
    std::pair<int, int> address;
    std::string name;
    // holds the 2 dimensional products locations
    std::vector<product> order;
    sahara sahara;
    
    customer();
         
    // will give and X and Y coordinate of the shipping address
    void assign_address();
    
    // will determine the aproximate shippint i.e plane, truck etc. and provide an estimated time of shipping.
    void assign_shipping();
    
    void construct_packages();
    
    
    
};

#endif /* source_hpp */
