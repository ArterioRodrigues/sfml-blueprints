#include "meteor.h"
#include "collision.h"


bool Meteor::isCollide(const Entity& other) const {
  if(dynamic_cast<const Meteor*>(&other) == nullptr) {
    return Collision::circleTest(_sprite, other._sprite);
  }

  return false;
}

void Meteor::update(sf::Time deltaTime) {
  float seconds = deltaTime.asSeconds();
  _sprite.move(seconds * _impulse);
}
