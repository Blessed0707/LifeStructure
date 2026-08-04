#include "goalStorage.hpp"

void GoalStorage::addGoal(GoalEntry& entry)
{
    try
    {
        std::string prepStatement;
        prepStatement+="INSERT INTO " + tableName + " (content) VALUES (?)";
        SQLite::Statement insert(dbRef, prepStatement);
        insert.bind(1,entry.getContent());
        insert.exec();
    }
    catch (const std::exception& e) 
    {
        // The program skips the exec() return and lands here
        std::cerr << "The query failed! Error: " << e.what() << std::endl;
    }
}
//Deletes all entries from the table
void GoalStorage::deleteEntries()
{
    dbRef.exec("DELETE FROM " + tableName);
}

bool GoalStorage::deleteByID(int id)
{
    try
    {
        std::string prepStatement = "DELETE FROM " + tableName + " WHERE id = ?";
        SQLite::Statement query(dbRef,prepStatement);
        query.bind(1,id);
        int numRowsDeleted = query.exec();

        if(numRowsDeleted == 0)
        {
            std::cout<<"No row found with ID: "<< id << std::endl;
            return false;
        }
        std::cout << "Successfully deleted note ID " << id << ".\n";
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    
}

bool GoalStorage::loadContainer(std::vector<GoalEntry> &container)
{
    try
    {
        SQLite::Statement query(dbRef, "SELECT * FROM goals");

        while (query.executeStep())
        {
            // pull each column out — column order/names must match your table schema
            int id = query.getColumn(0);
            std::string content = query.getColumn(1);
            // ... whatever other columns GoalEntry needs

            container.emplace_back(id, content);
        }

        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    
}
