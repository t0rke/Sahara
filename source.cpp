//
//  source.cpp
//  Sahara
//
//  Created by Suneeth Torke on 12/22/20.
//

#include "source.hpp"

using namespace std;

//////////////////////////////////////////PRODUCT FUNCTIONS//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// determines and assigns product specs (lWH) from hash int
product::product(const string name, const uint64_t hash) : name(name), hash(hash) {
    weight = hash % 10000;
    const size_t height = ((hash % 100000000) - weight) / 10000;
    const size_t width = ((hash % 100000000000) - (height * 10000) - weight) / 100000000;
    const size_t length = ((hash % 1000000000000000) - (width * 100000000) - (height * 10000) - weight) / 1000000000000;

    size_t t_lar = std::max({height,width, length});
    size_t t_sma = std::min({height, width, length});
    size_t t_mid = height ^ width ^ length ^ t_lar ^ t_sma;
    
    large = t_lar / 100.0;
    middle = t_mid / 100.0;
    small = t_sma / 100.0;
    volume = large * middle * small;
    //cout << large << " " << middle << " "  << small << " " << weight << endl;
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
package::package (class product product, class location location) : product(product), location(location) {};

void package::display() {
    cout << "Details: " << upc << endl;
    cout << "Tracking#: " << tracking << endl;
    cout << "Destination: " << location.to << endl;
    cout << "Origin: " << location.from << endl;
    //cout << "volume: " << product.volume << endl;
}
