#pragma once
#include "journalEntry.hpp"
#include "feature.hpp"
#include "entry.hpp"
#include "inputUtils.hpp"
#include <vector>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include "journalStorage.hpp"

/*
   JournalContainer 
   Description:
      The Journal Container class is a container for all things relating to a Journal or a Journal Feature
      implementation.
      This class handles multiple important tasks including:
      Handling and managing JournalEntries via entryContainer Vector
      Holding and accessing the JournalStorage
      Controlling the Journal Rendering Settings for the UI
      Terminal UI integration
*/
class JournalContainer: public Feature 
{
 private:
   //the entryContaier vector stores JournalEntries.
   std::vector<JournalEntry> entryContainer;
   //Holds a reference to a storage variable which holds the LifeStructure.DB table
   //Journal Entry class works with the 'Journal' table specifically
   JournalStorage& storage;
      
   //journal variables GUI
   char contentBuffer[1024] = "";
   char contentBuffer2[1024] = "";
   int moodChoice = 0; // 0 = Happy, 1 = Neutral, 2 = Sad
   bool showEntries = 0;
   //---------------------

public:
    JournalContainer(JournalStorage& store) : storage(store)
    {

    }

   //takes a journal entry and adds it do the entryContainer vector.
   void addEntry(const JournalEntry&jEntry);

   //saveEntry calls the Storage classes addEntry method to save the content of a Journal Entry
   //to the 'Journal' table.
   bool saveEntry(JournalEntry& entry);

   //returns the entryContainer vector
   std::vector<JournalEntry> getEntryCon()const;

   //returns the size of the entryContainer vector
   int getEntryConSize()const;


   //term ui specific
   //Creates a journal entry from terminal input
   JournalEntry createFromUserInput(int id); 
   //disolays all entries to terminal
   void displayEntries();
   //displays a Journal menu
   void menu()override;
   //term ui specific

   //Load storage calls the Storage classes loadContainer() method to load the information
   //from the core LifeStorage.db Journal table, into the entryContainer vector
   bool loadStorage()override;

   //GUI
   std::string name()const override;
   bool render() override;

   

};

