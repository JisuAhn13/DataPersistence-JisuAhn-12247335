#pragma once
#include <string>

class IController {
public:
    virtual ~IController() = default;

    virtual void run() = 0;
    virtual void handleCommand(const std::string& command) = 0;
};
