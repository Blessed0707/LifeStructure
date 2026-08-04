#include "GuiApp.hpp"
#include <iostream>

GuiApp::GuiApp()
{
    // ---- 1. Initialize GLFW and create a window ----
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // required on macOS
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE); // open maximized to fill the screen

    window = glfwCreateWindow(1920, 1080, "LifeStructure", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // enable vsync

    // ---- 2. Set up Dear ImGui ----
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();

     //Font
    fontBody = io.Fonts->AddFontFromFileTTF("assets/fonts/Chivo/ttf/Chivo-Regular.ttf",18.0f);
    fontHeader = io.Fonts->AddFontFromFileTTF("assets/fonts/Chivo/ttf/Chivo-Regular.ttf",28.0f);
    fontTitle = io.Fonts->AddFontFromFileTTF("assets/fonts/Chivo/ttf/Chivo-Bold.ttf",40.0f);



    // ---- Rounding & spacing ----
    style.WindowRounding    = 8.0f;
    style.FrameRounding     = 7.0f;
    style.GrabRounding      = 6.0f;
    style.WindowPadding     = ImVec2(20, 20);
    style.FramePadding      = ImVec2(12, 10); //Button sizes
    style.ItemSpacing       = ImVec2(10, 10);

    // ---- Color palette ----
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg]         = ImVec4(0.10f, 0.11f, 0.13f, 1.00f); // dark background
    colors[ImGuiCol_Text]             = ImVec4(0.92f, 0.92f, 0.94f, 1.00f); // near-white text

    colors[ImGuiCol_Button]           = ImVec4(0.20f, 0.45f, 0.85f, 1.00f); // accent blue
    colors[ImGuiCol_ButtonHovered]    = ImVec4(0.28f, 0.55f, 0.95f, 1.00f); // lighter on hover
    colors[ImGuiCol_ButtonActive]     = ImVec4(0.15f, 0.38f, 0.75f, 1.00f); // darker while pressed

    colors[ImGuiCol_FrameBg]          = ImVec4(0.16f, 0.17f, 0.20f, 1.00f); // input box background
    colors[ImGuiCol_FrameBgHovered]   = ImVec4(0.20f, 0.22f, 0.26f, 1.00f);
    colors[ImGuiCol_FrameBgActive]    = ImVec4(0.20f, 0.22f, 0.26f, 1.00f);

    colors[ImGuiCol_Separator]        = ImVec4(0.34f, 0.30f, 0.34f, 1.00f);

    const char* glsl_version = "#version 150";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

GuiApp::~GuiApp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void GuiApp::addFeature(std::unique_ptr<Feature> feature)
{
    feature->setFont(fontBody,fontHeader,fontTitle);
    features.push_back(std::move(feature));

}

void GuiApp::renderMainMenu()
{


    ImGui::PushFont(fontTitle);
    const char* title = "LifeStructure";
    float windowWidth = ImGui::GetWindowSize().x;
    float textWidth = ImGui::CalcTextSize(title).x;
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5);
    ImGui::Text("%s", title);
    ImGui::PopFont();
    ImGui::Separator();
    ImGui::PushFont(fontHeader);
    ImGui::Text("Productivity:");
    ImGui::PopFont();

    /*
        Underline method
    */
    ImVec2 textMin = ImGui::GetItemRectMin();
    ImVec2 textMax = ImGui::GetItemRectMax();

    ImGui::GetWindowDrawList()->AddLine(
    ImVec2(textMin.x, textMax.y),
    ImVec2(textMax.x - 10, textMax.y),
    ImGui::GetColorU32(ImGuiCol_Text), // matches current text color
    1.25f // line thickness
    );

     /*
        Underline method
    */


    for (size_t i = 0; i < features.size(); ++i)
    {
        if (i > 0)
        {
            ImGui::SameLine();
        }

        if (ImGui::Button(features[i]->name().c_str()))
            
        {
            features[i]->loadStorage();
            activeScreen = static_cast<int>(i);

        }
    }
}

void GuiApp::renderFrame()
{
    ImGui::Begin("LifeStructure");

    if (activeScreen == -1)
    {
        renderMainMenu();
    }
    else
    {
        if (features[activeScreen]->render())
        {
            activeScreen = -1; // "Back" was clicked
        }
    }
    ImGui::End();
}

void GuiApp::run()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderFrame();

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
}