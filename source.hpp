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
#include <queue>
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
    std::vector<double> dimensions;
    double price;
    double weight, volume;

    product(const std::string name, const uint64_t hash, const size_t location);
  
    void info();
    //product (string name, double price, double length, double width, double height, double weight) :
    //length(length), width(width), height(height), weight(weight) {};
    
};

// holds the relevant to and from locations, UPC
struct location {
    size_t from;
    std::pair<int,int> to;
    location();
    location(std::pair<int,int> address, size_t from);
};

struct parcel {
    std::string name;
    double weight;
    double price;
    std::vector<double> dim;
    parcel (std::string name, double weight, double price, std::vector<double> dim) : name(name), weight(weight), price(price), dim(dim) {};
};

// holds the box packaging sizes
class package {
public:
    size_t tracking;
    size_t upc;
    size_t urgency;
    size_t dim_index;
    double net_weight;
    double price;
    std::vector<size_t> product_indices;
    location location;
    
    package(std::vector<size_t> indices, class location &location, size_t dim_index, double net_weight, double price);
    
    void display();
    
};

const std::vector<double> FBL_small_and_light{16, 9 , 4};
const std::vector<double> small_standard{15, 12 , 0.75};
const std::vector<double> large_standard{18, 14, 8};
const std::vector<double> small_oversize{60, 30, 20};

const std::vector<std::vector<double>> containers {{FBL_small_and_light, small_standard, large_standard, small_oversize}};

const std::vector<parcel> box_types {
    {"FBA1", 3.3, 1.97, FBL_small_and_light},
    {"FBA2", 9.3, 2.39, FBL_small_and_light},
    {"SS1", 6, 2.50, small_standard},
    {"SS2", 12, 2.63, small_standard},
    {"LS1", 6, 3.31, large_standard},
    {"LS2", 12, 3.48, large_standard},
    {"LS3", 28, 4.90, large_standard},
    {"LS4", 44, 5.42, large_standard},
    {"LS5", 332, 5.42, large_standard},
    {"SO", 1132, 8.26, small_oversize}};

const std::vector<product> catalogue {
     {"iPhone XR",                      10594029800330069, 48336},
     {"iPhone X",                       10060102504500062, 48336},
     {"iPad Pro",                       10950073200380230, 48168},
     {"iPad Air",                       10974070000240160, 48168},
     {"iPad",                           10980068000290175, 48168},
     {"iPad Mini",                      10800053000240106, 48168},
     {"iPhone 12 Pro",                  10578028200290067, 51031},
     {"iPhone 12 Pro Max",              10633030700290081, 51031},
     {"iPhone 12 mini",                 10518025300290048, 51031},
     {"iPhone 12",                      10578028200290058, 51031},
     {"MacBook Air",                    10063119708360045, 71736},
     {"MacBook Pro",                    10061119708360480, 71736},
     {"Apple Watch Series 6 (44m)",     10174015000430017, 51031},
     {"Apple Watch Series 6 (40m)",     10158013400430015, 51031},
     {"AirPods Pro ",                   10239017800850017, 71736},
     {"iMac (21.5 in) ",	           	11770020806901920, 51031},
     {"iMac (27 in) ",			        12030256008003153, 51031},
     {"iMac Pro ",			            12030256008003440, 51031},
     {"Mac Mini ",			            10140077007700416, 51031},
     {"iPod Touch",			            10231048600240031, 51031},
     {"HomePod ",			            10680056005600880, 51031},
     {"HomePod mini",			        10330039003900122, 51031},
     {"Apple Watch SE (40m)",		    10158013400430011, 51031},
     {"Apple Watch SE (44m)",		    10174015000430013, 51031},
     {"iPhone SE",			            10545026500290053, 51031},
 };


class sahara {
public:
    
    
    std::priority_queue<package> order_priority;
    
    void initialize_supporting_materials();
    
    void generate_customer_accounts() {
        
    }
    
    void company_monetary() {
        
    }
    
    void increase_time() {
        
    }
    
    
    //const std::vector<int>
    //constexpr string hello = "hello";
    
};

//vector<tuple>sizing_chart();

class customer {
public:
    // shipping priority
    bool supreme;
    // coordinate pairs
    std::pair<int, int> address;
    std::string name;
    // holds the 2 dimensional products locations
    // order history
    std::vector<size_t> history;
    // current order
    std::vector<size_t> order_index;
    std::vector<product> order;
    std::queue<package> queue;
    
    
    customer();
         
    // will give and X and Y coordinate of the shipping address
    void assign_address();
    
    // will determine the aproximate shippint i.e plane, truck etc. and provide an estimated time of shipping.
    void assign_shipping();
    
    void construct_packages();
    
    void generate_profile();
    
    void package_handler(std::vector<size_t> &resort_splice);
    
    void display(size_t i);
    
    bool product_configurations(std::vector<std::vector<double>> &dim_matrix, size_t i);
    
    
    
};

#endif /* source_hpp */
