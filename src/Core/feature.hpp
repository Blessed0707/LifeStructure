#pragma once

#include <string>
class Feature
{
public:
    virtual ~Feature() = default;
    virtual void menu() = 0; //abstract class
    virtual std::string name()const = 0;
    virtual bool render() = 0;
};