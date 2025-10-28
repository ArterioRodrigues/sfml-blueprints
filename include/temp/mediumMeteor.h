#pragma once
#include "pch.h"
#include "meteor.h"

class MediumMeteor : public Meteor {
public: 
  MediumMeteor(World& world);
  virtual int getPoints() const;
  virtual void onDestroy();
};
