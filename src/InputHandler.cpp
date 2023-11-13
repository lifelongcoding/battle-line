#include "InputHandler.h"


int InputHandler::getChoice(int minChoice, int maxChoice, const std::string &prompt) {
    int choice;
    do {
        std::cout << prompt << std::endl;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice < minChoice || choice > maxChoice);

    return choice;
}

std::string InputHandler::getStringChoice(const std::string &prompt) {
    std::cout << prompt;
    std::string f;
    std::cin >> f;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return f;
}
