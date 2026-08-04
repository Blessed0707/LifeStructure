#include "journalContainer.hpp"

std::vector<JournalEntry> JournalContainer::getEntryCon() const
{
    return entryContainer;
}

int JournalContainer::getEntryConSize() const
{
    //size of the vector represents the most recent id.
    return static_cast<int>(entryContainer.size());
}


void JournalContainer::addEntry(const JournalEntry &jEntry)
{
    entryContainer.push_back(jEntry);    
}

bool JournalContainer::saveEntry(JournalEntry& entry)
{
    if(storage.addEntry(entry))
    {
        return true;
    }
    else{
        return false;

    }
}

JournalEntry JournalContainer::createFromUserInput(int id)
{
    std::string content;
    std::cout<<std::endl;
    std::cout << "Enter your journal entry (Type 'Done' when finished:)"<<std::endl;

    //loop until done typed
    std::string preFetch = ""; //checks what the user typed
    int count = 0;
    int len = 0;
    while(preFetch != "done" && preFetch !="Done")
    {
        std::cout<<">";
        std::getline(std::cin, preFetch);
        if(preFetch != "done" && preFetch != "Done")
        {
            if(count == 0) 
            {
                content+=preFetch;
                count++;
                continue;
            }
            len += preFetch.length();
            if(len>15)
            {
                content+='\n';
                len = 0;
            }
            else
            {
                content+=" ";

            }
            content+=preFetch;
        }
        
    }

    std::cout << "Select your mood:\n";
    std::cout << "1) Happy\n2) Neutral\n3) Sad\n";
    int choice = getValidatedInt("Choice:\n>",1,3);

    Mood mood;
    switch (choice) {
        case 1: mood = Mood::Happy; break;
        case 2: mood = Mood::Neutral; break;
        case 3: mood = Mood::Sad; break;
        default: mood = Mood::Neutral; break; // fallback if they type something invalid
    }
    Entry temp;
    std::string time = temp.getFormattedTime();
    return JournalEntry(id, content, mood,time);
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
            JournalEntry entry = createFromUserInput(getEntryConSize());
            addEntry(entry);
        }
        else if (choice == 2)
        {
            this->displayEntries();
        }

    } while (choice != 9);
}

bool JournalContainer::loadStorage()
{
    if(storage.loadContainer(entryContainer))
    {
        return true;
    }
    return false;

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
            JournalEntry entry = createFromUserInput(getEntryConSize());
            addEntry(entry);
        }
        else if (userInput == 5)
        {
            return;
        }

        //inputHandler()

        
    }while(i<entryContainer.size()-1);
    
}


std::string JournalContainer::name()const
{
    return "Journal";
}

bool JournalContainer::render()
{
    ImGui::PushFont(fontTitle);
    ImGui::Text("Welcome to your Journal");
    ImGui::PopFont();
    ImGui::Separator();

    ImGui::PushFont(fontBody);
    ImGui::Text("Write an Entry");
    ImGui::PopFont();

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

    if (ImGui::Button("Save Entry"))
    {
        Mood mood = static_cast<Mood>(moodChoice);
        JournalEntry entry(getEntryConSize(), contentBuffer, mood,entry.getFormattedTime());
        addEntry(entry);
        saveEntry(entry);

        contentBuffer[0] = '\0'; // clear the text box after saving
    }
    if (ImGui::Button(showEntries ? "Hide Entries" : "View Entries"))
    {
        showEntries = !showEntries;
    }

    if (showEntries)
    {
            // the BeginChild/loop code from before
        ImGui::Text("Past Entries");
        ImGui::Separator();

        ImGui::BeginChild("EntryList", ImVec2(0, 300), true); // 0 width = fill available, 300px tall, true = draw a border

        for (const JournalEntry& entry : getEntryCon())
        {
            ImGui::Text("Entry #%d", entry.getId() + 1);
            ImGui::TextWrapped("%s", entry.getContent().c_str()); // wraps long text instead of overflowing sideways
            ImGui::Text("Mood: %s", entry.moodToString(entry.getMood()).c_str());
            ImGui::Text("Time: %s", entry.getTime().c_str());
            ImGui::Separator();
        }

        ImGui::EndChild();
    }

    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 50.0f));

    if (ImGui::Button("Back"))
    {
        return true; // tell GuiApp the user wants to leave this screen
    }

    return false; // stay on this screen
}




