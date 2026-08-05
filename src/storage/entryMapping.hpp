#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include "goalEntry.hpp"
#include "journalEntry.hpp"

/*
    EntryMapping<T>
    Describes how one entry type maps onto a SQLite table: the table name, the
    column definitions, and how to move a T into and out of a row.

    This lives beside the database code rather than on the entry structs so the
    entries stay plain data with no knowledge of SQLite. Adding a new feature
    means adding one specialization here -- Table<T> itself is written once and
    reused, instead of copying an entire GoalStorage/JournalStorage pair.

    'columns' must list the same column names, in the same order, as 'schema'.
*/
template <typename T>
struct EntryMapping; //deliberately left undefined: a missing specialization is a compile error

template <>
struct EntryMapping<GoalEntry>
{
    static constexpr const char* table   = "Goals";
    static constexpr const char* schema  = "content TEXT, time TEXT, goalName TEXT";
    static constexpr const char* columns = "content, time, goalName";

    static void bind(SQLite::Statement& statement, const GoalEntry& entry)
    {
        statement.bind(1, entry.content);
        statement.bind(2, entry.time);
        statement.bind(3, entry.goalName);
    }

    static GoalEntry fromRow(SQLite::Statement& query)
    {
        //Column 0 is always the id; the rest follow 'columns' in order.
        return GoalEntry(query.getColumn(0).getInt(),
                         query.getColumn(1).getString(),
                         query.getColumn(2).getString(),
                         query.getColumn(3).getString());
    }
};

template <>
struct EntryMapping<JournalEntry>
{
    static constexpr const char* table   = "Journal";
    static constexpr const char* schema  = "content TEXT, mood TEXT, time TEXT";
    static constexpr const char* columns = "content, mood, time";

    static void bind(SQLite::Statement& statement, const JournalEntry& entry)
    {
        statement.bind(1, entry.content);
        statement.bind(2, moodToString(entry.mood));
        statement.bind(3, entry.time);
    }

    static JournalEntry fromRow(SQLite::Statement& query)
    {
        return JournalEntry(query.getColumn(0).getInt(),
                            query.getColumn(1).getString(),
                            stringToMood(query.getColumn(2).getString()),
                            query.getColumn(3).getString());
    }
};
