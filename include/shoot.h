#pragma once
#include "entity.h"
#include "pch.h"

class Shoot : public Entity {
public:
  Shoot(const Shoot &) = delete;
  Shoot &operator=(const Shoot &) = delete;
  using Entity::Entity;
  virtual void update(sf::Time deltaTime);

protected:
  sf::Time _duration;
};
