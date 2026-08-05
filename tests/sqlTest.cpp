#include "app.hpp"
#include "storage.hpp"
#include "table.hpp"
#include "timeUtils.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

/*
    TestSuite
    Runs a storage round trip against a scratch database, reports what passed,
    then launches the real app so this stays usable as the run harness.

    Pass --checks-only to run the checks and exit without opening a window,
    which is what you want when you just need to know whether something broke.
*/

namespace
{

int failures = 0;

void check(bool condition, const std::string& what)
{
    std::cout << (condition ? "[pass] " : "[FAIL] ") << what << std::endl;
    if (!condition)
    {
        ++failures;
    }
}

void storageRoundTrip()
{
    const std::string scratch = "storageRoundTrip.db";
    std::remove(scratch.c_str()); //start from a clean file every run

    std::cout << "\n--- storage round trip ---" << std::endl;

    Storage database(scratch);
    Table<GoalEntry> goals(database.getDB());
    Table<JournalEntry> journal(database.getDB());

    GoalEntry goal(0, "Ship LifeStructure", currentTimeString(), "Release");
    check(goals.insert(goal), "a goal inserts");
    check(goal.id > 0, "insert writes the SQLite id back onto the entry");

    JournalEntry note(0, "Refactored the storage layer", Mood::Happy, currentTimeString());
    check(journal.insert(note), "a journal entry inserts");
    check(note.id > 0, "the journal entry gets an id too");

    std::vector<GoalEntry> loadedGoals;
    check(goals.load(loadedGoals), "goals load");
    check(loadedGoals.size() == 1, "one goal comes back");

    //Loading twice used to append, so every entry appeared again on each visit.
    check(goals.load(loadedGoals) && loadedGoals.size() == 1, "load() clears before filling");

    check(loadedGoals[0].id == goal.id, "ids survive the round trip");
    check(loadedGoals[0].content == "Ship LifeStructure", "content survives the round trip");
    check(loadedGoals[0].goalName == "Release", "goalName is persisted");
    check(!loadedGoals[0].time.empty(), "the stored timestamp comes back, not the load time");
    check(loadedGoals[0].time == goal.time, "the timestamp is the one that was written");

    std::vector<JournalEntry> loadedNotes;
    check(journal.load(loadedNotes) && loadedNotes.size() == 1, "one journal entry comes back");
    check(loadedNotes[0].mood == Mood::Happy, "mood survives the round trip");

    check(goals.deleteById(goal.id), "delete by real id succeeds");
    check(!goals.deleteById(goal.id), "deleting a missing id reports failure");
    check(goals.load(loadedGoals) && loadedGoals.empty(), "the table is empty after the delete");

    //The old scheme took ids from the vector's size, so deleting a row shifted
    //the id of every row after it and the in-memory ids stopped matching the
    //database. Real rowids stay put.
    GoalEntry first(0, "First goal", currentTimeString(), "A");
    GoalEntry second(0, "Second goal", currentTimeString(), "B");
    check(goals.insert(first) && goals.insert(second), "two more goals insert");
    check(first.id != second.id, "each row gets its own id");

    check(goals.deleteById(first.id), "the first of the two deletes");
    check(goals.load(loadedGoals) && loadedGoals.size() == 1, "one goal remains");
    check(loadedGoals[0].id == second.id, "the surviving goal keeps its original id");
    check(loadedGoals[0].content == "Second goal", "the right goal survived");

    std::remove(scratch.c_str());
}

void schemaMigration()
{
    const std::string scratch = "schemaMigration.db";
    std::remove(scratch.c_str());

    std::cout << "\n--- schema migration ---" << std::endl;

    //Build a database the way an older build of the app did: no goalName column.
    {
        SQLite::Database old(scratch, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        old.exec("CREATE TABLE Goals (id INTEGER PRIMARY KEY, content TEXT, time TEXT)");
        old.exec("INSERT INTO Goals (content, time) "
                 "VALUES ('An older goal', 'Mon Jan  1 00:00:00 2024')");
    }

    //Opening it should add the missing column instead of failing on the first insert.
    Storage database(scratch);
    Table<GoalEntry> goals(database.getDB());

    std::vector<GoalEntry> loaded;
    check(goals.load(loaded), "a database from an older build still loads");
    check(loaded.size() == 1, "the existing row survived the migration");
    check(loaded[0].content == "An older goal", "its content is intact");
    check(loaded[0].time == "Mon Jan  1 00:00:00 2024", "its original timestamp is intact");
    check(loaded[0].goalName.empty(), "the new column reads back empty for old rows");

    GoalEntry added(0, "A newer goal", currentTimeString(), "Named");
    check(goals.insert(added), "new goals insert into the migrated table");
    check(goals.load(loaded) && loaded.size() == 2, "both the old and new rows load");

    std::remove(scratch.c_str());
}

void formattingChecks()
{
    std::cout << "\n--- formatting ---" << std::endl;

    check(!currentTimeString().empty(), "the current time formats to something");
    check(currentTimeString().find('\n') == std::string::npos, "the trailing newline is stripped");
    check(moodToString(Mood::Sad) == "Sad", "moodToString round trips");
    check(stringToMood("Sad") == Mood::Sad, "stringToMood round trips");

    //This used to fall off the end of the function without returning.
    check(stringToMood("not a mood") == Mood::Neutral, "an unknown mood falls back to Neutral");
}

} // namespace

int main(int argc, char** argv)
{
    bool checksOnly = false;
    for (int i = 1; i < argc; ++i)
    {
        if (std::string(argv[i]) == "--checks-only")
        {
            checksOnly = true;
        }
    }

    storageRoundTrip();
    schemaMigration();
    formattingChecks();

    std::cout << "\n" << (failures == 0 ? "All checks passed." : "Some checks FAILED.") << std::endl;

    if (!checksOnly)
    {
        std::cout << "Starting LifeStructure...\n" << std::endl;
        runLifeStructure("LifeStructure.db");
    }

    return failures == 0 ? 0 : 1;
}
