#include <iostream>
#include "entry.hpp"
#include "journalEntry.hpp"
#include "journalContainer.hpp"
#include "termUI.hpp"
#include <memory>

int main()
{

    TermUI tui(0);
    tui.addFeature(std::make_unique<JournalContainer>());
    tui.userInputScanner();
   
    return 0;
}
