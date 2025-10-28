#pragma once
#include "enemy.h"
#include "pch.h"

class Meteor : public Enemy {
public:
  Meteor(const Meteor&) = delete;
  Meteor& operator=(const Meteor&) = delete;
  using Enemy::Enemy;

  virtual bool isCollide(const Entity& other) const;
  virtual void update(sf::Time deltaTime);
};
