#pragma once
#include "entry.hpp"
#include <string>

/*
    GoalEntry
    Plain data: a goal is its name, its text, and when it was written.
    It knows nothing about SQLite (see storage/entryMapping.hpp) and nothing
    about ImGui (see Containers/goalContainer.hpp).
*/
struct GoalEntry : Entry
{
    std::string goalName;

    GoalEntry() = default;
    GoalEntry(int id, std::string content, std::string time, std::string goalName = "");

    //Terminal UI display
    void display() const;
};
