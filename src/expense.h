#pragma once

#include <stdexcept>
#include <string>
#include <iostream>

class Expense {
    std::string description;
    std::string category;
    std::string date;
    double amount;
public:
    explicit Expense(std::string des, std::string cat, std::string dat, double amo)
    : description(std::move(des)), category(std::move(cat)), date(std::move(dat)), amount(std::move(amo)) {
        if (description.empty()) throw std::invalid_argument("Description must be not empty");
        if (category.empty()) throw std::invalid_argument("Category must be not empty");
        if (date.empty()) throw std::invalid_argument("Date must be not empty");
        if (amount < 0) throw std::invalid_argument("Amount must be positive");
    }

    std::string get_description() { return description; }
    std::string get_category() { return category; }
    std::string get_date() { return date; }
    double get_amount() { return amount; }

    void print() {
        std::cout << "[" << date << "] " << description << " (" << category << ") " << amount << "₽" << std::endl;
    }
};
