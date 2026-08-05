#include "timeUtils.hpp"

std::string formatTime(std::time_t t)
{
    //ctime() returns nullptr for values it cannot represent, and constructing
    //a std::string from nullptr is undefined behaviour, so the result has to
    //be checked before it is used.
    const char* text = std::ctime(&t);
    if (text == nullptr)
    {
        return "";
    }

    std::string formatted(text);
    if (!formatted.empty() && formatted.back() == '\n')
    {
        formatted.pop_back(); //remove the newline ctime() appends
    }
    return formatted;
}

std::string currentTimeString()
{
    return formatTime(std::time(nullptr));
}
