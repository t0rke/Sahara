//
//  main.cpp
//  Sahara
//
//  Created by Suneeth Torke on 12/19/20.
//

#include <iostream>
#include <vector>
#include <random>

// length width and height are grabbed from hashing the tracking number
// the UPC will be LLLLBBBBHHHHWWWWPP..
// the tracking will be PPTTTTFFFFCC
// priority, to, from, product_code
using namespace std;

class product {
public:
    size_t hash;
    string name;
    double price;
    double length;
    double width;
    double height;
    double weight;
    double volume;
    
    product (string name, size_t hash) : name(name), hash(hash) {
        length = 0;
        width = 0;
        height = 0;
        weight = 0;
        volume = 0;
    };
    //product (string name, double price, double length, double width, double height, double weight) :
    //length(length), width(width), height(height), weight(weight) {};
    
    void info () {
        cout << "NAME: " << name << endl;
        cout << "Price: " << price << endl;
        cout << "Length: " << length << endl;
        cout << "Width: " << width << endl;
        cout <<  "Height: " << height << endl;
        cout << "Weight: " << weight << endl;
    }
};

class location {
public:
    size_t to;
    size_t from;
    location();
    location(size_t to, size_t from) : to(to), from (from) {};
};

class package {
public:
    size_t tracking;
    size_t upc;
    size_t urgency;
    product product;
    location location;
    
    package (class product product, class location location) : product(product), location(location) {};
    void display() {
        cout << "Details: " << upc << endl;
        cout << "Tracking#: " << tracking << endl;
        cout << "Destination: " << location.to << endl;
        cout << "Origin: " << location.from << endl;
        //cout << "volume: " << product.volume << endl;
    }
    
};



class secure {
    //vector<product> catalogue {{"iPad Pro", 799.99, 18, 14, 8, },
    //    {"iPad Air" }, "iPad", "iPhone Pro Max", "iPhone 12", "iPhone Pro Mini"};
};

int main(int argc, const char * argv[]) {
    //std::random_device rd; // obtain a random number from hardware
    //std::mt19937 gen(rd()); // seed the generator
    //std::uniform_int_distribution<> distr(6, 27); // define the range
    
    // name and then UPC(length|width|height|weight)
    const vector<product> product_names {{"iPad Pro", 10594029800330007}};
    
    // insert code here...
    cout << endl;
    std::cout << "Hello, World!\n";
    return 0;
}
