#pragma once
#include <string>

/*
    Entry
    The plain data every kind of entry shares.

    There are deliberately no virtual functions here. Nothing in the project
    ever holds an Entry* or an Entry&, so there is no base type to dispatch
    through -- the containers store concrete std::vector<GoalEntry> and
    std::vector<JournalEntry>. Feature is where this project actually needs
    polymorphism; Entry only needs to carry fields.
*/
struct Entry
{
    //Matches the SQLite rowid once the entry has been written to the database.
    //0 means "built in memory, not saved yet".
    int id = 0;

    std::string content;

    //The formatted timestamp, stored exactly as it is displayed. There is no
    //separate time_t member: keeping both meant an entry loaded from the
    //database reported the time it was loaded instead of the time it was written.
    std::string time;

    Entry() = default;
    Entry(int id, std::string content, std::string time);
};
