# Sahara

Sahara is a C++ project that features everything I have learned thus far in computer science. It is the culmination of three years of learning and growth. The program models a Shipping company named Sahara that seeks to optimize shipping routes and minimize both overhead and shipping costs while quickly being able to gather and track customer information.

#### Notable Components
1. Data Structures -> Vector, Deque, Priority Queue, Unordered Map
2. Hashing
3. Optimization Algorithm w/ Heuristics
4. Relational Database w/ Quick Lookup
5. Pathfinding 
6. High Level Abstraction

## Program Hierarchy and General Information

Sahara is a national shipping company that focuses on getting a limited selection of products to customers as quickly and efficiently as possible. With a wide range of facilties and transportation methods available, I have implemented a program that will take our Randomly generated Customer Accounts and manage shipping, billing and transcational functions for these accounts

The program will randomly generate a series a of customer profiles using two pregenerated list `firstname.txt` and `lastname.txt` to generate a customers first and last name. These names act as one part of the customers uniqe indentifier. Through the use of the STL Mersenne Twister Random Number Generator, the program will select each customers home location and what products they will order.

Sahara has multiple Warehouses that hold products that may be unique to that facility. Each Facility will hold at least one type of item, and Shipping Routes are predetermined, but Last Mile Shipping will be variable due to location.


## How it Works
### Key Terminology:
- **Customer** -> a randomly generated entity which has the ability to order items, and has a set home location.
- **Product** -> any item that is purchaseable by the customer (i.e. Mouse, Computer, Tablet, Chair)
- **Package** -> a combination of one or more `Products`, groups one or more items ordered by the customer (travelling to the same destination) to reduce packaging and shipping costs
- **Warehouse** -> a location which a product originates from i.e Detroit, Michigan or Springfield, Illinois, which is stored as a coordinate pair of the longitude and Latitude of the buildings geolocation.


### Order Processing

At Runtime, the user speicifed number of accounts are generated and preliminary orders are managed. Throut a calendar year, a customer may order N products M times and this information is stored to understand the customers buying behavior (for marketing functions). Based on which warehouse location each of the M products are our classifying algorithm determines how many of the products to fit into the package.

Sahara's ideology is simple, the more products they can fit into a shipping package the less money is used for packaging materials. If a customer order both an apple and orange from Warehouse A, the classifying algorithm will attempt to find that smallest package that will be able to house both products. Similarly if multiple products are comming from one location, an alternate algorithm will attempt to figure out the optimal number of packages to fit in a transportation vehicle.

### Shipping



### Marketing



### Returns




