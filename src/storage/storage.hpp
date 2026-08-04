#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <string>


//storage class will hold the database
//and control access to it
class Storage
{
private:
    SQLite::Database db;


public:
    //Storage constructor initializes the database
    Storage(std::string dbPath): 
    db(dbPath,SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
    {
    }

    SQLite::Database& getDB() {return db;}

};