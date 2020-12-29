//
//  main.cpp
//  Sahara
//
//  Created by Suneeth Torke on 12/19/20.
//

#include <iostream>
#include "source.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    //std::random_device rd; // obtain a random number from hardware
    //std::mt19937 gen(rd()); // seed the generator
    //std::uniform_int_distribution<> distr(6, 27); // define the range
    
    // name and then UPC(length|width|height|weight)
    

    sahara sahara;
    //customer temp;
    int hello = 0;
    vector<customer> custs;
    custs.reserve(100000);
    customer temp;
    for (int i = 0; i < 1000; ++i) {
        cout << "----------------------------------------\n";
        cout << "#" << i << endl;
        customer temp;
        //custs.push_back(temp)
        //temp.display(i);
        hello += temp.order.size();

    }
    cout << hello << endl;
    
    // need to add random customer generation right adter

    // insert chode here...
    
}


/*
 
 Dec 21st -
    Began hashing UPC for vendor products
 Dec 22nd - completed product spec hasing
 Dec 25th - complete single parcel to package conversion
 Dec 27th - rebalanced number of packages being ordered per day
 Dec 29th - completed multiple package implementation, with cost per package shipping
 
 
 
 TODO: determine how to do location tracking for customers
 TODO: determine how to estimate and handle 1000 packages at once with customers unique identifier;
 
 
 
 
 
 */
