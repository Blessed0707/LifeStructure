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
    dbRef.exec("DELETE FROM" + tableName);
}

bool JournalStorage::loadContainer(std::vector<JournalEntry> &container)
{
      try
    {
        SQLite::Statement query(dbRef, "SELECT * FROM " + tableName);

        while (query.executeStep())
        {
            int id = query.getColumn(0);
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
