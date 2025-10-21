#include "player.h"
#include "actionTarget.h"
#include "configuration.h"

int TURNING_ANGLE = 180;

Player::Player()
    :ActionTarget<int>(Configuration::playerInputs), _ship(Configuration::textures.get(Configuration::Textures::Player)), _isMoving(false),
      _rotation(0) {
  _ship.setOrigin(sf::Vector2f(0, 0));

  bind(Configuration::PlayerInputs::Up, [this](const sf::Event &) { _isMoving = true; });
  bind(Configuration::PlayerInputs::Left, [this](const sf::Event &) { _rotation -= 1; });
  bind(Configuration::PlayerInputs::Right, [this](const sf::Event &) { _rotation += 1; });
}


void Player::processEvent() {
  _isMoving = false;
  _rotation = 0;
  ActionTarget::processEvents();
}

void Player::update(sf::Time deltaTime) {
  float seconds = deltaTime.asSeconds();
  if (_rotation != 0) {
    sf::Angle angle = sf::degrees((_rotation > 0 ? 1 : -1) * TURNING_ANGLE * seconds);
    _ship.rotate(angle);
  }
  if (_isMoving) {
    float angle = (_ship.getRotation().asDegrees() / TURNING_ANGLE * M_PI) - (M_PI / 2);
    _velocity += sf::Vector2f(std::cos(angle), std::sin(angle)) * 60.f * seconds;
  } else {
    _velocity = sf::Vector2f(0, 0);
  }
  _ship.move(seconds * _velocity);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(_ship, states);
}
