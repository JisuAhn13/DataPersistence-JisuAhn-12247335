#pragma once
#include "IView.h"
#include "../Model/UserModel.h"

class ConsoleView : public IView {
public:
    explicit ConsoleView(const UserModel& model);

    void render() override;
    void showMessage(const std::string& message) override;
    std::string getUserInput(const std::string& prompt) override;

private:
    const UserModel& model_;

    void printHeader() const;
    void printUsers() const;
    void printFooter() const;
};
