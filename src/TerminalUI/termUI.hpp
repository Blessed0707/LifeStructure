#pragma once
#include "journalEntry.hpp"
#include "journalContainer.hpp"
#include "feature.hpp"
#include "inputUtils.hpp"

#include <memory>
#include <iostream>
#include <string>
#include <ctime>
/*
    TerminalUI
    07/23/2026

    Description:
    TerminalUI will be a representenaion of the LifeStructure app usuable entirely through terminal.
    This will be useful for testing all features before implementing GUI.
*/
class TermUI
{
    private:
    time_t timestamp;
    int userInput;
    std::vector<std::unique_ptr<Feature>> features;//Holds pointers to any feature derived class
    
    public:
    TermUI(int userInput = 0);
    ~TermUI() = default;
    void displayMenu();
    void userInputScanner();
    int getUserInput()const;

    void addFeature(std::unique_ptr<Feature> feature);
    
    void tuiJEC(JournalContainer& JC);
    
    
};