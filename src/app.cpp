#include "app.hpp"
#include "GuiApp.hpp"
#include "goalContainer.hpp"
#include "journalContainer.hpp"
#include "storage.hpp"
#include "table.hpp"
#include <memory>

void runLifeStructure(const std::string& dbPath)
{
    //Declaration order matters: the features hold references to the tables, and
    //the tables hold a reference to the database, so the database has to be
    //declared first and therefore destroyed last.
    Storage database(dbPath);
    Table<JournalEntry> journalTable(database.getDB());
    Table<GoalEntry> goalTable(database.getDB());

    GuiApp app;
    app.addFeature(std::make_unique<JournalContainer>(journalTable));
    app.addFeature(std::make_unique<GoalContainer>(goalTable));

    app.run();
}
