#include "Order.h"

std::string Order::createOrderId(Customer* customer) {
    int id = customer->getOrderNumber() + 1;
    if (id > maxOrdersPerClient) {
        throw SeriesIdEnd("Please buy Pro version of the soft!");
    }

    std::string temp1 = customer->getLogin();
    std::string temp2 = std::to_string(id);

    int counter = 0;
    for (; id > 0; ++counter) {
        id /= 10;
    }

    temp2.insert(0, maxSignsInOrdersID - counter, '0');

    return temp1 + "-" + temp2;
}

Order::Order(Customer* customer, Item* item, int quantity) {
    this->orderId = createOrderId(customer);
    this->client = customer;
    this->itemsInOrder = new std::map<Item*, int>();
    this->totalPrice = 0.0;
    this->addItemInOrder(item, quantity);
    this->client->addOrder(this);
    allOrders->insert(this);
}

Order::Order(const Order& copy) {
    this->orderId = createOrderId(copy.client);
    this->client = copy.client;
    this->itemsInOrder = new std::map<Item*, int>(*copy.itemsInOrder);
    this->totalPrice = copy.totalPrice;
    this->client->addOrder(this);
    allOrders->insert(this);
    for (auto it = itemsInOrder->begin(); it != itemsInOrder->end(); ++it) {
        it->first->addOrderInItem(this);
    }
}

Order& Order::operator=(const Order& copy) {
    for (auto it = itemsInOrder->begin(); it != itemsInOrder->end(); ++it) {
        it->first->removeOrderFromItem(this);
    }
    this->itemsInOrder = copy.itemsInOrder;
    this->totalPrice = copy.totalPrice;
    for (auto it = itemsInOrder->begin(); it != itemsInOrder->end(); ++it) {
        it->first->addOrderInItem(this);
    }
    if (this->client != copy.client) {
        this->client->deleteOrder(this);
        this->orderId = createOrderId(copy.client);
        this->client = copy.client;
        this->client->addOrder(this);
    }
    return *this;
}

Order::~Order() {
    for (auto it = itemsInOrder->begin(); it != itemsInOrder->end(); ++it) {
        it->first->removeOrderFromItem(this);
    }
    delete(this->itemsInOrder);
    client->deleteOrder(this);
    this->totalPrice = 0.0;
    allOrders->erase(this);
}

const std::string& Order::getOrderId() const {
    return this->orderId;
}

double Order::getTotalPrice() const {
    return this->totalPrice;
}

void Order::addItemInOrder(Item* item, int amount) {
    if (itemsInOrder->find(item) == itemsInOrder->end()) {
        itemsInOrder->insert(std::pair<Item*, int>(item, 0));
    }
    itemsInOrder->at(item) += amount;
    this->totalPrice += item->getPrice() * amount;
    item->addOrderInItem(this);
}

void Order::removeItemFromOrder(Item* item) {
    std::map<Item*, int>::iterator it = itemsInOrder->find(item);
    this->totalPrice -= item->getPrice() * it->second;
    itemsInOrder->erase(item);
    if (itemsInOrder->empty()) {
        std::cout << "Order # " << this->orderId << " is empty, is deleted " << std::endl;
        delete(this);
    }
}

void Order::displayOrder() {
    std::cout << "Order #";
    std::cout << this->orderId << std::endl;
    for (auto it = itemsInOrder->begin(); it != itemsInOrder->end(); ++it) {
        std::cout << "\t" << it->first->getName() << " : ";
        std::cout << it->second << " pcs." << std::endl;
    }
    std::cout << "Total price of order #" << this->orderId << " : ";
    std::cout << this->totalPrice << " units" << std::endl;
}

//static

std::set<Order*>* Order::allOrders = new std::set<Order*>();

void Order::showAllOrders() {
    std::cout << "Orders: " << std::endl;
    for (auto it = allOrders->begin(); it != allOrders->end(); it++) {
        std::cout << "\tOrder #" << (*it)->getOrderId();
        std::cout << "\tTotal price: " << (*it)->getTotalPrice() << " units" << std::endl;
    }
}
