//
//  source.cpp
//  Sahara
//
//  Created by Suneeth Torke on 12/22/20.
//

#include "source.hpp"
#include <algorithm>

using namespace std;
///////////////////////////////////////////GEN FUNCTIONS/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct compare {
    inline bool operator() (const product &product1, const product &product2){
        return product1.location < product2.location;
    }
};


//////////////////////////////////////////PRODUCT FUNCTIONS//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// determines and assigns product specs (lWH) from hash int


product::product(const string name, const uint64_t hash, size_t location) : name(name), hash(hash), location(location) {
    weight = hash % 10000;
    const size_t height = ((hash % 100000000) - weight) / 10000;
    const size_t width = ((hash % 1000000000000) - (height * 10000) - weight) / 100000000;
    const size_t length = ((hash % 10000000000000000) - (width * 100000000) - (height * 10000) - weight) / 1000000000000;
    
    size_t t_lar = std::max({height,width, length});
    size_t t_sma = std::min({height, width, length});
    size_t t_mid = height ^ width ^ length ^ t_lar ^ t_sma;
    
    large = t_lar / 100.0;
    middle = t_mid / 100.0;
    small = t_sma / 100.0;
    weight /= 10.0;
    volume = large * middle * small;
    cout << name + ": "<< large << " " << middle << " "  << small << " " << weight << " [" << volume << "]" << endl;
}
// prints the relevant product information
void product::info() {
    cout << "NAME: " << name << endl;
    cout << "Price: " << price << endl;
    cout << "Dim: " << endl;
    cout << "Weight: " << weight << endl;
}

//////////////////////////////////////////LOCATION FUNCTIONS//////////////////////////////////////////////////////////////////////////////////////////////////////////////
location::location() {};

location::location(size_t to, size_t from) : to(to), from (from) {};


//////////////////////////////////////////PACKAGE FUNCTIONS///////////////////////////////////////////////////////////////////////////////////////////////////////
package::package (class product &product, class location &location) : product(product), location(location) {};

void package::display() {
    cout << "Details: " << upc << endl;
    cout << "Tracking#: " << tracking << endl;
    cout << "Destination: " << location.to << endl;
    cout << "Origin: " << location.from << endl;
    //cout << "volume: " << product.volume << endl;
}

//////////////////////////////////////////CUSTOMER FUNCTIONS///////////////////////////////////////////////////////////////////////////////////////////////////////
customer::customer() {
    assign_address();
    assign_shipping();
    construct_packages();
};


void customer::assign_address() {
    
}

void customer::assign_shipping() {
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(0, 1); // uniform int distribution
    supreme = (distr(gen) == 1 ? true : false);
}

size_t package_classifier () {
   // if ( ) {}
    
    return 0;
}

void customer::construct_packages() {
    order.clear();
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> idistr(0, 1); // generate a uniform dist
    cout << std:: boolalpha;
    cout << "Customer Prime status: " << supreme << endl;
    if (idistr(gen) == 1) {
        normal_distribution<> ndist(2, 1); // define the range
        const size_t num_products = ndist(gen);
        // cout << num_products << endl;
    
        // seeds the products into the order
        order.reserve(num_products);
        uniform_int_distribution<> udistr(0, int(sahara.catalogue.size()) - 1);
        for (size_t i = 0; i < num_products; ++i) {
            order.emplace_back(sahara.catalogue[udistr(gen)]);
            //cout << sahara.catalogue[udistr(gen)].name << endl;
        }
    }
    // sorts the product in an order
    //sort(begin(order), end(order), compare());
    //vector<vector<size_t>> resort();
    //resort.reserve(order.size());
     
    
    
    
    //package package;
}
