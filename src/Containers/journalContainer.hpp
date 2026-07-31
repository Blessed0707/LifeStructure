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

class JournalContainer: public Feature 
{
 private:
    std::vector<JournalEntry> entryContainer;
        
    //journal variables GUI
    char contentBuffer[1024] = "";
    int moodChoice = 0; // 0 = Happy, 1 = Neutral, 2 = Sad

    bool showEntries = 0;

public:
   JournalContainer();

   //takes a journal entry and adds it do the entryContainer vector.
   void addEntry(const JournalEntry&jEntry);

   //returns the entryContainer
   std::vector<JournalEntry> getEntryCon()const;

   int getBackID()const;
   JournalEntry createFromUserInput(int id); //term ui specific
   void displayEntries();

   void menu()override;

   //GUI
   std::string name()const override;
   bool render() override;

};

