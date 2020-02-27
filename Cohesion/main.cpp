#include <iostream>
#include "Category.h"
#include "Item.h"
#include "Order.h"
#include "Customer.h"

using namespace std;

int main() {

    // RANDOM TEST:
    try {
        Category* rifles = new Category("Rifles");
        Category* pistols = new Category("Pistols");

        Item* AK = new Item(rifles, "AK-74", 300);
        Item* UAR = new Item(rifles, "UAR-15", 400);

        Item* PM = new Item(pistols, "PM", 100);
        Item* TT = new Item(pistols, "TT", 200);

        Customer* dimon = new Customer("Dimon");
        Customer* helgie = new Customer("Helgie");

        Order* dimon1 = new Order(dimon, AK, 5);
        dimon1->addItemInOrder(UAR, 5);
        Order* dimon2 = new Order(dimon, PM, 5);
        dimon2->addItemInOrder(TT, 5);

        Order* helgie1 = new Order(helgie, AK, 10);
        helgie1->addItemInOrder(UAR, 10);
        helgie1->addItemInOrder(TT, 5);
        Order* helgie2 = new Order(helgie, PM, 10);
        helgie2->addItemInOrder(PM, 10);
        helgie2->addItemInOrder(TT, 10);
        std::cout << "+++++++++++++++++++++++++++++" << std::endl;

        Category::showAllCategories();
        Item::showAllItems();
        AK->showItemOrders();
        UAR->showItemOrders();
        PM->showItemOrders();
        TT->showItemOrders();
        Order::showAllOrders();
        // dimon->showCustomerOrders();
        // helgie->showCustomerOrders();
        Customer::showAllCustomers();

        std::cout << "+++++++++++++++++++++++++++++" << std::endl;
        //delete(helgie);
        // delete(pistols);
        // delete(PM);
        // delete(dimon1);

        std::cout << "+++++++++++++++++++++++++++++" << std::endl;

        Category::showAllCategories();
        Item::showAllItems();
        AK->showItemOrders();
        UAR->showItemOrders();
        PM->showItemOrders();
        TT->showItemOrders();
        Order::showAllOrders();
        dimon->showCustomerOrders();
        // helgie->showCustomerOrders();
        Customer::showAllCustomers();

        std::cout << "+++++++++++++++++++++++++++++" << std::endl;

        std::cout << "+++++++++++++++++++++++++++++" << std::endl;


        std::cout << "+++++++++++++++++++++++++++++" << std::endl;


        std::cout << "+++++++++++++++++++++++++++++" << std::endl;


        std::cout << "+++++++++++++++++++++++++++++" << std::endl;
    }
    catch (SeriesIdEnd message) {
        std::cout << message.text << std::endl;
    }
    catch (notUniqueLogin message) {
        std::cout << message.text << std::endl;
    }
    // RANDOM TEST END


    return 0;
}
