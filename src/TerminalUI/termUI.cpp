#include "termUI.hpp"
#include <iostream>
#include <string>

TermUI::TermUI(int userInput): userInput(userInput){}

int TermUI::getUserInput() const
{
    return userInput;
}


void TermUI::displayMenu() {
    userInput = 0;
    std::cout<<std::endl;
    std::cout<<"-----Welcome to TerminalUI-----"<<std::endl;
    std::cout<<"Options:"<<std::endl;
    std::cout<<"(1) Journal"<< std::endl;
    std::cout<<"(9) Exit TerminalUI"<<std::endl;
    userInput = getValidatedInt(">",1,9);
}

void TermUI::userInputScanner()
{
    while (userInput != 9)
    {
        this->displayMenu();

        if (userInput == 9)
            break;

        if (userInput >= 1 && userInput <= static_cast<int>(features.size()))
            features[userInput - 1]->menu();
        else
            std::cout << "Invalid option.\n";
    }
    //user enters 9
    std::cout<<"TerminalUI Exited."<<std::endl;
    std::cout<<std::endl;
}

void TermUI::addFeature(std::unique_ptr<Feature> feature)
{
    features.push_back(std::move(feature));
}
