#pragma once
#include "entryFeature.hpp"
#include "journalEntry.hpp"
#include "inputUtils.hpp"

/*
   JournalContainer
   The Journal screen. The structural half -- holding the entries, saving,
   loading, the list, the delete box, the back button -- comes from
   EntryFeature<JournalEntry>.

   What is left is the two things Journal genuinely does differently:
     the GUI hooks below (mood buttons, and how an entry is built and drawn)
     the terminal UI, which Goals has no equivalent of and which therefore
     stays down here rather than being pushed into the shared base.
*/
class JournalContainer : public EntryFeature<JournalEntry>
{
public:
    explicit JournalContainer(Table<JournalEntry>& store) : EntryFeature<JournalEntry>(store) {}

    std::string name() const override;

    //term ui specific
    //Creates a journal entry from terminal input
    JournalEntry createFromUserInput();
    //displays all entries to terminal
    void displayEntries();
    //displays a Journal menu
    void menu() override;
    //term ui specific

protected:
    std::string title() const override;

    void drawEditor() override;
    JournalEntry buildEntry() const override;
    void clearEditor() override;
    void drawEntry(const JournalEntry& entry) const override;

private:
    int moodChoice = 0; // 0 = Happy, 1 = Neutral, 2 = Sad
};
