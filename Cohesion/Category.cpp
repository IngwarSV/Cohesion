#include "Category.h"

void Category::seriesCounter() {
    if (nextSeries[1] + 1 > 'Z') {
        if (nextSeries[0] + 1 > 'Z') {
            throw SeriesIdEnd("Please buy Pro version of the soft!");
        }
        nextSeries[1] = 'A';
        nextSeries[0] += 1;
        return;
    }
    nextSeries[1] += 1;
}

Category::Category(const char* name) {
    seriesCounter();
    this->series = nextSeries;
    this->name = name;
    this->items = new std::set<Item*>();
    allCategories->insert(std::pair<Category*, int>(this, 0));
}

Category::Category(const Category& copy) {
    seriesCounter();
    this->series = nextSeries;
    this->name = copy.name;
    this->items = new std::set<Item*>();
    allCategories->insert(std::pair<Category*, int>(this, 0));
}

Category::~Category() {
    for (auto it = this->items->begin(); !this->items->empty(); it++) {
        delete(*it);
    }
    delete(this->items);
    allCategories->erase(this);
}

const char* Category::getName() const {
    return this->name;
}

const std::string& Category::getSeries() const {
    return this->series;
}

const int Category::getItemId() {
    return allCategories->at(this);
}

void Category::addItem(Item* item) {
    this->items->insert(item);
    allCategories->at(this) += 1;
}

void Category::removeItem(Item* item) {
    this->items->erase(item);
}

void Category::listItems() {
    std::cout << "Items in category " << "\"" << this->getName() << "\"" << ":" << std::endl;
    for (auto it = this->items->begin(); it != this->items->end(); ++it) {
        std::cout << "\tSeriesId: " << (*it)->getSeriesId();
        std::cout << "\tItem's Name: " << (*it)->getName() << std::endl;
    }
}

//static

std::string Category::nextSeries = "A@";

std::map<Category*, int>* Category::allCategories = new std::map<Category*, int>();

void Category::showAllCategories() {
    std::cout << "Categories: " << std::endl;
    for (auto it = allCategories->begin(); it != allCategories->end(); ++it) {
        std::cout << "\tSeries: " << it->first->getSeries();
        std::cout << "\tName: " << it->first->getName();
        std::cout << "\tItem's quantity: " << it->second << std::endl;
    }
}

