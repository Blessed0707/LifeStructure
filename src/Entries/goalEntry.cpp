#include "goalEntry.hpp"

GoalEntry::GoalEntry(int id, const std::string &content, const std::string& time):
Entry(id,content),
time(time)
{
}

void GoalEntry::display() const
{
    std::cout<<"-----Goal Entry #"<<id+1<< "-----"<<std::endl;
    std::cout<<"Time: [ "<<getFormattedTime()<<" ]"<<std::endl;
    std::cout<<"Entry:\n"<<content<<std::endl;
    std::cout<<"-----Goal Entry End-----"<<std::endl;
}

void GoalEntry::addName(char *name)
{
    goalName = name;
}

std::string GoalEntry::getName() const
{
    return goalName;
}
