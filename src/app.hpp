#pragma once
#include <string>

/*
    Opens the database, wires every feature into the GUI, and runs until the
    window closes.

    This lives in its own file so main.cpp and the test executable can both
    start the app without duplicating the wiring.
*/
void runLifeStructure(const std::string& dbPath);
