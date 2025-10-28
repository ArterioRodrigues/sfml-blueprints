#pragma once
#include "pch.h"
#include "shoot.h"
#include "smallSaucer.h"

class ShootSaucer : public Shoot{
public:
  ShootSaucer(const ShootSaucer&) = delete;
  ShootSaucer& operator=(const ShootSaucer&) = delete;

  ShootSaucer();
  ShootSaucer(SmallSaucer& other);

  virtual bool isCollide(const Entity& other) const;
};
