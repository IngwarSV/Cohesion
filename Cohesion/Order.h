#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <map>
#include "Item.h"
#include "Customer.h"

const int maxOrdersPerClient = 1000;
const int maxSignsInOrdersID = 4;

class Item;
class Customer;
class SeriesIdEnd;

class Order {
private:
    std::string createOrderId(Customer* customer);
    std::string orderId;
    Customer* client;
    std::map<Item*, int>* itemsInOrder;
    double totalPrice;

    static std::set<Order*>* allOrders;

public:
    Order(Customer* client, Item* item, int quantity);
    Order(const Order& copy);
    Order& operator=(const Order& copy);
    ~Order();

    const std::string& getOrderId() const;
    double getTotalPrice() const;

    void addItemInOrder(Item* item, int amount);
    void removeItemFromOrder(Item* item);

    void displayOrder();

    static void showAllOrders();
};

#endif // ORDER_H
