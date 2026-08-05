#include "goalContainer.hpp"
#include "timeUtils.hpp"

std::string GoalContainer::name() const
{
    return "Goals";
}

std::string GoalContainer::title() const
{
    return "Welcome To Goals";
}

std::string GoalContainer::subtitle() const
{
    return "Improve Your Future one Goal at a Time";
}

std::string GoalContainer::entryNoun() const
{
    return "Goal";
}

void GoalContainer::drawEditor()
{
    ImGui::Text("Write a Goal");

    ImGui::InputText("Goal Name", nameBuffer, IM_ARRAYSIZE(nameBuffer));

    std::string description = "Write Your Life Goals\n\n";
    description += "Aim High\n";
    description += "Achieve Higher";
    ImGui::InputTextMultiline(description.c_str(), contentBuffer, IM_ARRAYSIZE(contentBuffer), ImVec2(400, 100));
}

GoalEntry GoalContainer::buildEntry() const
{
    //id 0 means "not saved yet" -- saveEntry() fills in the real one.
    return GoalEntry(0, contentBuffer, currentTimeString(), nameBuffer);
}

void GoalContainer::clearEditor()
{
    contentBuffer[0] = '\0';
    nameBuffer[0] = '\0';
}

void GoalContainer::drawEntry(const GoalEntry& entry) const
{
    if (!entry.goalName.empty())
    {
        ImGui::Text("Name: %s", entry.goalName.c_str());
    }
    ImGui::TextWrapped("%s", entry.content.c_str()); // wraps long text instead of overflowing sideways
    ImGui::Text("Time: %s", entry.time.c_str());
}
