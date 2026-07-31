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

class GoalContainer: public Feature
{
public:
    GoalContainer() = default;

    std::string name()const override;
    void addEntry(const GoalEntry& entry);
    const std::vector<GoalEntry>& getEntryCon();
    int getBackID()const;
    bool removeEntry(int id);
    bool render()override;

private:
    std::vector<GoalEntry> entryContainer;
    //journal variables GUI
    char contentBuffer[1024] = "";
    char contentBuffer2[1024] = "";

    bool showEntries = false;




};


