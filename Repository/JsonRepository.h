#pragma once
#include "IRepository.h"
#include "../Model/User.h"
#include <string>

class JsonRepository : public IRepository<User> {
public:
    explicit JsonRepository(const std::string& filePath);
    void save(const std::vector<User>& users, int nextId) override;
    std::vector<User> load(int& nextId) override;
private:
    std::string filePath_;
};
