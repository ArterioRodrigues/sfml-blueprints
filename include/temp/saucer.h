#pragma once
#include "pch.h"
#include "enemy.h"

class Saucer: public Enemy {
  public:

    Saucer(const Saucer&) = delete;
    Saucer& operator=(const Saucer&) = delete;

    using Enemy::Enemy;

    virtual bool isCollide(const Entity& other) const;
    virtual void update(sf::Time deltaTime);
    virtual void onDestroy();
    static void newSaucer(World& world);
};
