#include "shoot.h"

void Shoot::update(sf::Time deltaTime) {
  float seconds = deltaTime.asSeconds();
  _sprite.move(seconds * _impulse);
  _duration -= deltaTime;
  if (_duration < sf::Time::Zero) {
    _alive = false;
  }
}
