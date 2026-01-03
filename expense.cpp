#include "expense.h"
#include "expense_tracker.h"
#include <vector>
#include <iostream>

int main() {
    Expense_tracker tracker;
    std::string filename = "expenses.csv";
    tracker.load_from_file(filename);
    int option;

    while (true) {
        std::cout << "Сhoose an option:\n";
        std::cout << "1) List of expenses\n";
        std::cout << "2) List of expenses by category\n";
        std::cout << "3) Add a new expense\n";
        std::cout << "4) Remove expense\n";
        std::cout << "5) Save and Quit\n";
        std::cout << "Enter your choose: ";
        std::cin >> option;
        std::cout << std::endl;

        switch (option) {
            case(1): { tracker.print_all(); break; }
            case(2): {
                std::string category;
                std::cout << "Enter a categoty: ";
                std::cin >> category;
                std::cout << "\n-----------------------------Expenses-----------------------------\n";
                tracker.print_category(category);
                break;
            }
            case(3): {
                std::string desc, cat, date;
                double amount;
                std::cout << "Description: "; std::cin.ignore(); std::getline(std::cin, desc);
                std::cout << "Category: "; std::getline(std::cin, cat);
                std::cout << "Date (YYYY-MM-DD): "; std::getline(std::cin, date);
                std::cout << "Amount: "; std::cin >> amount;

                try {
                    tracker.add_expense(Expense(desc, cat, date, amount));
                    tracker.save_to_file(filename);
                    std::cout << "Saved.\n";
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
                break;
            }
            case(4): break;
            case(5): return 0;

            default:
                std::cout << "Error: Choose only 1-5! \n\n";
        }
    }
    return 0;
}
