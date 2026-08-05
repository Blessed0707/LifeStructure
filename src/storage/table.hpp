#pragma once
#include <SQLiteCpp/SQLiteCpp.h>
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include "entryMapping.hpp"

/*
    Table<T>
    One table's worth of database access for any entry type that has an
    EntryMapping specialization.

    This replaces GoalStorage and JournalStorage, which were the same 85 lines
    with different column names -- deleteById() and deleteAll() were identical
    character for character. Written once here, every future feature gets them
    for free.
*/
template <typename T>
class Table
{
public:
    explicit Table(SQLite::Database& db):
        db(db),
        tableName(EntryMapping<T>::table)
    {
        db.exec("CREATE TABLE IF NOT EXISTS " + tableName +
                " (id INTEGER PRIMARY KEY, " + EntryMapping<T>::schema + ")");
        addMissingColumns();
        std::cout << "Table " << tableName << " initialized." << std::endl;
    }

    //Writes the entry and fills in entry.id with the id SQLite assigned.
    bool insert(T& entry);

    //Replaces the contents of 'out' with every row in the table.
    bool load(std::vector<T>& out);

    //Returns false if no row had that id.
    bool deleteById(int id);

    bool deleteAll();

    const std::string& name() const { return tableName; }

private:
    SQLite::Database& db;
    std::string tableName;

    void addMissingColumns();

    static std::vector<std::string> splitOnCommas(const std::string& list);
    static std::string placeholdersFor(const std::string& columns);
};

template <typename T>
bool Table<T>::insert(T& entry)
{
    try
    {
        const std::string columns = EntryMapping<T>::columns;
        SQLite::Statement statement(db,
            "INSERT INTO " + tableName + " (" + columns + ") VALUES (" +
            placeholdersFor(columns) + ")");

        EntryMapping<T>::bind(statement, entry);

        if (statement.exec() == 0)
        {
            std::cerr << "Insert into " << tableName << " affected no rows." << std::endl;
            return false;
        }

        //SQLite owns the id. Deriving ids from the vector's size meant they
        //stopped matching the database the moment a row was deleted.
        entry.id = static_cast<int>(db.getLastInsertRowid());
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Insert into " << tableName << " failed: " << e.what() << std::endl;
        return false;
    }
}

template <typename T>
bool Table<T>::load(std::vector<T>& out)
{
    //Cleared first. load() runs every time a feature screen is opened, and
    //appending meant every entry appeared again on each visit.
    out.clear();

    try
    {
        //Columns are named rather than using SELECT *, so adding a column later
        //cannot silently shift what getColumn(n) returns.
        SQLite::Statement query(db,
            "SELECT id, " + std::string(EntryMapping<T>::columns) + " FROM " + tableName);

        while (query.executeStep())
        {
            out.push_back(EntryMapping<T>::fromRow(query));
        }
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Loading " << tableName << " failed: " << e.what() << std::endl;
        return false;
    }
}

template <typename T>
bool Table<T>::deleteById(int id)
{
    try
    {
        SQLite::Statement query(db, "DELETE FROM " + tableName + " WHERE id = ?");
        query.bind(1, id);

        if (query.exec() == 0)
        {
            std::cout << "No row found in " << tableName << " with ID " << id << "." << std::endl;
            return false;
        }

        std::cout << "Deleted " << tableName << " row " << id << "." << std::endl;
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Delete from " << tableName << " failed: " << e.what() << std::endl;
        return false;
    }
}

template <typename T>
bool Table<T>::deleteAll()
{
    try
    {
        db.exec("DELETE FROM " + tableName);
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Clearing " << tableName << " failed: " << e.what() << std::endl;
        return false;
    }
}

template <typename T>
void Table<T>::addMissingColumns()
{
    //CREATE TABLE IF NOT EXISTS does nothing to a table that already exists, so
    //a database file written by an older build can be missing newer columns.
    //Without this, opening an existing LifeStructure.db would fail on insert.
    try
    {
        std::vector<std::string> existing;
        SQLite::Statement info(db, "PRAGMA table_info(" + tableName + ")");
        while (info.executeStep())
        {
            existing.push_back(info.getColumn(1).getString()); //column 1 is the name
        }

        for (const std::string& definition : splitOnCommas(EntryMapping<T>::schema))
        {
            const std::string columnName = definition.substr(0, definition.find(' '));
            if (std::find(existing.begin(), existing.end(), columnName) == existing.end())
            {
                db.exec("ALTER TABLE " + tableName + " ADD COLUMN " + definition);
                std::cout << "Added missing column '" << columnName
                          << "' to " << tableName << "." << std::endl;
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Could not check the schema of " << tableName << ": " << e.what() << std::endl;
    }
}

//Splits "content TEXT, time TEXT" into {"content TEXT", "time TEXT"}, trimming spaces.
template <typename T>
std::vector<std::string> Table<T>::splitOnCommas(const std::string& list)
{
    std::vector<std::string> parts;

    std::size_t start = 0;
    while (start <= list.size())
    {
        const std::size_t comma = list.find(',', start);
        const std::size_t end = (comma == std::string::npos) ? list.size() : comma;

        const std::size_t first = list.find_first_not_of(" \t", start);
        if (first != std::string::npos && first < end)
        {
            const std::size_t last = list.find_last_not_of(" \t", end - 1);
            parts.push_back(list.substr(first, last - first + 1));
        }

        start = end + 1;
    }

    return parts;
}

//Builds "?, ?, ?" to match the number of columns, so the two can never drift apart.
template <typename T>
std::string Table<T>::placeholdersFor(const std::string& columns)
{
    const std::size_t count = splitOnCommas(columns).size();

    std::string placeholders;
    for (std::size_t i = 0; i < count; ++i)
    {
        if (i > 0)
        {
            placeholders += ", ";
        }
        placeholders += "?";
    }
    return placeholders;
}
