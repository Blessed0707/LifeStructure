#pragma once
#include <ctime>
#include <string>

/*
    Timestamp formatting.

    These are free functions rather than members of Entry because formatting a
    time is not behaviour that belongs to an entry -- a value goes in and a
    value comes out. Making it a member forced call sites to build a throwaway
    Entry just to get at it.
*/

//Converts a time_t into a human readable string.
//Returns an empty string for values ctime() cannot represent.
std::string formatTime(std::time_t t);

//The current wall-clock time, already formatted.
std::string currentTimeString();
