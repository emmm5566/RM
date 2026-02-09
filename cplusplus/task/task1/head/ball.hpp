#pragma once

#include <iostream>
#include <string>
using namespace std;

//BaseClass

class Ball
{
    protected:
    string name;

    public:
    Ball(string theName = "ball");    //base_constructor
};

//SubClass

class Projectile : public Ball
{
    protected:
    int size; //(mm)
    double price; //(rmb:yuan)
    bool fluorescent;

    public:
    Projectile(string theName = "projectile", int theSize = 0, double thePrice = 0);     //sub_constructor

    void set_projectile(string theName, int theSize, double thePrice, bool isFluorescent);
    void print_projectile();
    void set_Fluorescent();
};