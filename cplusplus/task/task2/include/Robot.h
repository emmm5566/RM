#pragma once

#include <string>

class Object
{
public:
    int Health_;

    Object(std::string theType_ = "Unknown", int theHealth_ = 0);
    virtual ~Object() = default;

    bool Survive() const;
    std::string getType_() const;

    virtual void TakeDamage(int damage) {}

protected:
    std::string Type_;
};

class Robot : public Object
{
public:
    Robot(std::string theType_ = "Unknown", int theHealth_ = 0, int theATK_ = 0, double theHIT_ = 0);

    void Hit(Object& object);

    void TakeDamage(int damage) override;

protected:
    int ATK_;
    double HIT_;
};

class Building : public Object
{   
public:
    bool Invincible;
    bool Protected;

    Building(std::string theType_ = "Unknown", int theHealth_ = 0);

    void TakeDamage(int damage) override;

};