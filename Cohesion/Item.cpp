#include "Item.h"

std::string Item::setSeriesId(Category* category) {
    int id = category->getItemId() + 1;
    if (id > maxItemsInCategory) {
        throw SeriesIdEnd("Please buy Pro version of the soft!111");
    }

    std::string temp1 = category->getSeries();
    std::string temp2 = std::to_string(id);

    int counter = 0;
    for (; id > 0; ++counter) {
        id /= 10;
    }

    temp2.insert(0, maxSignsInItemsID - counter, '0');

    return temp1 + " " + temp2;
}

Item::Item(Category* category, const char* name, double price) {
    this->seriesId = setSeriesId(category);
    this->itemCategory = category;
    this->name = name;
    this->price = price;
    this->ordersList = new std::set<Order*>();
    category->addItem(this);
    allItems->insert(this);
}

Item::Item(const Item& copy) {
    this->seriesId = setSeriesId(copy.itemCategory);
    this->itemCategory = copy.itemCategory;
    this->name = copy.name;
    this->price = copy.price;
    this->ordersList = new std::set<Order*>();
    this->itemCategory->addItem(this);
    allItems->insert(this);
}

Item& Item::operator=(const Item& copy) {
    itemCategory->removeItem(this);
    for (auto it = this->ordersList->begin(); it != this->ordersList->end(); it++) {
        (*it)->removeItemFromOrder(this);
    }
    this->ordersList->clear();
    this->seriesId = setSeriesId(copy.itemCategory);
    this->itemCategory = copy.itemCategory;
    this->name = copy.name;
    this->price = copy.price;
    this->itemCategory->addItem(this);
    allItems->insert(this);

    return *this;
}

Item::~Item() {
    itemCategory->removeItem(this);
    for (auto it = this->ordersList->begin(); it != this->ordersList->end(); it++) {
        (*it)->removeItemFromOrder(this);
    }
    delete(this->ordersList);
    allItems->erase(this);
}

const char* Item::getName() const {
    return this->name;
}

const std::string& Item::getSeriesId() const {
    return this->seriesId;
}

double Item::getPrice() const {
    return this->price;
}

void Item::addOrderInItem(Order* order) {
    this->ordersList->insert(order);
}

void Item::removeOrderFromItem(Order* order) {
    this->ordersList->erase(order);
}

void Item::showItemOrders() {
    std::cout << this->name << " in orders: " << std::endl;
    for (auto it = this->ordersList->begin(); it != this->ordersList->end(); ++it) {
        std::cout << "\t#" << (*it)->getOrderId() << std::endl;
    }
}

//static

std::set<Item*>* Item::allItems = new std::set<Item*>();

void Item::showAllItems() {
    std::cout << "Items: " << std::endl;
    for (auto it = allItems->begin(); it != allItems->end(); ++it) {
        std::cout << "\tName: " << (*it)->getName();
        std::cout << "\tSeriesId: " << (*it)->getSeriesId();
        std::cout << "\tPrice: " << (*it)->getPrice() << " units" << std::endl;
    }
}
