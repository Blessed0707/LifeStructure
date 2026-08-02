#pragma once
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include "feature.hpp"
#include<vector>
#include <memory>


class GuiApp
{
private:
    GLFWwindow* window;
    std::vector<std::unique_ptr<Feature>> features;//Holds pointers to any feature derived class

    
     //Font
    ImFont* fontTitle = nullptr;
    ImFont* fontBody = nullptr;
    ImFont* fontHeader = nullptr;

    /*
        Screen Variables
    */
    // Tracks which "screen" we're currently drawing
    //-1 is a sentinal value which represents the main menu
    int activeScreen = -1;
     /*
        Screen Variables
    */

    /*
    Rendering
    */
    void renderMainMenu();
    /*
    Rendering
    */

public:
    GuiApp();
    ~GuiApp();
    void addFeature(std::unique_ptr<Feature> feature);
    void renderFrame();
    void run();

};