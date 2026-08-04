#pragma once
#include "goalEntry.hpp"
#include "feature.hpp"
#include "entry.hpp"
#include "inputUtils.hpp"
#include <vector>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "goalStorage.hpp"

/*
    The GoalContainer class handles:
    GoalStorage use and access (Goals sql table)
    holding goalEntrys through entryContainer vector
    handling GUI implementation.
    TermUI implementation
*/
class GoalContainer: public Feature
{
public:
    GoalContainer(GoalStorage& store) : storage(store)
    {

    }

    std::string name()const override;
    void addEntry(const GoalEntry& entry);
    std::vector<GoalEntry>& getEntryCon();
    int getBackID()const;
    bool removeEntry(int id);
    bool render()override;
    //saves entry to the db storage.
    bool saveEntry(GoalEntry& entry);
    bool loadStorage()override;


private:
    std::vector<GoalEntry> entryContainer;
    GoalStorage& storage;
    //journal variables GUI
    char contentBuffer[1024] = "";
    char contentBuffer2[1024] = "";

    bool showEntries = false;
    bool showDeleteMenu = false;




};


