//
//  source.cpp
//  Sahara
//
//  Created by Suneeth Torke on 12/22/20.
//

#include "source.hpp"
#include <algorithm>
#include <fstream>

using namespace std;

///////////////////////////////////////////GEN FUNCTIONS/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<string> generate_list(string list_name) {
    string name;
    vector<string> names_list;
    ifstream file(list_name);
    if (file.fail()) cout << "couldnt open file" << endl;
    names_list.reserve(2500);
    while (getline(file, name)) names_list.push_back(name);
    return names_list;
}

// holds the FIRST and LAST names
const std::vector<std::string> first_names = generate_list("Fnames.txt"),
    last_names = generate_list("Fnames.txt");

struct compare {
    inline bool operator() (const product &product1, const product &product2){
        return product1.location < product2.location;
    }
};

const double VERBOSE = true;

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
    
    //cout << name << " " << dimensions[0] << " " << dimensions[1] << " " << dimensions[2] << " " << weight << endl;
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
package::package(vector<size_t> indices, class location &location, size_t dim_index, double net_weight, double price) :
    product_indices(indices), location(location), dim_index(dim_index), net_weight(net_weight), price(price) {};

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
    construct_order();
};

void customer::generate_profile() {
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(0, 2248);
    name = first_names[distr(gen)] + " " + last_names[distr(gen)];
}

void customer::assign_address() {
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> adistr(-3500, 2000); //
    uniform_int_distribution<> bdistr(-20000, 1500); //
    address = {adistr(gen), bdistr(gen)};
}
// assigns the shipping priority
void customer::assign_shipping() {
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(0, 1); // uniform int distribution
    supreme = (distr(gen) == 1 ? true : false);
}

// TODO: implement more combinations of this to make sure the correct item was picked
bool customer::product_configurations(vector<vector<double>> &dim_matrix, size_t i) {
    vector<double>local_dims;
    local_dims.reserve(3);
    if (dim_matrix.size() == 2) {
        cout << "       Detected A set of 2" << endl;
        local_dims.push_back(dim_matrix[0][0] + dim_matrix[1][0]);
        local_dims.push_back(dim_matrix[0][1] + dim_matrix[1][1]);
        local_dims.push_back(dim_matrix[0][2] + dim_matrix[1][2]);
    }
    if (dim_matrix.size() == 3) {
        cout << "       Detected A set of 3" << endl;
        local_dims.push_back(dim_matrix[0][0] + dim_matrix[1][0] + dim_matrix[2][1]);
        local_dims.push_back(dim_matrix[0][1] + dim_matrix[1][1] + dim_matrix[2][2]);
        local_dims.push_back(dim_matrix[0][2] + dim_matrix[1][2] + dim_matrix[2][0]);
    }
    if (dim_matrix.size() == 4) {
        cout << "       Detected A set of 4" << endl;
        local_dims.push_back(dim_matrix[0][0] + dim_matrix[1][0] + dim_matrix[2][0] + dim_matrix[3][1]);
        local_dims.push_back(dim_matrix[0][1] + dim_matrix[1][1] + dim_matrix[2][1] + dim_matrix[3][2]);
        local_dims.push_back(dim_matrix[0][2] + dim_matrix[1][2] + dim_matrix[2][2] + dim_matrix[3][0]);
    }
    sort(rbegin(local_dims), rend(local_dims));
    size_t valid = 0;
    for(size_t j = 0; j < 3; ++j) {
        if (local_dims[j] <= box_types[i].dim[j]) {
            if (VERBOSE) cout << "       validated: " << local_dims[j] << " <= " << box_types[i].dim[j] << endl;
            ++valid;
        }
        if (valid == 3) return true;
    }
    return false;
}

void customer::package_handler(vector<size_t> &resort_splice) {
    if (VERBOSE) cout << "  Entered Package Handler" << endl;
    if (resort_splice.size() > 1) {
        if (VERBOSE) cout << "      Detected multiple products" << endl;
        vector<vector<double>> dim_matrix;
        double net_weight = 0;
        for (size_t i = 0; i < resort_splice.size(); ++i) {
            dim_matrix.push_back(order[resort_splice[i]].dimensions);
            net_weight += order[resort_splice[i]].weight;
        }
        for (size_t i = 0; i < box_types.size(); ++i) {
            if (net_weight <= box_types[i].weight) {
                if (VERBOSE) cout << "       matched: " << net_weight << " <= " << box_types[i].weight << endl;
                if (product_configurations(dim_matrix, i)) {
                    if (VERBOSE) cout << "       Selected a package ->" << box_types[i].name << endl;
                    double price = box_types[i].price;
                    if (box_types[i].name == "LS5" || box_types[i].name == "SO") {
                        double diff = 0.0;
                        if (box_types[i].name == "LS5") diff = net_weight - 32;
                        else diff = net_weight - 48;
                        price = box_types[i].price + (ceil(diff / 16.0) * 0.38);
                        cout << "       Calculated Price: " << price << endl;
                    }
                    location temp({address, order[resort_splice[0]].location});
                    queue.push({{order_index[resort_splice[0]]}, temp, i, order[resort_splice[0]].weight + 7, price});
                    break;
                }
            }
        }
    }
    else {
        if (VERBOSE) cout << "      Detected solo product" << endl;
        for (size_t i = 0; i < box_types.size(); ++i) {
            size_t valid = 0;
            for (size_t j = 0; j < 3; ++j) {
                if (order[resort_splice[0]].dimensions[j] <= box_types[i].dim[j]) {
                    if (VERBOSE) cout << "       validated: " << order[resort_splice[0]].dimensions[j] << " <= " << box_types[i].dim[j] << endl;
                    ++valid;
                }
                if (valid == 3) {
                    for (size_t k = 0; k < box_types.size(); ++k, ++i) {
                        if (order[resort_splice[0]].weight <= box_types[i].weight) {
                            if (VERBOSE) cout << "       validated: " << order[resort_splice[0]].weight << " <= " << box_types[i].weight << endl;
                            if (VERBOSE) cout << "       Selected a package ->" << box_types[i].name << endl;
                            double price = order[resort_splice[0]].weight;
                            if (box_types[i].name == "LS5" || box_types[i].name == "SO") {
                                double diff = 0.0;
                                if (box_types[i].name == "LS5") diff = box_types[i].weight - 32;
                                else diff = box_types[i].weight - 48;
                                price = box_types[i].price + (ceil(diff / 16.0) * 0.38);
                                cout << "       Calculated Price: " << price << endl;
                            }
                            location temp({address, order[resort_splice[0]].location});
                            // the product index from the list or products, the location, the index of the dimension from the list, the combined pacakge and product weight
                            // could be removed and grabbed from indices again
                            queue.push({{order_index[resort_splice[0]]}, temp, i, order[resort_splice[0]].weight + 7, price});
                            return;
                        }
                    }
                }
            }
        }
    }
}

void customer::construct_order() {
    order.clear();
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> idistr(0, 100); // generate a uniform dist
    cout << std:: boolalpha;
    // cout << "Customer Prime status: " << supreme << endl;
    if (idistr(gen) == 1) {
        normal_distribution<double> distr(2, 1); // define the range  // HAVING ISSUES WITH NDIST
        uint32_t num_products = distr(gen);
        if (num_products > 9) num_products = 0;
        if (num_products == 0) {
            if (VERBOSE) cout << ">No Order" << endl;
            return;
        }
        // seeds the products into the order
        order.reserve(num_products);
        uniform_int_distribution<> udistr(0, int(catalogue.size()) - 1);
        if (VERBOSE) cout << "[" + name + "]" << endl;
        for (size_t i = 0; i < num_products; ++i) {
            size_t prod = udistr(gen);
            order.push_back(catalogue[prod]);
            order_index.push_back(prod);
            history.push_back(prod);
            if (VERBOSE) cout << catalogue[prod].name << endl;
        }
        // sorts the product in an order
        sort(begin(order), end(order), compare());
        vector<vector<size_t>> resort;
        
        // will not ship two of the same products in a single package!!!
        vector<size_t>temp;
        temp.push_back(0);
        for (size_t i = 1; i < order.size(); ++i) {
            if (order[i - 1].location == order[i].location) temp.push_back(i);
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
    else { if (VERBOSE) cout << "No Order" << endl; }
}

void customer::reorder() {
    ++reorder_count;
    construct_order();
}

void customer::display(size_t i) {
    cout << "#" << i << " [" + name + "] (" << address.first << ", " << address.second
        << ") SPM->" << supreme << " CORD: " << order.size() << " HIST: " << history.size() << " Rord: " << reorder_count << endl;
}

//////////////////////////////////////////SAHARA FUNCTIONS///////////////////////////////////////////////////////////////////////////////////////////////////////


void sahara::initialize_supporting_materials() {
    // initializes the names lists
//    generate_list(first_names, "fname.txt");
//    generate_list(last_names, "lname.txt");

}

