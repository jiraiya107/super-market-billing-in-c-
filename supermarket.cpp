#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;

class Store {
public:
    int s;
    int p_id;
    char p_name[20];
    int p_price;
    int p_quantity;
    int p_discount;

    void displayHomeMenu();
    void handleUserChoice(int choice);
    void item();
    void add_item();
    void dis();
    void rmv();
    void bill();
};

// main function
int main() {
    Store store;
    int choice;
    while (true) {
        system("cls");
        store.displayHomeMenu();
        cout << "ENTER YOUR CHOICE: ";
        cin >> choice;
        store.handleUserChoice(choice);
    }
    return 0;
}

void Store::displayHomeMenu() {
    cout << "\t\t\t\t_______________________________________\n";
    cout << "\t\t\t\t               HOME                    \n";
    cout << "\t\t\t\t_______________________________________\n";
    cout << "\t\t\t\t|    1. ITEM                   |\n";
    cout << "\t\t\t\t|    2. DISPLAY ADDED ITEM     |\n";
    cout << "\t\t\t\t|    3. GENERATE BILL          |\n";
    cout << "\t\t\t\t|    4. EXIT                   |\n";
}

void Store::handleUserChoice(int choice) {
    switch (choice) {
        case 1:
            item();
            break;
        case 2:
            dis();
            break;
        case 3:
            bill();
            break;
        case 4:
            exit(0);
        default:
            cout << "ERROR: Invalid choice" << endl;
    }
}

void Store::item() {
    system("cls");
    cout << "\t\t\t\t_______________________________________\n";
    cout << "\t\t\t\t               ITEM MENU               \n";
    cout << "\t\t\t\t________________________________________\n";
    cout << "\t\t\t\t|        1. ADD ITEM           |\n";
    cout << "\t\t\t\t|        2. REMOVE ITEM        |\n";
    cout << "\t\t\t\t|        3. EXIT               |\n";
    cout << "ENTER YOUR CHOICE: ";
    cin >> s;

    switch (s) {
        case 1:
            system("cls");
            add_item();
            break;
        case 2:
            system("cls");
            rmv();
            break;
        case 3:
            exit(0);
        default:
            cout << "ERROR: Invalid choice" << endl;
    }
}

void Store::add_item() {
    cout << "Enter the Product ID: ";
    cin >> p_id;
    cout << "Enter the Product Name: ";
    cin.ignore();  // Clear the buffer
    cin.getline(p_name, 20);  // Use getline to handle spaces in product name
    cout << "Enter the Price of Product: ";
    cin >> p_price;
    cout << "Enter the Quantity of Product: ";
    cin >> p_quantity;
    cout << "Enter the Discount (in %): ";
    cin >> p_discount;

    // Save the item to file
    ofstream onfile("cart.txt", ios::app);
    if (!onfile) {
        cout << "Error opening file for writing." << endl;
        return;
    }
    onfile << p_id << " " << p_name << " " << p_price << " " << p_quantity << " " << p_discount << endl;
    onfile.close();

    cout << "PRODUCT ADDED SUCCESSFULLY" << endl;
}

void Store::dis() {
    char view;
    ifstream infile("cart.txt");
    if (!infile.is_open()) {
        cout << "No items to display!" << endl;
        return;
    }

    cout << "\n\nITEMS ADDED:\n";
    while (infile.get(view)) {
        cout << view;
    }
    infile.close();

    cout << "\n1. Go to Home Page" << endl;
    cout << "2. Exit" << endl;
    cout << "Enter Your Choice: ";
    cin >> s;

    if (s == 1) {
        system("cls");
    } else {
        exit(0);
    }
}

void Store::bill() {
    ifstream infile("cart.txt");
    if (!infile.is_open()) {
        cout << "No items to generate bill!" << endl;
        return;
    }

    float totalBill = 0;
    cout << "\n------ BILL ------\n";

    while (infile >> p_id >> p_name >> p_price >> p_quantity >> p_discount) {
        float discountAmount = (p_price * p_discount) / 100.0;  // Calculate discount
        float priceAfterDiscount = p_price - discountAmount;    // Price after discount
        float itemTotal = priceAfterDiscount * p_quantity;      // Total after discount for quantity
        totalBill += itemTotal;

        cout << "Product ID: " << p_id << endl;
        cout << "Product Name: " << p_name << endl;
        cout << "Price (per unit): " << p_price << endl;
        cout << "Quantity: " << p_quantity << endl;
        cout << "Discount: " << p_discount << "%" << endl;
        cout << "Price after Discount (per unit): " << priceAfterDiscount << endl;
        cout << "Total for this item: " << itemTotal << endl;
        cout << "------------------\n";
    }

    cout << "Total Bill: " << totalBill << endl;

    infile.close();
    cout << "\nPress any key to return to the main menu...";
    cin.ignore(); 
    cin.get(); 
}

void Store::rmv() {
    ofstream onfile("cart.txt", ios::out | ios::trunc);  // Clear the file
    onfile.close();

    cout << "\t\t\t\t_______________________________________\n";
    cout << "\t\t\t\t            DATA WAS DELETED           \n";
    cout << "\t\t\t\t_______________________________________\n";
}
