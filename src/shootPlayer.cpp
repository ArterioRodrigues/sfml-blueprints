#include "shootPlayer.h"
#include "collision.h"
#include "configuration.h"

ShootPlayer::ShootPlayer(Player &other)
    : Shoot(Configuration::Textures::ShootPlayer, other._world) {

  _duration = sf::seconds(5);

  float angle = other._sprite.getRotation().asDegrees() / 180 * M_PI - M_PI / 2;
  _impulse = sf::Vector2f(std::cos(angle), std::sin(angle)) * 500.f;

  setPosition(other.getPosition());
  _sprite.setRotation(other._sprite.getRotation());
  //_world.add(Configuration::SoundBuffers::LaserPlayer);
}

bool ShootPlayer::isCollide(const Entity &entity) const {
  return Collision::circleTest(_sprite, entity._sprite);
}

void ShootPlayer::update(sf::Time deltaTime) { Shoot::update(deltaTime); }
