#include "AppController.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>

AppController::AppController(UserModel& model, IView& view)
    : model_(model), view_(view) {
    model_.addObserver([this]() { view_.render(); });
}

void AppController::run() {
    view_.render();
    while (running_) {
        std::string input;
        std::getline(std::cin, input);
        if (!input.empty()) handleCommand(input);
    }
}

void AppController::handleCommand(const std::string& command) {
    std::istringstream ss(command);
    std::string cmd;
    ss >> cmd;

    std::string args;
    std::getline(ss, args);
    if (!args.empty() && args.front() == ' ') args.erase(0, 1);

    if      (cmd == "add")    cmdAdd();
    else if (cmd == "list")   cmdList();
    else if (cmd == "search") cmdSearch(args);
    else if (cmd == "update") cmdUpdate(args);
    else if (cmd == "remove") cmdRemove(args);
    else if (cmd == "quit")   cmdQuit();
    else {
        view_.showMessage("Unknown command: " + cmd);
        view_.render();
    }
}

// ── Create ──────────────────────────────────────────────────────────────────
void AppController::cmdAdd() {
    std::string name  = view_.getUserInput("  Name  : ");
    std::string email = view_.getUserInput("  Email : ");
    if (name.empty() || email.empty()) {
        view_.showMessage("Name and email cannot be empty.");
        view_.render();
        return;
    }
    model_.addUser(name, email);
}

// ── Read (all) ───────────────────────────────────────────────────────────────
void AppController::cmdList() {
    view_.render();
}

// ── Read (search) ────────────────────────────────────────────────────────────
void AppController::cmdSearch(const std::string& args) {
    if (args.empty()) {
        view_.showMessage("Usage: search <id or name>");
        view_.render();
        return;
    }

    bool isNumeric = !args.empty() &&
        std::all_of(args.begin(), args.end(), ::isdigit);

    if (isNumeric) {
        int id = std::stoi(args);
        auto user = model_.findById(id);
        if (user) {
            view_.showMessage("Found: [" + std::to_string(user->id) + "] "
                              + user->name + " / " + user->email);
        } else {
            view_.showMessage("No user with ID " + args + ".");
        }
    } else {
        auto results = model_.findByName(args);
        if (results.empty()) {
            view_.showMessage("No users matching: " + args);
        } else {
            view_.showMessage("Search results (" + std::to_string(results.size()) + "):");
            for (const auto& u : results) {
                view_.showMessage("  [" + std::to_string(u.id) + "] "
                                  + u.name + " / " + u.email);
            }
        }
    }
    view_.render();
}

// ── Update ───────────────────────────────────────────────────────────────────
void AppController::cmdUpdate(const std::string& args) {
    if (args.empty()) {
        view_.showMessage("Usage: update <id>");
        view_.render();
        return;
    }
    int id = std::stoi(args);
    auto user = model_.findById(id);
    if (!user) {
        view_.showMessage("User " + std::to_string(id) + " not found.");
        view_.render();
        return;
    }

    view_.showMessage("Current: [" + std::to_string(user->id) + "] "
                      + user->name + " / " + user->email);
    std::string field = view_.getUserInput("  Field to update (name/email): ");
    if (field != "name" && field != "email") {
        view_.showMessage("Invalid field. Use 'name' or 'email'.");
        view_.render();
        return;
    }
    std::string value = view_.getUserInput("  New value: ");
    if (value.empty()) {
        view_.showMessage("Value cannot be empty.");
        view_.render();
        return;
    }

    if (model_.updateUser(id, field, value))
        view_.showMessage("User " + std::to_string(id) + " updated.");
    else
        view_.showMessage("Update failed.");
    view_.render();
}

// ── Delete ───────────────────────────────────────────────────────────────────
void AppController::cmdRemove(const std::string& args) {
    if (args.empty()) {
        view_.showMessage("Usage: remove <id>");
        view_.render();
        return;
    }
    int id = std::stoi(args);
    if (model_.removeUser(id))
        view_.showMessage("User " + std::to_string(id) + " removed.");
    else
        view_.showMessage("User " + std::to_string(id) + " not found.");
    view_.render();
}

// ── Quit ─────────────────────────────────────────────────────────────────────
void AppController::cmdQuit() {
    view_.showMessage("Goodbye.");
    running_ = false;
}
