#pragma once
#include "pch.h"
#include "meteor.h"

class BigMeteor : public Meteor {
public: 
  BigMeteor(World& world);
  virtual int getPoints() const;
  virtual void onDestroy();
};
