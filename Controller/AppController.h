#pragma once
#include "IController.h"
#include "../Model/UserModel.h"
#include "../View/IView.h"
#include <string>

class AppController : public IController {
public:
    AppController(UserModel& model, IView& view);

    void run() override;
    void handleCommand(const std::string& command) override;

private:
    UserModel& model_;
    IView&     view_;
    bool       running_ = true;

    void cmdAdd();
    void cmdList();
    void cmdSearch(const std::string& args);
    void cmdUpdate(const std::string& args);
    void cmdRemove(const std::string& args);
    void cmdQuit();
};
