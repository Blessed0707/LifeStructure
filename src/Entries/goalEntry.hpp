#pragma once
#include "entry.hpp"
#include "feature.hpp"

class GoalEntry : public Entry
{
public:
    GoalEntry(int id, const std::string& content, const std::string& time);

    //Terminal UI Controlls and Displays
    void display() const override;


    void addName(char* name);

    std::string getName()const;
    const std::string& getContent()const {return content;}
    std::string getTime()const {return time;}
private:
    std::string goalName;
    std::string time;

};