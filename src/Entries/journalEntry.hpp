#pragma once
#include "entry.hpp"
#include "feature.hpp"

#include <iostream>

enum class Mood {Happy, Neutral, Sad}; //Allows for a user to track their current mood


class JournalEntry : public Entry
{

 private:
    Mood mood;
    std::string time;

 public:
    JournalEntry(int id, const std::string& content,Mood mood,std::string time);
    std::string moodToString(Mood m)const; //converts and enum MOOD to a string

    Mood getMood() const;
    std::string getTime()const {return time;}


    //Terminal UI Function, controlls Termonal UI configs
    void display()const override;
};    

    Mood stringToMood(std::string& mood);
