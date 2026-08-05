#pragma once
#include "entry.hpp"
#include <string>

enum class Mood { Happy, Neutral, Sad }; //Allows a user to track their current mood

//Free functions: converting a Mood to and from text is a value in, value out
//operation, so it does not need to be a member of anything.
std::string moodToString(Mood m);
Mood stringToMood(const std::string& mood);

/*
    JournalEntry
    Plain data: the text, the mood, and when it was written.
*/
struct JournalEntry : Entry
{
    Mood mood = Mood::Neutral;

    JournalEntry() = default;
    JournalEntry(int id, std::string content, Mood mood, std::string time);

    //Terminal UI display
    void display() const;
};
