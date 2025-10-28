#pragma once
#include "actionTarget.h"
#include "entity.h"
#include "pch.h"
#include "world.h"

class Player : public Entity, public ActionTarget<int> {
public:
  Player(const Player &) = delete;
  Player &operator=(const Player &) = delete;
  Player(World &world);

  virtual bool isCollide(const Entity &other) const override;
  virtual void update(sf::Time deltaTime) override;

  void processEvent();
  void shoot();

  void goToHyperspace();
  virtual void onDestroy() override;


  bool _isMoving;
  int _rotation;
private:
  sf::Time _timeSinceLastShoot;
};
