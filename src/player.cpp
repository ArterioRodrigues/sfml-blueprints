#include "player.h"
#include "actionTarget.h"
#include "configuration.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

int TURNING_ANGLE = 180;

Player::Player()
    : ActionTarget<int>(Configuration::playerInputs),
      _ship(Configuration::textures.get(Configuration::Textures::Player)), _isMoving(false),
      _rotation(0) {

  _ship.setOrigin(sf::Vector2f(0, 0));

  bind(Configuration::PlayerInputs::Up, [this](const sf::Event &) { _isMoving = true; });
  bind(Configuration::PlayerInputs::Left, [this](const sf::Event &) { _rotation -= 1; });
  bind(Configuration::PlayerInputs::Right, [this](const sf::Event &) { _rotation += 1; });
}
Player::Player(int frameWidth, int frameHeight, int totalFrames, int timePerFrame)
    : ActionTarget<int>(Configuration::playerInputs),
      _ship(Configuration::textures.get(Configuration::Textures::PlayerSprite)), _isMoving(false),
      _rotation(0) {

  _currentFrame = 0;
  _frameWidth = frameWidth;
  _frameHeight = frameHeight;
  _timePerFrame = timePerFrame;
  _animationTimer = 0.0f;
  _totalFrames = totalFrames;

  _ship.setOrigin(sf::Vector2f(0, 0));
  _ship.setTextureRect(sf::IntRect({0, 0}, {32, 32}));

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

  _animationTimer += deltaTime.asMicroseconds();
  if (_isMoving && _animationTimer > _timePerFrame) {
    _animationTimer = 0.0f;
    _currentFrame = (_currentFrame + 1) % _totalFrames - 1;
    int column = _currentFrame * _frameWidth;
    _ship.setTextureRect(sf::IntRect({column, 0}, {_frameWidth, _frameHeight}));
  } else if(_isMoving) { 
    int column = _currentFrame * _frameWidth;
    _ship.setTextureRect(sf::IntRect({_currentFrame, 0}, {_frameWidth, _frameHeight}));
  }
  else {
    int column = 3 * _frameWidth;
    _ship.setTextureRect(sf::IntRect({column, 0}, {_frameWidth, _frameHeight}));
  }
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(_ship, states);
}
