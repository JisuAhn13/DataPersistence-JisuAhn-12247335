#pragma once
#include <string>

class IView {
public:
    virtual ~IView() = default;

    virtual void render() = 0;
    virtual void showMessage(const std::string& message) = 0;
    virtual std::string getUserInput(const std::string& prompt) = 0;
};
