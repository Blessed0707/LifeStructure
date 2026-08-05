#include "journalContainer.hpp"
#include "timeUtils.hpp"
#include <iostream>

std::string JournalContainer::name() const
{
    return "Journal";
}

std::string JournalContainer::title() const
{
    return "Welcome to your Journal";
}


// ---------------------------------------------------------------------------
// GUI hooks: the parts EntryFeature cannot know about
// ---------------------------------------------------------------------------

void JournalContainer::drawEditor()
{
    ImGui::Text("Write an Entry");

    std::string journalDescripion = "Write about your day\n";
    journalDescripion += "Think through problems\n";
    journalDescripion += "Brainstorm Ideas\n";
    journalDescripion += "Organize Your Thoughts\n";
    journalDescripion += "Improve Your Life!";

    ImGui::InputTextMultiline(journalDescripion.c_str(), contentBuffer, IM_ARRAYSIZE(contentBuffer));

    ImGui::Separator();
    ImGui::Text("Mood:");
    ImGui::RadioButton("Happy", &moodChoice, 0);
    ImGui::SameLine();
    ImGui::RadioButton("Neutral", &moodChoice, 1);
    ImGui::SameLine();
    ImGui::RadioButton("Sad", &moodChoice, 2);
}

JournalEntry JournalContainer::buildEntry() const
{
    //id 0 means "not saved yet" -- saveEntry() fills in the real one.
    return JournalEntry(0, contentBuffer, static_cast<Mood>(moodChoice), currentTimeString());
}

void JournalContainer::clearEditor()
{
    contentBuffer[0] = '\0';
}

void JournalContainer::drawEntry(const JournalEntry& entry) const
{
    ImGui::TextWrapped("%s", entry.content.c_str()); // wraps long text instead of overflowing sideways
    ImGui::Text("Mood: %s", moodToString(entry.mood).c_str());
    ImGui::Text("Time: %s", entry.time.c_str());
}


// ---------------------------------------------------------------------------
// Terminal UI: Journal only, so it is not pushed into EntryFeature
// ---------------------------------------------------------------------------

JournalEntry JournalContainer::createFromUserInput()
{
    std::string content;
    std::cout << std::endl;
    std::cout << "Enter your journal entry (Type 'Done' when finished:)" << std::endl;

    //loop until done typed
    std::string preFetch = ""; //checks what the user typed
    int count = 0;
    int len = 0;
    while (preFetch != "done" && preFetch != "Done")
    {
        std::cout << ">";
        std::getline(std::cin, preFetch);
        if (preFetch != "done" && preFetch != "Done")
        {
            if (count == 0)
            {
                content += preFetch;
                count++;
                continue;
            }
            len += static_cast<int>(preFetch.length());
            if (len > 15)
            {
                content += '\n';
                len = 0;
            }
            else
            {
                content += " ";
            }
            content += preFetch;
        }
    }

    std::cout << "Select your mood:\n";
    std::cout << "1) Happy\n2) Neutral\n3) Sad\n";
    int choice = getValidatedInt("Choice:\n>", 1, 3);

    Mood mood;
    switch (choice) {
        case 1: mood = Mood::Happy; break;
        case 2: mood = Mood::Neutral; break;
        case 3: mood = Mood::Sad; break;
        default: mood = Mood::Neutral; break; // fallback if they type something invalid
    }

    //id 0 means "not saved yet" -- saveEntry() fills in the real one.
    return JournalEntry(0, content, mood, currentTimeString());
}


void JournalContainer::menu()
{
    int choice = 0;
    do
    {
        std::cout << std::endl;
        std::cout << "-----Welcome to Your Journal-----" << std::endl;
        std::cout << "(1) Write an entry" << std::endl;
        std::cout << "(2) Display Entries" << std::endl;
        std::cout << "(9) Back" << std::endl;

        choice = getValidatedInt(">", 1, 9);

        if (choice == 1)
        {
            JournalEntry entry = createFromUserInput();
            if (saveEntry(entry))
            {
                addEntry(entry);
            }
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
    if (getEntryCon().empty())
    {
        std::cout << std::endl;
        std::cout << "No Journal Entries Yet." << std::endl;
        std::cout << std::endl;
        return;
    }

    int i = -1;
    //loop through entries
    do
    {
        //display entry, then ask to either view the next entry,
        //edit the current, or search for the next entry

        i++;
        getEntryCon()[i].display();
        std::cout << std::endl;
        std::cout << "Would you like to:" << std::endl;
        std::cout << "(1) View Next Entry" << std::endl;
        std::cout << "(2) Write an Entry" << std::endl;
        std::cout << "(3) Search For an Entry" << std::endl;
        std::cout << "(4) Edit Current Entry" << std::endl;
        std::cout << "(5) Exit Entries" << std::endl;
        int userInput = getValidatedInt(">", 1, 5);

        if (userInput == 1)
        {
            if (i == getEntryConSize() - 1)
            {
                std::cout << std::endl;
                std::cout << "No More Entries Remaining." << std::endl;
                std::cout << std::endl;
            }
            continue;
        }
        else if (userInput == 2)
        {
            JournalEntry entry = createFromUserInput();
            if (saveEntry(entry))
            {
                addEntry(entry);
            }
        }
        else if (userInput == 5)
        {
            return;
        }

        //inputHandler()

        //getEntryConSize() returns int: comparing i against the unsigned
        //size() directly made the comparison wrap.
    } while (i < getEntryConSize() - 1);
}
