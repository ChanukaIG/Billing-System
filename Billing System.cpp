#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MENU_SIZE = 8;
const int MAX_ORDER_SIZE = 15;

struct MenuItem {
    int itemNo{};
    string itemName;
    double price{};
};

// LOAD MENU LIST TO ARRAY
void getData(MenuItem menuList[])
{
    menuList[0] = { 111, "Plain Egg    ", 1.45 };
    menuList[1] = { 112, "Bacon and Egg", 2.45 };
    menuList[2] = { 113, "Muffin       ", 0.99 };
    menuList[3] = { 114, "French Toast ", 1.99 };
    menuList[4] = { 115, "Fruit Basket ", 2.49 };
    menuList[5] = { 116, "Cereal       ", 0.69 };
    menuList[6] = { 117, "Coffee       ", 0.50 };
    menuList[7] = { 118, "Tea          ", 0.75 };
}

// DISPLAY MENU FOR CUSTOMER
void showMenu(const MenuItem menuList[])
{
    cout.setf(ios::fixed);
    cout.precision(2);

    cout << "------- Welcome to Meal Hut --------" << endl;
    cout << "----- Breakfast Billing System -----\n";
    cout << "                              \n";
    cout << "Item No     Menu Item         Price\n";
    for (int i = 0; i < MENU_SIZE; ++i) {
        cout << menuList[i].itemNo << "         " << menuList[i].itemName << "     $" << menuList[i].price << endl;
    }
    cout << "\nNote: A 5% tax will be added to the full bill.\n";
    cout << "\nInstructions: \n";
    cout << "    * Enter No 2 (Order Items) for start add items to your order.\n";
    cout << "    * Enter one item number at a time.\n";
    cout << "    * After adding items please enter No 3 (Calculate Bill) for generate the bill.\n";
    cout << "    * You can order only 15 items per bill.\n";
}

// ADD ITEMS TO THE ORDER 
int orderPlace(const MenuItem menuList[], int orderedItemsCount[])
{
    int orderAmount = 0;
    const int MAX_ORDER_SIZE = 15;

    cout << "Enter item numbers to order, one at a time (type 0 to finish): ";
    int input;
    while (cin >> input && input != 0) {
        if (orderAmount >= MAX_ORDER_SIZE) {
            cout << "You have reached the maximum order limit of " << MAX_ORDER_SIZE << " items.\n";
            break;
        }

        bool found = false;
        for (int i = 0; i < MENU_SIZE; ++i) {
            if (menuList[i].itemNo == input) {
                orderedItemsCount[orderAmount++] = i;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Invalid item number. Please try again.\n";
        }
        else if (orderAmount <= MAX_ORDER_SIZE) {
            cout << "ITEM ADDED!\n";
            cout << "\nEnter next item number or 0 to finish: ";
        }
    }

    if (orderAmount > 0) {
        cout << "\nItems successfully added to your order.\n";
    }
    else {
        cout << "\nNo items were added.\n";
    }

    return orderAmount;
}

// CALCULATE AND PRINT BILL AND SAVE BILLS TO A FILE
void printCheck(const string& filename, const MenuItem menuList[], const int orderedItemsCount[], int orderAmount)
{
    static int orderNo = 1;
    double subTotal = 0;
    double taxRate = 0.05;

    // ROUNDING FOR TWO DECIMAL POINTS
    cout.setf(ios::fixed);
    cout.precision(2);

    cout << " ------------ Meal Hut ------------\n";
    cout << "     ----      No.101       ----   \n";
    cout << "      --        York         --    \n";
    cout << "     ----      LONDON       ----   \n";
    cout << " ------------ INVOICE -------------\n";
    cout << "            Order No: " << orderNo << endl;
    cout << endl;

    for (int j = 0; j < orderAmount; ++j) {
        int itemIndex = orderedItemsCount[j];
        cout << menuList[itemIndex].itemNo << "         " << menuList[itemIndex].itemName << "     $" << menuList[itemIndex].price << endl;
        subTotal = subTotal + menuList[itemIndex].price;
    }

    double tax = subTotal * taxRate;
    double total = subTotal + tax;

    cout << endl;
    cout << "Subtotal:                     $" << subTotal << endl;
    cout << "Tax Amount (5%):              $" << tax << endl;
    cout << "Amount Due:                   $" << total << endl;
    cout << endl;
    cout << "Thank you for visiting Meal Hut.HAVE A NICE DAY!!\n";

    ofstream outFile(filename, ios::app);
    outFile << "Order No: " << orderNo << endl;
    outFile << endl;
    for (int j = 0; j < orderAmount; ++j) {
        int itemIndex = orderedItemsCount[j];
        outFile << menuList[itemIndex].itemNo << "         " << menuList[itemIndex].itemName << "     $" << menuList[itemIndex].price << endl;
    }

    outFile.setf(ios::fixed);
    outFile.precision(2);

    outFile << endl;
    outFile << "Subtotal:                     $" << subTotal << endl;
    outFile << "Tax Amount (5%):              $" << tax << endl;
    outFile << "Amount Due:                   $" << total << endl;
    outFile << endl;
    outFile << "-----------------------------------------\n";
    outFile << endl;

    outFile.close();
    orderNo++;
}

int main()
{
    string filename = "E:/bill.txt";

    MenuItem menuList[MENU_SIZE];
    int orderAmount = 0;
    int orderedItemsCount[MAX_ORDER_SIZE];

    getData(menuList);


    // NAVIGATION MENU SYSTEM
    int choice;

    do {
        cout << "\nWelcome to Meal Hut! Enjoy the best breakfast in town.\n";
        cout << endl;
        cout << "1. Breakfast Menu\n";
        cout << "2. Order Items\n";
        cout << "3. Calculate Bill\n";
        cout << "4. Exit\n";
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
            showMenu(menuList);
            break;
        case 2:
            orderAmount = orderPlace(menuList, orderedItemsCount);
            break;
        case 3:
            if (orderAmount > 0) {
                printCheck(filename, menuList, orderedItemsCount, orderAmount);
            }
            else {
                cout << "No items ordered yet.\n";
            }
            break;
        case 4:
            cout << "Thank you for visiting Meal Hut.HAVE A NICE DAY!!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            cout << endl;
            break;
        }
    } while (choice != 4);

    return 0;
}
