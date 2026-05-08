#include "UserModel.h"
#include <algorithm>
#include <cctype>

UserModel::UserModel(IRepository<User>& repo) : repo_(repo) {
    users_ = repo_.load(nextId_);
}

void UserModel::addUser(const std::string& name, const std::string& email) {
    users_.push_back({nextId_++, name, email});
    persist();
    notifyObservers();
}

bool UserModel::removeUser(int id) {
    auto it = std::find_if(users_.begin(), users_.end(),
        [id](const User& u) { return u.id == id; });
    if (it == users_.end()) return false;
    users_.erase(it);
    persist();
    notifyObservers();
    return true;
}

bool UserModel::updateUser(int id, const std::string& field, const std::string& value) {
    auto it = std::find_if(users_.begin(), users_.end(),
        [id](const User& u) { return u.id == id; });
    if (it == users_.end()) return false;

    if      (field == "name")  it->name  = value;
    else if (field == "email") it->email = value;
    else return false;

    persist();
    notifyObservers();
    return true;
}

std::optional<User> UserModel::findById(int id) const {
    auto it = std::find_if(users_.begin(), users_.end(),
        [id](const User& u) { return u.id == id; });
    if (it == users_.end()) return std::nullopt;
    return *it;
}

std::vector<User> UserModel::findByName(const std::string& query) const {
    std::string lq = query;
    std::transform(lq.begin(), lq.end(), lq.begin(), ::tolower);

    std::vector<User> results;
    for (const auto& u : users_) {
        std::string ln = u.name;
        std::transform(ln.begin(), ln.end(), ln.begin(), ::tolower);
        if (ln.find(lq) != std::string::npos) results.push_back(u);
    }
    return results;
}

const std::vector<User>& UserModel::getUsers() const { return users_; }
int UserModel::getNextId() const { return nextId_; }

void UserModel::save() {
    persist();
}

void UserModel::reload() {
    users_ = repo_.load(nextId_);
    notifyObservers();
}

void UserModel::persist() { repo_.save(users_, nextId_); }
