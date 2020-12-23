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
product::product(string name, size_t hash) : name(name), hash(hash) {
    length = 0;
    width = 0;
    height = 0;
    weight = 0;
    volume = 0;
}
// prints the relevant product information
void product::info() {
    cout << "NAME: " << name << endl;
    cout << "Price: " << price << endl;
    cout << "Length: " << length << endl;
    cout << "Width: " << width << endl;
    cout <<  "Height: " << height << endl;
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
