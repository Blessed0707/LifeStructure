#include "goalEntry.hpp"
#include <iostream>
#include <utility>

GoalEntry::GoalEntry(int id, std::string content, std::string time, std::string goalName):
    Entry(id, std::move(content), std::move(time)),
    goalName(std::move(goalName))
{}

void GoalEntry::display() const
{
    //id is the real SQLite rowid, so it is printed as-is rather than offset by one.
    std::cout << "-----Goal Entry #" << id << "-----" << std::endl;
    if (!goalName.empty())
    {
        std::cout << "Name: [ " << goalName << " ]" << std::endl;
    }
    std::cout << "Time: [ " << time << " ]" << std::endl;
    std::cout << "Entry:\n" << content << std::endl;
    std::cout << "-----Goal Entry End-----" << std::endl;
}
