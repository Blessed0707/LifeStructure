#include "inputUtils.hpp"

int getValidatedInt(const std::string& prompt, int min, int max)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "That's not a number. Try again.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (value < min || value > max)
        {
            std::cout << "Please enter a number between " << min << " and " << max << ".\n";
            continue;
        }

        return value;
    }
}