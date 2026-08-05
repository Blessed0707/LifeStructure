#include "entry.hpp"
#include <utility>

Entry::Entry(int id, std::string content, std::string time):
    id(id),
    content(std::move(content)),
    time(std::move(time))
{}
