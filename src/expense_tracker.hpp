#pragma once

#include "expense.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class Expense_tracker {
    std::vector<Expense> expenses;
public:
    Expense_tracker() = default;

    void add_expense(Expense e) {
        expenses.push_back(std::move(e));
        std::cout << "\nAdd expense: [" << e.get_date() << "] " << e.get_description() << " (" << e.get_category() << ") " << e.get_amount() << "₽\n" << std::endl;
    }

    double total() {
        double total_sum = 0;
        for (size_t i = 0; i < expenses.size(); ++i) {
            total_sum += expenses[i].get_amount();
        }
        return total_sum;
    }

    double total_by_category( std::string categ) {
        double total_sum = 0;
        for (size_t i = 0; i < expenses.size(); ++i) {
            if (expenses[i].get_category() == categ) {
                total_sum += expenses[i].get_amount();
            }
        }
        return total_sum;
    }

    void print_category(std::string categ) {
        for (size_t i = 0; i < expenses.size(); ++i) {
            if (expenses[i].get_category() == categ) {
                expenses[i].print();
            }
        }
        std::cout << "Total expenses from " << categ << " category: " << total_by_category(categ) << "\n\n";

    }

    void print_all() {
        std::cout << "-----------------------------Expenses-----------------------------\n";
        for (auto& e : expenses) {
            e.print();
        }

        std::cout << "Total expenses: " << total() << "₽" << "\n\n";
    }

    bool save_to_file(std::string filename) {
        std::ofstream file(filename, std::ios::app);
        if (!file.is_open()) return false;

        if (!expenses.empty()) {
            auto e = expenses.back();
            file << e.get_date() << ";" << e.get_description() << ";" << e.get_category() << ";" << e.get_amount() << "\n";
        }
        return true;
    }

    bool load_from_file(std::string filename) {
        std::ifstream file(filename);
        std::string line, desc, cat, date, amount_str;
        double amount;
        expenses.clear();
        if (!file.is_open()) return false;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            if (line.empty()) continue;

            std::getline(ss, date, ';');
            std::getline(ss, desc, ';');
            std::getline(ss, cat, ';');
            std::getline(ss, amount_str, ';');

            try {
                amount = std::stod(amount_str);
            } catch (...) {
                continue;
            }

            try {
                expenses.emplace_back(desc, cat, date, amount);
            } catch (...) {}
        }
        return true;
    }
};
