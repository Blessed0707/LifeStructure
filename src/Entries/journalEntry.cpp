#include "journalEntry.hpp"
#include <iostream>
#include <utility>

JournalEntry::JournalEntry(int id, std::string content, Mood mood, std::string time):
    Entry(id, std::move(content), std::move(time)),
    mood(mood)
{}

std::string moodToString(Mood m)
{
    switch (m)
    {
        case Mood::Happy:   return "Happy";
        case Mood::Neutral: return "Neutral";
        case Mood::Sad:     return "Sad";
    }
    return "Unknown";
}

Mood stringToMood(const std::string& mood)
{
    if (mood == "Happy")
    {
        return Mood::Happy;
    }
    if (mood == "Neutral")
    {
        return Mood::Neutral;
    }
    if (mood == "Sad")
    {
        return Mood::Sad;
    }

    //Every path has to return a value. Falling off the end of this function
    //was undefined behaviour whenever the stored text did not match.
    std::cerr << "Unknown mood '" << mood << "', defaulting to Neutral." << std::endl;
    return Mood::Neutral;
}

void JournalEntry::display() const
{
    //id is the real SQLite rowid, so it is printed as-is rather than offset by one.
    std::cout << "-----Journal Entry #" << id << "-----" << std::endl;
    std::cout << "Time: [ " << time << " ]" << std::endl;
    std::cout << "Mood: [ " << moodToString(mood) << " ]" << std::endl;
    std::cout << "Entry:\n" << content << std::endl;
    std::cout << "-----Journal Entry End-----" << std::endl;
}
