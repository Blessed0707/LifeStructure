#pragma once

class Feature
{
public:
    virtual ~Feature() = default;
    virtual void menu() = 0; //abstract class
};