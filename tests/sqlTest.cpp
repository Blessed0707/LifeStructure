#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include "storage.hpp"
#include "goalStorage.hpp"
#include "goalEntry.hpp"
#include "goalContainer.hpp"
int main()
{
    // SQLite::Database db("test.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    // db.exec("CREATE TABLE IF NOT EXISTS journal_entries ("
    //         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    //         "content TEXT NOT NULL)");

    // SQLite::Statement insert(db, "INSERT INTO journal_entries (content) VALUES (?)");
    // insert.bind(1, "My first entry");
    // insert.exec();

    // SQLite::Statement query(db, "SELECT id, content FROM journal_entries");
    // while (query.executeStep())
    // {
    //     std::cout << query.getColumn(0).getInt() << ": "
    //               << query.getColumn(1).getText() << std::endl;
    // }

    Storage dbAccess("LifeStructure.db");
    GoalStorage goalTable(dbAccess.getDB());

    // GoalEntry gE(0,"Hello");
    // GoalEntry gE1(1,"Wasgud");
    // goalTable.addGoal(gE);
    // goalTable.addGoal(gE1);

    GoalContainer goals;
    goalTable.loadContainer(goals.getEntryCon());

    std::vector<GoalEntry>& ref = goals.getEntryCon();

    std::string con = ref[0].getContent();
    std::string con2 = ref[1].getContent();
    std::cout<<con<<std::endl;
    std::cout<<con2<<std::endl;

    


    return 0;
}