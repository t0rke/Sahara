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
    size_t hash;
    std::string name;
    double price;
    double length, width, height, weight;
    double volume;
    
    product (std::string name, size_t hash);
  
    void info ();
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
    
    package (class product product, class location location);
    void display();
    
};



class secure {
    //vector<product> catalogue {{"iPad Pro", 799.99, 18, 14, 8, },
    //    {"iPad Air" }, "iPad", "iPhone Pro Max", "iPhone 12", "iPhone Pro Mini"};
};

#endif /* source_hpp */
