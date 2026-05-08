#include "JsonRepository.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

JsonRepository::JsonRepository(const std::string& filePath) : filePath_(filePath) {}

void JsonRepository::save(const std::vector<User>& users, int nextId) {
    json j;
    j["nextId"] = nextId;
    j["users"] = json::array();
    for (const auto& u : users) {
        j["users"].push_back({{"id", u.id}, {"name", u.name}, {"email", u.email}});
    }
    std::ofstream ofs(filePath_);
    if (!ofs) {
        std::cerr << "[ERROR] Cannot open file for writing: " << filePath_ << "\n";
        return;
    }
    ofs << j.dump(2);
}

std::vector<User> JsonRepository::load(int& nextId) {
    std::vector<User> users;
    std::ifstream ifs(filePath_);
    if (!ifs) { nextId = 1; return users; }

    try {
        json j;
        ifs >> j;
        nextId = j.value("nextId", 1);
        for (const auto& item : j.at("users")) {
            users.push_back({item.at("id").get<int>(),
                             item.at("name").get<std::string>(),
                             item.at("email").get<std::string>()});
        }
    } catch (const std::exception& e) {
        std::cerr << "[WARN] JSON parse error: " << e.what() << "\n";
        nextId = 1;
    }
    return users;
}
