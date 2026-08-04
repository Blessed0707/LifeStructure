#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include "storage.hpp"
#include "goalStorage.hpp"
#include "goalEntry.hpp"
#include "goalContainer.hpp"
#include "journalContainer.hpp"
#include "journalStorage.hpp"
#include "GuiApp.hpp"


int main()
{

    Storage dbAccess("LifeStructure.db");
    GoalStorage goalTable(dbAccess.getDB());
    JournalStorage journalTable(dbAccess.getDB());

    // goalTable.deleteEntries();
    // journalTable.deleteEntries();
    GuiApp app;
    

    app.addFeature(std::make_unique<JournalContainer>(journalTable));
    app.addFeature(std::make_unique<GoalContainer>(goalTable));

    app.run();



    return 0;
}