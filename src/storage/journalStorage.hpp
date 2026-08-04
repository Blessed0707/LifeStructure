#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <string>
#include <vector>
#include "journalEntry.hpp"

enum class Mood2 {Happy, Neutral, Sad}; //Allows for a user to track their current mood


class JournalStorage
{

private:
    friend class GoalContainer;
    std::string tableName;
    SQLite::Database& dbRef;
public:
    //Creates the Goals table
    JournalStorage(SQLite::Database& db): tableName("Journal"),dbRef(db)
    {
        std::string prepStatement = "CREATE TABLE IF NOT EXISTS " + tableName + "( id INTEGER PRIMARY KEY, ";
        prepStatement +="content TEXT,mood TEXT, time TEXT)";
        dbRef.exec(prepStatement);
        std::cout<<"Table "<<tableName<<" initialized."<<std::endl;
    }

    //adds a journal entry to the db table
    bool addEntry(JournalEntry& entry);
    //deleted all entries in the table
    void deleteEntries();

    bool deleteByID(int id);


    bool loadContainer(std::vector<JournalEntry>& container);



};