#include "GuiApp.hpp"
#include "journalContainer.hpp"

int main()
{
    GuiApp app;
    app.addFeature(std::make_unique<JournalContainer>());
    app.run();

    return 0;
}