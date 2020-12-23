//
//  source.cpp
//  Sahara
//
//  Created by Suneeth Torke on 12/22/20.
//

#include "source.hpp"

using namespace std;

//////////////////////////////////////////PRODUCT FUNCTIONS//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// determines product information from the product hash
product::product(const string name, const uint64_t hash) : name(name), hash(hash) {

    // insert code here:
    
    
    
    
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
