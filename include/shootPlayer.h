#pragma once
#include "pch.h"
#include "shoot.h"
#include "player.h"

class ShootPlayer : public Shoot{
public:
  ShootPlayer(const ShootPlayer &) = delete;
  ShootPlayer &operator=(const ShootPlayer &) = delete;
  ShootPlayer(Player &other);

  virtual bool isCollide(const Entity& entity) const override;
  virtual void update(sf::Time deltaTime) override; 
protected:
  sf::Time _duration;
};
