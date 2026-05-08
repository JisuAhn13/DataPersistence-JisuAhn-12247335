#pragma once
#include <functional>
#include <vector>

class IModel {
public:
    virtual ~IModel() = default;

    using Observer = std::function<void()>;

    void addObserver(Observer observer) {
        observers_.push_back(std::move(observer));
    }

protected:
    void notifyObservers() const {
        for (const auto& obs : observers_) obs();
    }

private:
    std::vector<Observer> observers_;
};
