#ifndef CATEGORY_H
#define CATEGORY_H

#include <iostream>
#include <set>
#include <map>
#include "Item.h"

const int maxItemsInCategory = 999'999;
const int maxSignsInItemsID = 6;

class Item;

class SeriesIdEnd {
public:
    std::string text;
    SeriesIdEnd(const std::string& text) : text(text) {}
};

class Category {
private:
    void seriesCounter();
    std::string series;
    const char* name;
    std::set<Item*>* items;

    static std::string nextSeries;
    static std::map<Category*, int>* allCategories;

public:
    Category(const char* name = "Category");
    Category(const Category& copy);
    ~Category();
    Category& operator=(const Category& copy) = delete;

    const char* getName() const;
    const std::string& getSeries() const;
    const int getItemId();

    void addItem(Item* item);
    void removeItem(Item* item);

    void listItems();

    static void showAllCategories();
};

#endif // CATEGORY_H
