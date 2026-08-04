#include "journalStorage.hpp"

bool JournalStorage::addEntry(JournalEntry &entry)
{
    try
    {
        std::string prepStatement = "INSERT INTO " + tableName + " (content,mood,time) VALUES (?,?,?)";
        SQLite::Statement insert(dbRef,prepStatement);
        insert.bind(1,entry.getContent());
        insert.bind(2,entry.moodToString(entry.getMood()));
        insert.bind(3,entry.getFormattedTime());

        int rowsAltered = insert.exec();
        if(rowsAltered == 0)
        {
            std::cout<<"Insert Failed."<<std::endl;
            return false;
        }


    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    
    return true;
    
}

void JournalStorage::deleteEntries()
{
    dbRef.exec("DELETE FROM " + tableName);
}

bool JournalStorage::deleteByID(int id)
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
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;

}

bool JournalStorage::loadContainer(std::vector<JournalEntry> &container)
{
      try
    {
        SQLite::Statement query(dbRef, "SELECT * FROM " + tableName);

        while (query.executeStep())
        {
            int id = (query.getColumn(0));
            id-=1;//subtract 1 to keep the index and ids aligned index = id -1;
            std::string content = query.getColumn(1);
            std::string mood = query.getColumn(2);
            std::string time = query.getColumn(3);


            container.emplace_back(id, content,stringToMood(mood),time);
        }

        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}
