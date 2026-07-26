#include "journalContainer.hpp"

JournalContainer::JournalContainer()
{

}


std::vector<JournalEntry> JournalContainer::getEntryCon() const
{
    return entryContainer;
}

int JournalContainer::getBackID() const
{
    //size of the vector represents the most recent id.
    return entryContainer.size();
}


void JournalContainer::addEntry(const JournalEntry &jEntry)
{
    entryContainer.push_back(jEntry);    
}

JournalEntry JournalContainer::createFromUserInput(int id)
{
    std::string content;
    std::cout<<std::endl;
    std::cout << "Enter your journal entry: ";
    std::getline(std::cin, content);

    std::cout << "Select your mood:\n";
    std::cout << "1) Happy\n2) Neutral\n3) Sad\n";
    int choice = getValidatedInt("Choice:\n>",1,3);
   // clears leftover newline so future getline calls work correctly

    Mood mood;
    switch (choice) {
        case 1: mood = Mood::Happy; break;
        case 2: mood = Mood::Neutral; break;
        case 3: mood = Mood::Sad; break;
        default: mood = Mood::Neutral; break; // fallback if they type something invalid
    }

    return JournalEntry(id, content, mood);
}


void JournalContainer::menu()
{
    int choice = 0;
    do
    {
        std::cout<<std::endl;
        std::cout << "-----Welcome to Your Journal-----" << std::endl;
        std::cout << "(1) Write an entry" << std::endl;
        std::cout << "(2) Display Entries" << std::endl;
        std::cout << "(9) Back" << std::endl;

        choice = getValidatedInt(">", 1, 9);

        if (choice == 1)
        {
            JournalEntry entry = createFromUserInput(getBackID());
            addEntry(entry);
        }
        else if (choice == 2)
        {
            this->displayEntries();
        }

    } while (choice != 9);
}

void JournalContainer::displayEntries()
{
    //display entry 1;
    //ask user to advance to entry 2, 3 etc
    //ask user to search by id

    //if vector empty go back to menu()
    if(entryContainer.empty())
    {
        std::cout<<std::endl;
        std::cout<<"No Journal Entries Yet."<<std::endl;
        std::cout<<std::endl;
        return;
    }
    int i = -1;
    //loop through entries
    do
    {
        //display entry, then ask to either view the next entry,
        //edit the current, or search for the next entry

        i++;
        entryContainer[i].display(); 
        //std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<"Would you like to:"<<std::endl;
        std::cout<<"(1) View Next Entry"<<std::endl;
        std::cout<<"(2) Write an Entry"<<std::endl;
        std::cout<<"(3) Search For an Entry"<<std::endl;
        std::cout<<"(4) Edit Current Entry"<<std::endl; 
        std::cout<<"(5) Exit Entries"<<std::endl;
        int userInput = getValidatedInt(">",1,5);

        if(userInput == 1)
        {
            if(i == static_cast<int>(entryContainer.size()-1))
            {
                std::cout<<std::endl;
                std::cout<<"No More Entries Remaining."<<std::endl;
                std::cout<<std::endl;
            }
            continue;

        }
        else if (userInput == 2)
        {
            JournalEntry entry = createFromUserInput(getBackID());
            addEntry(entry);
        }
        else if (userInput == 5)
        {
            return;
        }

        //inputHandler()

        
    }while(i<entryContainer.size()-1);
    
}


