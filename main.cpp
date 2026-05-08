#include "Model/UserModel.h"
#include "View/ConsoleView.h"
#include "Controller/AppController.h"
#include "Repository/JsonRepository.h"

int main() {
    JsonRepository repo("users.json");
    UserModel      model(repo);
    ConsoleView    view(model);
    AppController  controller(model, view);

    controller.run();
    return 0;
}
