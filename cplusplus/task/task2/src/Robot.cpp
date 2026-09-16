#include <cstdlib>
#include "Robot.h"

//Object

Object::Object(std::string theType_, int theHealth_) : Type_(theType_), Health_(theHealth_)
{
}

bool Object::Survive() const
{
    return Health_>0;
}

std::string Object::getType_() const
{
    return Type_;
}





//Robot

Robot::Robot(std::string theType_, int theHealth_, int theATK_, double theHIT_)
 : Object(theType_, theHealth_), ATK_(theATK_), HIT_(theHIT_)
{
}

void Robot::Hit(Object& object)
{
    if(!Survive())
    {
        return;
    }

    if(!object.Survive())
    {
        return;
    }

    if((rand()%100) < (HIT_*100))
    {
        object.TakeDamage(ATK_);
    }
}

void Robot::TakeDamage(int damage)
{
    Health_ -= damage;
    if(Health_ < 0)
    {
        Health_ = 0;
    }
}





//Building

Building::Building(std::string theType_, int theHealth_)
 : Object(theType_, theHealth_)
{
}

void Building::TakeDamage(int damage)
{
    if(getType_()=="Base")
    {
        if(Invincible)
        {
            return;
        }
        if(Protected)
        {
            damage = 0;
        }
    }

    Health_ -= damage;
    if(Health_ < 0)
    {
        Health_ = 0;
    }
}
