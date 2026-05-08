#include "ConsoleView.h"
#include <iostream>
#include <iomanip>

ConsoleView::ConsoleView(const UserModel& model) : model_(model) {}

void ConsoleView::render() {
    printHeader();
    printUsers();
    printFooter();
}

void ConsoleView::showMessage(const std::string& message) {
    std::cout << "[INFO] " << message << "\n";
}

std::string ConsoleView::getUserInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void ConsoleView::printHeader() const {
    std::cout << "\n========== User Management ==========\n";
    std::cout << std::left
              << std::setw(5)  << "ID"
              << std::setw(20) << "Name"
              << std::setw(30) << "Email"
              << "\n";
    std::cout << "-------------------------------------\n";
}

void ConsoleView::printUsers() const {
    const auto& users = model_.getUsers();
    if (users.empty()) {
        std::cout << "  (no users)\n";
        return;
    }
    for (const auto& u : users) {
        std::cout << std::left
                  << std::setw(5)  << u.id
                  << std::setw(20) << u.name
                  << std::setw(30) << u.email
                  << "\n";
    }
}

void ConsoleView::printFooter() const {
    std::cout << "=====================================\n";
    std::cout << "Commands:\n";
    std::cout << "  add                 - Create new user\n";
    std::cout << "  list                - Read all users\n";
    std::cout << "  search <id|name>    - Read by ID or name\n";
    std::cout << "  update <id>         - Update a user field\n";
    std::cout << "  remove <id>         - Delete a user\n";
    std::cout << "  quit                - Exit\n";
    std::cout << "> ";
}
