#include "journalEntry.hpp"
#include <iostream>


JournalEntry::JournalEntry(int id, const std::string& content,Mood mood):
Entry(id,content),
mood(mood)
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





