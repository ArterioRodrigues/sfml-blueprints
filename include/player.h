#pragma once
#include "actionTarget.h"
#include "pch.h"

class Player : public sf::Drawable, public ActionTarget<int> {
public:
  Player(const Player &) = delete;
  Player &operator=(const Player &) = delete;
  Player();
  Player( int frameWidth = 32, int frameHeight =32, int totalFrames = 4, int timePerFrame = 1000);
  template <typename... Args> void setPosition(Args &&...args) {
    _ship.setPosition(std::forward<Args>(args)...);
  }

  void processEvent();
  void update(sf::Time deltaTime);

  bool _isMoving;
  int _rotation;
private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  sf::Sprite _ship;
  sf::Vector2f _velocity;

  int _timePerFrame;
  int _totalFrames;
  float _animationTimer;
  int _currentFrame;
  int _frameWidth;
  int _frameHeight;
};
