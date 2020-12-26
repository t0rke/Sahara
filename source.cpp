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


double verbose = false;

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
    
    dimensions.resize(3);
    dimensions[0] = t_lar / 100.0;
    dimensions[1] = t_mid / 100.0;
    dimensions[2] = t_sma / 100.0;
    weight /= 10.0;
    volume = dimensions[0] * dimensions[1] * dimensions[2];
    cout << name + ": "<< dimensions[0] << " " << dimensions[1] << " "  << dimensions[2] << " " << weight << " [" << volume << "]" << endl;
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

location::location(pair<int,int> address, size_t from) : to(address), from (from) {};


//////////////////////////////////////////PACKAGE FUNCTIONS////////////////////////////////////////////////////////////////////////////////////////////////////////////
package::package(vector<size_t> indices, class location &location, size_t dim_index, double net_weight) :
    product_indices(indices), location(location), dim_index(dim_index), net_weight(net_weight) {};

void package::display() {
    cout << "Details: " << upc << endl;
    cout << "Tracking#: " << tracking << endl;
    cout << "Destination: " << location.to.first << endl;
    cout << "Origin: " << location.from << endl;
    //cout << "volume: " << product.volume << endl;
}

//////////////////////////////////////////CUSTOMER FUNCTIONS///////////////////////////////////////////////////////////////////////////////////////////////////////
customer::customer() {
    generate_profile();
    assign_address();
    assign_shipping();
    construct_packages();
};

void customer::generate_profile() {
    std::ifstream file;
	file.open("Lnames.txt", ios::in);
	vector <string> names;
	string name;
	names.reserve(62644);
	int i = 0;
	while (getline(file, name)) {

		getline(file, name);
		names.push_back(name);
		if (i % 14 == 0) {
			cout << name << endl;
		}
		else {

		}
		i++;
	}
}

void customer::assign_address() {
    
}
// assigns the shipping priority
void customer::assign_shipping() {
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(0, 1); // uniform int distribution
    supreme = (distr(gen) == 1 ? true : false);
}

void customer::package_handler(vector<size_t> &resort_splice) {
    if (verbose) cout << "Entered Package Handler" << endl;
    if (resort_splice.size() > 1) {
        vector<vector<double>> dim_matrix;
        for (size_t i = 0; i < resort_splice.size(); ++i) {
             dim_matrix.push_back(order[resort_splice[i]].dimensions);
        }
    }
    else {
        if (verbose) cout << "    Determined solo product" << endl;
        for (size_t i = 0; i < box_types.size(); ++i) {
            size_t valid = 0;
            for (size_t j = 0; j < 3; ++j) {
                if (order[resort_splice[0]].dimensions[j] <= box_types[i].dim[j]) {
                    ++valid;
                    if (verbose) cout << "     validated: " << order[resort_splice[0]].dimensions[j] << " <= " << box_types[i].dim[j] << endl;
                }
                if (valid == 3) {
                    for (size_t k = 0; k < box_types.size(); ++k, ++i) {
                        if (order[resort_splice[0]].weight <= box_types[i].weight) {
                            if (verbose) cout << "     validated: " << order[resort_splice[0]].weight << " <= " << box_types[i].weight << endl;
                            if (verbose) cout << "     Selected a package ->" << box_types[i].name << endl;
                            // sets the
                            location temp({address, order[resort_splice[0]].location});
                            // the product index from the list or products, the location, the index of the dimension from the list, the combined pacakge and product weight
                            // could be removed and grabbed from indices again
                            queue.push({{order_index[resort_splice[0]]}, temp, i, order[resort_splice[0]].weight + 7});
                            return;
                        }
                    }
                }
            }
        }
    }
}

void customer::construct_packages() {
    order.clear();
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> idistr(0, 1); // generate a uniform dist
    cout << std:: boolalpha;
    // cout << "Customer Prime status: " << supreme << endl;
    if (/* idistr(gen) == 1 */ (true)) {
        normal_distribution<> ndist(2, 1); // define the range
        const size_t num_products = ndist(gen);
        // cout << num_products << endl;
        if (num_products == 0) {
            if (verbose) cout << "SP no order" << endl;
            return;
        }
        // seeds the products into the order
        order.reserve(num_products);
        uniform_int_distribution<> udistr(0, int(catalogue.size()) - 1);
        for (size_t i = 0; i < num_products; ++i) {
            size_t prod = udistr(gen);
            order.push_back(catalogue[prod]);
            order_index.push_back(prod);
            history.push_back(prod);
            cout << catalogue[prod].name << endl;
        }
        // sorts the product in an order
        sort(begin(order), end(order), compare());
        vector<vector<size_t>> resort;
        
        // will not ship two of the same products in a single package!!!
        vector<size_t>temp;
        temp.push_back(0);
        for (size_t i = 1; i < order.size(); ++i) {
            if (order[i - 1].location == order[i].location) {
                temp.push_back(i);
            }
            else {
                resort.push_back(temp);
                temp.clear();
                temp.push_back(i);
            }
        }
        resort.push_back(temp);
        // determines how to package the items
        for (int i = 0; i < resort.size(); ++i) package_handler(resort[i]);
    }
    else {
        if (verbose) cout << "No Order" << endl;
    }
}
