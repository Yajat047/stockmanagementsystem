#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

class StockItem {
public:
    std::string name;
    int quantity;
    double price;

    StockItem(const std::string& itemName, int itemQuantity, double itemPrice)
        : name(itemName), quantity(itemQuantity), price(itemPrice) {}
};

class StockManager {
private:
    std::vector<StockItem> stock;

public:
    void addItem() {
        std::string name;
        int quantity;
        double price;

        std::cout << "Enter item name: ";
        std::cin >> name;
        std::cout << "Enter quantity: ";
        std::cin >> quantity;
        std::cout << "Enter price per unit: ";
        std::cin >> price;

        stock.emplace_back(name, quantity, price);
        std::cout << "Item added successfully.\n";
    }

     void displayStock() const {
        if (stock.empty()) {
            std::cout << "Stock is empty.\n";
            return;
        }

        std::cout << std::setw(20) << "Item Name" << std::setw(15) << "Quantity" << std::setw(15) << "Price\n";
        double totalPrice = 0.0;

        for (const auto& item : stock) {
            std::cout << std::setw(20) << item.name << std::setw(15) << item.quantity << std::setw(15) << item.price << '\n';
            totalPrice += item.quantity * item.price;
        }

        std::cout << "Total Price: Rs " << std::fixed << std::setprecision(2) << totalPrice << "\n";
    }

    void sellItem() {
        std::string itemName;
        int quantity;

        std::cout << "Enter item name to sell: ";
        std::cin >> itemName;

        auto it = std::find_if(stock.begin(), stock.end(),
            [&itemName](const StockItem& item) { return item.name == itemName; });

        if (it != stock.end()) {
            std::cout << "Enter quantity to sell: ";
            std::cin >> quantity;

            if (quantity <= it->quantity) {
                it->quantity -= quantity;
                std::cout << "Sold successfully.\n";
            } else {
                std::cout << "Not enough stock available.\n";
            }
        } else {
            std::cout << "Item not found in stock.\n";
        }
    }

    void updatePrice() {
        std::string itemName;
        double newPrice;

        std::cout << "Enter item name to update price: ";
        std::cin >> itemName;

        auto it = std::find_if(stock.begin(), stock.end(),
            [&itemName](const StockItem& item) { return item.name == itemName; });

        if (it != stock.end()) {
            std::cout << "Enter new price for " << itemName << ": ";
            std::cin >> newPrice;

            it->price = newPrice;
            std::cout << "Price updated successfully.\n";
        } else {
            std::cout << "Item not found in stock.\n";
        }
    }
};

int main() {
    StockManager stockManager;
    int choice;

    do {
        std::cout << "\nStock Management System\n";
        std::cout << "1. Add Item\n";
        std::cout << "2. Display Stock\n";
        std::cout << "3. Sell Item\n";
        std::cout << "4. Exit\n";
        std::cout << "5. Update Price\n"; // Added option for price update
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                stockManager.addItem();
                break;
            case 2:
                stockManager.displayStock();
                break;
            case 3:
                stockManager.sellItem();
                break;
            case 4:
                std::cout << "Exiting program.\n";
                break;
            case 5:
                stockManager.updatePrice(); // Added case for updating price
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
