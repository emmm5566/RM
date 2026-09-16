#include "ball.hpp"

//BaseClass

Ball::Ball(string theName) : name(theName)
{
    ;
}

//SubClass

Projectile::Projectile(string theName, int theSize, double thePrice)
     : Ball(theName), size(theSize), price(thePrice)
{
    ;
}

void Projectile::set_projectile(string theName, int theSize, double thePrice, bool isFluorescent)
{
    name = theName;
    size = theSize;
    price = thePrice;
    fluorescent = isFluorescent;
}

void Projectile::print_projectile()
{
    cout << "name: " << name << "\n"
         << "size: " << size << " mm\n"
         << "price: " << price << " yuan/piece" << endl;
}

void Projectile::set_Fluorescent()
{
    if(fluorescent)
    {
        cout << "Fluorescent Projectile" << endl;
    }
    else
    {
        cout << "Ordinary Projectiles" << endl;
    }
}