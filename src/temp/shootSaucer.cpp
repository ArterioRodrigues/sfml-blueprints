#include "shootSaucer.h"
#include "configuration.h"
#include "helpers.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>

ShootSaucer::ShootSaucer(SmallSaucer &other)
    : Shoot(Configuration::Textures::ShootSaucer, other._world) {
  _duration = sf::seconds(5);
  sf::Vector2f position = Configuration::player->getPosition() - other.getPosition();
  float accuracyLost = randomTemplate<float>(1.f, 1.f) * M_PI/((200 + Configuration::getScore())/100.f);

  float angleRadians = std::atan2(position.y, position.x) + accuracyLost;
  float angleDegrees = angleRadians * 180 / M_PI;

  _impulse = sf::Vector2f(std::cos(angleRadians), std::sin(angleRadians)) * 500.f;
  setPosition(other.getPosition());
  _sprite.setRotation(angleDegrees + 90);
  _world.add(Configuration::SoundBuffers::LaserEnemy);
}
