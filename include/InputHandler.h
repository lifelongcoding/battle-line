#pragma once

#include <iostream>
#include <string>
#include <limits>


class InputHandler {
public:
    static int getChoice(int, int, const std::string&);
    static std::string getStringChoice(const std::string&);

private:
    InputHandler() = default;
};
