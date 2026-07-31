#include "GuiApp.hpp"
#include "journalContainer.hpp"
#include "goalContainer.hpp"
int main()
{
    GuiApp app;
    app.addFeature(std::make_unique<JournalContainer>());
    app.addFeature(std::make_unique<GoalContainer>());

    app.run();

    return 0;
}