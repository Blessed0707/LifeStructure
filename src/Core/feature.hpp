#pragma once
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>

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
    virtual std::string name()const = 0;

    //GUI Rendering Configurations
    virtual bool render() = 0;

    //called in GuiApp addFeature()
    //Allows for fonts to be used in all features
    void setFont(ImFont* body,ImFont* header,ImFont* title)
    {
        fontTitle = title;
        fontHeader = header;
        fontBody = body;
    }
};