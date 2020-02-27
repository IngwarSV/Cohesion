#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <set>
#include <string>

#include "Category.h"
#include "Order.h"

class Category;
class Order;
class SeriesIdEnd;

class Item {
private:
    std::string setSeriesId(Category* category);
    std::string seriesId;
    Category* itemCategory;
    const char* name;
    double price;
    std::set<Order*>* ordersList;

    static std::set<Item*>* allItems;

public:
    Item(Category* category, const char* name = "Item", double price = 0.0);
    Item(const Item& copy);
    Item& operator=(const Item& copy);
    ~Item();

    const char* getName() const;
    const std::string& getSeriesId() const;
    double getPrice() const;

    void addOrderInItem(Order* order);
    void removeOrderFromItem(Order* order);

    void showItemOrders();

    static void showAllItems();
};

#endif // ITEM_H
