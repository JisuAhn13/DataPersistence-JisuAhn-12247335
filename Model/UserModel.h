#pragma once
#include "IModel.h"
#include "User.h"
#include "../Repository/IRepository.h"
#include <optional>
#include <string>
#include <vector>

class UserModel : public IModel {
public:
    explicit UserModel(IRepository<User>& repo);

    void addUser(const std::string& name, const std::string& email);
    bool removeUser(int id);
    bool updateUser(int id, const std::string& field, const std::string& value);

    std::optional<User>  findById(int id) const;
    std::vector<User>    findByName(const std::string& query) const;
    const std::vector<User>& getUsers() const;
    int getNextId() const;

    void save();
    void reload();

private:
    IRepository<User>& repo_;
    std::vector<User>  users_;
    int                nextId_ = 1;

    void persist();
};
