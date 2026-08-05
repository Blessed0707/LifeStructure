#pragma once
#include "imgui.h"
#include <string>

/*
    Feature
    A screen the app can show. GuiApp holds a vector<unique_ptr<Feature>> and
    drives every screen through this interface without knowing which one it is,
    so adding a feature costs GuiApp no changes at all. This is the one place
    the project genuinely needs inheritance.

    Only imgui.h is included here. The GLFW and backend headers are a GuiApp
    concern, and including them from this header dragged the whole windowing
    stack (plus SQLiteCpp) into every file that merely touched an entry.
*/
class Feature
{
protected:
    //Font
    ImFont* fontTitle = nullptr;
    ImFont* fontBody = nullptr;
    ImFont* fontHeader = nullptr;

public:
    virtual ~Feature() = default;

    //For TermUi Configs
    virtual void menu() {}

    //Returns the name of the feature
    virtual std::string name() const = 0;

    //GUI Rendering Configurations
    virtual bool render() = 0;

    //Refreshes the feature's in-memory entries from the database.
    virtual bool loadStorage()
    {
        return false;
    }

    //called in GuiApp addFeature()
    //Allows for fonts to be used in all features
    void setFont(ImFont* body, ImFont* header, ImFont* title)
    {
        fontTitle = title;
        fontHeader = header;
        fontBody = body;
    }
};
