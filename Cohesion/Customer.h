#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <set>
#include <map>
#include "Item.h"
#include "Order.h"

class Item;
class Order;

class notUniqueLogin {
public:
    std::string text;
    notUniqueLogin(const std::string& text) : text(text) {}
};

class Customer {
private:
    void customerLoginVerification(const char* login);
    const char* login;
    std::set<Order*>* customerOrders;

    static std::map<Customer*, int>* allCustomers;

public:
    Customer(const char* login = "Customer");
    Customer(const Customer& copy);
    Customer& operator=(const Customer& copy) = delete;
    ~Customer();

    const char* getLogin() const;
    int getOrderNumber();

    void addOrder(Order* order);
    void deleteOrder(Order* order);

    void showCustomerOrders();

    static void showAllCustomers();
};

#endif // CUSTOMER_H
