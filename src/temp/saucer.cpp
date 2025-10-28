#include "saucer.h"
#include "smallSaucer.h"
#include "bigSaucer.h"
#include "collision.h"
#include "configuration.h"
#include "helpers.h"
#include "shootPlayer.h"
#include "world.h"

bool Saucer::isCollide(const Entity &other) const {
  if (dynamic_cast<const ShootSaucer *>(&other) == nullptr) {
    return Collision::circleTest(_sprite, other._sprite);
  }

  return false;
}

void Saucer::update(sf ::Time deltaTime) {

  float seconds = deltaTime.asSeconds();

  Entity *near = nullptr;
  float near_distance = 300;

  for (Entity *entity_ptr : _world.getEntities()) {
    if (entity_ptr != this and (dynamic_cast<const Meteor *>(entity_ptr) or
                                dynamic_cast<const ShootPlayer *>(entity_ptr))) {

      float x = getPosition().x - entity_ptr->getPosition().x;
      float y = getPosition().y - entity_ptr->getPosition().y;
      float dist = std::sqrt(x * x + y * y);
      if (dist < near_distance) {
        near_distance = dist;
        near = entity_ptr;
      }
    }

    if (near != nullptr) {
      sf::Vector2f pos = near->getPosition() - getPosition();
      float angle_rad = std::atan2(pos.y, pos.x);
      _impulse -= sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 300.f * seconds;
    } else {

      sf::Vector2f pos = Configuration::player->getPosition() - getPosition();

      float angle_rad = std::atan2(pos.y, pos.x);

      _impulse += sf::Vector2f(std::cos(angle_rad), std::sin(angle_rad)) * 100.f * seconds;
    }

    _sprite.move(seconds * _impulse);
  }
}

void Saucer::onDestroy() {
  Enemy::onDestroy();
  _world.add(Configuration::SoundBuffers::Boom2);
}

void Saucer::newSaucer(World &world) {
  Saucer *res = nullptr;
  if (randomTemplate<float>(0.f, 1.f) > Configuration::getScore() / 40000.f) {
    res = new BigSaucer(world);
  } else {
    res = new SmallSaucer(world);
  }

  res->setPosition((randomTemplate<float>(0, 1)) * world.getX(), randomTemplate<float>(0.f, (float)world.getY()));
  world.add(res);
}
