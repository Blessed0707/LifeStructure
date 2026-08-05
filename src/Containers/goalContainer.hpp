#pragma once
#include "entryFeature.hpp"
#include "goalEntry.hpp"

/*
    GoalContainer
    The Goals screen. Everything structural -- holding the entries, saving,
    loading, the list, the delete box, the back button -- comes from
    EntryFeature<GoalEntry>. What is left here is only what makes Goals
    different from any other entry screen: the wording, the name field, and
    how a goal is built and drawn.
*/
class GoalContainer : public EntryFeature<GoalEntry>
{
public:
    explicit GoalContainer(Table<GoalEntry>& store) : EntryFeature<GoalEntry>(store) {}

    std::string name() const override;

protected:
    std::string title() const override;
    std::string subtitle() const override;
    std::string entryNoun() const override;

    void drawEditor() override;
    GoalEntry buildEntry() const override;
    void clearEditor() override;
    void drawEntry(const GoalEntry& entry) const override;

private:
    //Goals have a name on top of the shared content box.
    char nameBuffer[128] = "";
};
