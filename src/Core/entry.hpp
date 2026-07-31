#pragma once
#include <iostream>
#include <ctime>
#include <string>
class Entry
{
protected:
    int id; //entry number
    time_t timestamp;
    std::string content;


public:
    Entry(int id = 0, const std::string& content = ""); 
    virtual ~Entry() = default;

    int getId() const;
    std::string getContent() const;

    
    virtual void display() const;

    //converts a time_t type timestamp into a human readable time and returns it as a string
    std::string getFormattedTime()const; 

};