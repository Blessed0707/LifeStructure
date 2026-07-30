#include <iostream>
#include "entry.hpp"
#include "journalEntry.hpp"
#include "journalContainer.hpp"
#include "termUI.hpp"
#include <memory>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{



        // ---- 1. Initialize GLFW and create a window ----
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
 
    // Tell GLFW/macOS which OpenGL version we want (required on Mac)
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // required on macOS


    //glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "LifeStructure", nullptr, nullptr);
    
    //window settings (option b)
    // GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    // const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    // GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "LifeStructure", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
 
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // enable vsync
 
    // ---- 2. Set up Dear ImGui ----
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
 
    ImGui::StyleColorsDark();
 
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
 
    /*
        Screen Variables
    */

    // Tracks which "screen" we're currently drawing
    bool showJournal = false;

    //journal variables
    JournalContainer journalContainer;
    char contentBuffer[1024] = "";
    int moodChoice = 0; // 0 = Happy, 1 = Neutral, 2 = Sad
 
     /*
        Screen Variables
    */

    // ---- 3. Main loop: runs once per frame until the window is closed ----
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); // handle OS/input events (clicks, keys, resize, etc.)
 
        // Start a new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
 
        // ---- This is where our widgets will go later ----
        ImGui::Begin("LifeStructure");
 
        if (!showJournal)
        {
            // ---- Main menu screen ----
            ImGui::Text("Hello, ImGui!");
 
            if (ImGui::Button("Journal"))
            {
                showJournal = true;
            }
        }
        else
        {
            // ---- Journal screen ----
            ImGui::Text("Welcome to your Journal");
            ImGui::Separator();

            ImGui::InputTextMultiline("Entry", contentBuffer, IM_ARRAYSIZE(contentBuffer));

            ImGui::Text("Mood:");
            ImGui::RadioButton("Happy", &moodChoice, 0);
            ImGui::SameLine();
            ImGui::RadioButton("Neutral", &moodChoice, 1);
            ImGui::SameLine();
            ImGui::RadioButton("Sad", &moodChoice, 2);

            if (ImGui::Button("Save Entry"))
            {
                Mood mood = static_cast<Mood>(moodChoice);
                JournalEntry entry(journalContainer.getBackID(), contentBuffer, mood);
                journalContainer.addEntry(entry);

                contentBuffer[0] = '\0'; // clear the text box after saving
            }

            ImGui::Separator();

            if (ImGui::Button("Back"))
            {
                showJournal = false;
            }
        }
 
        ImGui::End();
        // ---------------------------------------------------
 
        // Render the frame ImGui just described
        ImGui::Render();
 
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
 
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
 
        glfwSwapBuffers(window);
    }
 
    // ---- 4. Cleanup ----
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
 
    glfwDestroyWindow(window);
    glfwTerminate();


 
    return 0;

   
   
}
