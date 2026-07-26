#pragma once
#include "journalEntry.hpp"
#include "feature.hpp"
#include "entry.hpp"
#include "inputUtils.hpp"

class JournalContainer: public Feature 
{
 private:
    std::vector<JournalEntry> entryContainer;


public:
   JournalContainer();

   //takes a journal entry and adds it do the entryContainer vector.
   void addEntry(const JournalEntry&jEntry);

   //returns the entryContainer
   std::vector<JournalEntry> getEntryCon()const;

   int getBackID()const;
   JournalEntry createFromUserInput(int id);
   void menu()override;
   void displayEntries();

};

