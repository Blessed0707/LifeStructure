#include "goalContainer.hpp"






std::string GoalContainer::name() const
{
    return "Goals";
}

void GoalContainer::addEntry(const GoalEntry &entry)
{
    entryContainer.push_back(entry);
}

bool GoalContainer::saveEntry(GoalEntry& entry)
{
    if(storage.addGoal(entry))
    {
        return true;
    }
    else{
        return false;

    }
}

bool GoalContainer::loadStorage()
{
    if(storage.loadContainer(entryContainer))
    {
        return true;
    }
    return false;
}

std::vector<GoalEntry> &GoalContainer::getEntryCon()
{
    return entryContainer;
}

int GoalContainer::getBackID() const
{
    return static_cast<int>(entryContainer.size());
}

bool GoalContainer::removeEntry(int id)
{
    //id is always +1 from index
    //check if id-1 is in bounds
    if(id - 1 >= 0 && static_cast<int>(entryContainer.size()) > id-1)
    {
        entryContainer.erase(entryContainer.begin() + id-1);
        return true;
    }
    //if id is out of bounds
    return false;
}

bool GoalContainer::render()
{
    //Title Settings
    ImGui::PushFont(fontTitle);
    ImGui::Text("Welcome To Goals");
    ImGui::PopFont();

    //Header Settings
    ImGui::PushFont(fontHeader);
    ImGui::SetWindowFontScale(.75);
    ImGui::Text("Improve Your Future one Goal at a Time");
    ImGui::SetWindowFontScale(1.0);
    ImGui::PopFont();
    ImGui::Separator();

    ImGui::PushFont(fontBody);
    ImGui::Spacing();

    ImGui::Text("Write a Goal");
    ImGui::PopFont();

    std::string Descripion = "Write Your Life Goals\n\n";
    Descripion += "Aim High\n";
    Descripion += "Achieve Higher";
    ImGui::InputTextMultiline(Descripion.c_str(), contentBuffer, IM_ARRAYSIZE(contentBuffer),ImVec2(400,100));
    ImGui::Separator();

    if (ImGui::Button("Save Entry"))
    {
        GoalEntry entry(getBackID(), contentBuffer,entry.getFormattedTime());
        addEntry(entry);//add the entry to the vector
        saveEntry(entry);//save the entry to the db
        contentBuffer[0] = '\0'; // clear the text box after saving
    }

    //show entires button that flips to either show or hide when clicked
    if (ImGui::Button(showEntries ? "Hide Entries" : "View Entries"))
    {
        showEntries = !showEntries;
    }

    if(showEntries)
    {
                  // the BeginChild/loop code from before
        ImGui::Text("Goals");
        ImGui::Separator();

        ImGui::BeginChild("EntryList", ImVec2(0, 300), true); // 0 width = fill available, 300px tall, true = draw a border

        for (const GoalEntry& entry : getEntryCon())
        {
            ImGui::Text("Goal #%d", entry.getId() + 1);
            ImGui::TextWrapped("%s", entry.getContent().c_str()); // wraps long text instead of overflowing sideways
            ImGui::Text("Time: %s", entry.getTime().c_str());
            ImGui::Separator();
        }

        ImGui::EndChild();
    }

    if(ImGui::Button("Delete Entry"))
    {
        showDeleteMenu = !showDeleteMenu;
    }

    if(showDeleteMenu)
    {
        // ImGui::Text("Enter the ID of the goal to delete:");
        // ImGui::InputInt("Goal ID", &deleteIdInput);

        // if(ImGui::Button("Confirm Delete"))
        // {
        //     if(removeEntry(deleteIdInput))
        //     {
        //         storage.deleteByID(deleteIdInput);
        //     }
        //     showDeleteMenu = false;
        // }
        // ImGui::SameLine();
        // if(ImGui::Button("Cancel"))
        // {
        //     showDeleteMenu = false;
        // }
    }

    //space before back
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0.0f, 50.0f));

    if (ImGui::Button("Back"))
    {
        return true; // tell GuiApp the user wants to leave this screen
    }
    
    return false;
}
