#include <iostream>
#include "Journal/journal.hpp"
#include "Core/entry.hpp"

int main()
{
    
    JournalEntry Test(1,"testing",Mood::Happy);
    
    Test.display();
    return 0;
}
