#include "player.h"
#include "action.h"
#include "collision.h"
#include "shoot.h"
#include "shootPlayer.h"
#include "configuration.h"
#include "helpers.h"
#include "shootPlayer.h"
#include <SFML/System/Vector2.hpp>

Player::Player(World &world)
    : ActionTarget<int>(Configuration::playerInputs),
      Entity(Configuration::Textures::Player, world), _isMoving(false), _rotation(0) {

  bind(Configuration::PlayerInputs::Up, [this](const sf::Event &) { _isMoving = true; });
  bind(Configuration::PlayerInputs::Left, [this](const sf::Event &) { _rotation -= 1; });
  bind(Configuration::PlayerInputs::Right, [this](const sf::Event &) { _rotation += 1; });
  bind(Configuration::PlayerInputs::Shoot, [this](const sf::Event &) { shoot(); });
  bind(Configuration::PlayerInputs::Hyperspace, [this](const sf::Event &) { goToHyperspace(); });
}

bool Player::isCollide(const Entity &other) const {
  if (dynamic_cast<const ShootPlayer *>(&other) == nullptr) {
    // Sprite is in protected may need to changes
    return Collision::circleTest(_sprite, other._sprite);
  }
  return false;
}

void Player::shoot() {
  if (_timeSinceLastShoot > sf::seconds(0.3)) {

    _world.add(new ShootPlayer(*this));
    _timeSinceLastShoot = sf::Time::Zero;
  }
}

void Player::goToHyperspace() {
  _impulse = sf::Vector2f(0, 0);
  sf::Vector2f position = sf::Vector2f(randomTemplate<int>(0, _world.getX()), randomTemplate<int>(0, _world.getY()));
  setPosition(position);
  //_world.add(Configuration::SoundBuffers::Jump);
}

void Player::processEvent() {
  _isMoving = false;
  _rotation = 0;
  ActionTarget::processEvents();
}

void Player::update(sf::Time deltaTime) {
  float seconds = deltaTime.asSeconds();
  _timeSinceLastShoot += deltaTime;

  if (_rotation != 0) {
    sf::Angle angle = sf::degrees((_rotation > 0 ? 1 : -1) * 250 * seconds);
    _sprite.rotate(angle);
  }

  if (_isMoving) {
    float angle = _sprite.getRotation().asDegrees()/ 180 * M_PI - M_PI / 2;
    _impulse += sf::Vector2f(std::cos(angle), std::sin(angle)) * 300.f * seconds;
  }
  _sprite.move(seconds * _impulse);
}

void Player::onDestroy() {
  Entity::onDestroy();
  Configuration::lives--;
  //_world.add(Configuration::SoundBuffers::Boom);
}
