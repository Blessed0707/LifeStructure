#include "Core/entry.hpp"
#include <iostream>
#include "entry.hpp"
 Entry::Entry(int id, const std::string& content) : 
    id(id), 
    timestamp(std::time(nullptr)),
    content(content) {}

int Entry::getId() const
{
    return id;
}

std::string Entry::getContent()const
{
    return content;
}

void Entry::display() const
{
    std::cout<<"[Entry #] " <<id<<std::endl;
    std::cout<<content<<std::endl;
}
std::string Entry::getFormattedTime() const
{
    std::string timeStr = std::ctime(&timestamp); //converts the time_t to a string readable as a real time value
    timeStr.pop_back(); //remove newline
    return timeStr;
}