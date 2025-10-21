#include "player.h"
#include "actionTarget.h"

int TURNING_ANGLE = 180;

Player::Player()
    : ActionTarget(_playerInputs), _shape(sf::Vector2f(32, 32)), _isMoving(false), _rotation(0) {
  _shape.setFillColor(sf::Color::Blue);
  _shape.setOrigin(sf::Vector2f(0, 0));

  bind(PlayerInputs::Up, [this](const sf::Event &) { _isMoving = true; });
  bind(PlayerInputs::Left, [this](const sf::Event &) { _rotation -= 1; });
  bind(PlayerInputs::Right, [this](const sf::Event &) { _rotation += 1; });
}

void Player::setDefaultsInput() {
  _playerInputs.map(PlayerInputs::Up, Action(sf::Keyboard::Key::Up));
  _playerInputs.map(PlayerInputs::Right, Action(sf::Keyboard::Key::Right));
  _playerInputs.map(PlayerInputs::Left, Action(sf::Keyboard::Key::Left));
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
    _shape.rotate(angle);
  }
  if (_isMoving) {
    float angle = (_shape.getRotation().asDegrees() / TURNING_ANGLE * M_PI) - (M_PI / 2);
    _velocity += sf::Vector2f(std::cos(angle), std::sin(angle)) * 60.f * seconds;
  } else {
    _velocity = sf::Vector2f(0, 0);
  }
  _shape.move(seconds * _velocity);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(_shape, states);
}

ActionMap<int> Player::_playerInputs;
