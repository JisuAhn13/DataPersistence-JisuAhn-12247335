#pragma once
#include <vector>

template<typename T>
class IRepository {
public:
    virtual ~IRepository() = default;
    virtual void save(const std::vector<T>& items, int nextId) = 0;
    virtual std::vector<T> load(int& nextId) = 0;
};
