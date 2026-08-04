#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <string>
#include <vector>
#include "goalEntry.hpp"

class GoalStorage
{

private:
    std::string tableName;
    SQLite::Database& dbRef;
public:
    //Creates the Goals table
    GoalStorage(SQLite::Database& db): tableName("Goals"),dbRef(db)
    {
        std::string statement = "CREATE TABLE IF NOT EXISTS " + tableName + "( id INTEGER PRIMARY KEY, ";
        statement +="content TEXT)";
        dbRef.exec(statement);
        std::cout<<"Table "<<tableName<<" initialized."<<std::endl;
    }

    void addGoal(GoalEntry& entry);
    void deleteEntries();
    bool deleteByID(int id);


    bool loadContainer(std::vector<GoalEntry>& container);



};