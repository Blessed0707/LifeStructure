#include "journalEntry.hpp"
#include <iostream>


JournalEntry::JournalEntry(int id, const std::string& content,Mood mood,std::string time):
Entry(id,content),
mood(mood),
time(time)
{}



Mood JournalEntry::getMood()const{
    return mood;
}


std::string JournalEntry::moodToString(Mood m)const{
    switch(m)
    {
        case Mood::Happy:
            return "Happy";
        case Mood::Neutral:
            return "Neutral";
        case Mood::Sad:
            return "Sad";
        default:
            return "Unknown";
    }
}

void JournalEntry::display()const {
    std::cout<<"-----Journal Entry #"<<id+1<< "-----"<<std::endl;
    std::cout<<"Time: [ "<<getFormattedTime()<<" ]"<<std::endl;
    std::cout<<"Mood: [ "<<moodToString(mood)<<" ]"<<std::endl;
    std::cout<<"Entry:\n"<<content<<std::endl;
    std::cout<<"-----Journal Entry End-----"<<std::endl;

}



Mood stringToMood(std::string &mood)
{
    if(mood == "Happy")
    {
        return Mood::Happy;

    }
    else if(mood == "Neutral")
    {
        return Mood::Neutral;
    }
    else if(mood == "Sad")
    {
        return Mood::Sad;
    }
    else
    {
        std::cout<<"Mood Unknown."<<std::endl;
    }
 
}

std::string getFormattedTime()
{
    return std::string();
}
