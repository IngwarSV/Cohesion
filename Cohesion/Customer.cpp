#include "Customer.h"

void Customer::customerLoginVerification(const char* login) {
    for (auto it = allCustomers->begin(); it != allCustomers->end(); ++it) {
        if (it->first->getLogin() == login) {
            throw notUniqueLogin("Login is already exsisting");
        }
    }
}

Customer::Customer(const char* login) {
    customerLoginVerification(login);
    this->login = login;
    this->customerOrders = new std::set<Order*>();
    allCustomers->insert(std::pair<Customer*, int>(this, 0));
}

Customer::Customer(const Customer& copy) {
    throw notUniqueLogin("Login is already exsisting, please create new one object");
}

// Customer& Customer::operator=(const Customer& copy) {
//     std::cout << "Login is already exsisting, you can't copy another object" << '\n';
//     return *this;
// }

Customer::~Customer() {
    for (auto it = this->customerOrders->begin(); !this->customerOrders->empty(); ++it) {
        delete(*it);
    }
    delete(this->customerOrders);
    allCustomers->erase(this);
}

const char* Customer::getLogin() const {
    return this->login;
}

int Customer::getOrderNumber() {
    return allCustomers->at(this);
}

void Customer::showCustomerOrders() {
    std::cout << "Client " << this->login << ":" << std::endl;
    for (auto it = this->customerOrders->begin(); it != this->customerOrders->end(); ++it) {
        std::cout << "\tOrder #" << (*it)->getOrderId() << std::endl;
    }
}

void Customer::addOrder(Order* order) {
    this->customerOrders->insert(order);
    allCustomers->at(this) += 1;
}

void Customer::deleteOrder(Order* order) {
    this->customerOrders->erase(order);
}

//static

std::map<Customer*, int>* Customer::allCustomers = new std::map<Customer*, int>();

void Customer::showAllCustomers() {
    std::cout << "Customers: " << std::endl;
    for (auto it = allCustomers->begin(); it != allCustomers->end(); ++it) {
        std::cout << "\tName: " << it->first->getLogin();
        std::cout << "\tOrder's quantity: " << it->second << std::endl;
    }
}
