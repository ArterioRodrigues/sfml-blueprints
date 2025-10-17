#pragma once
#include "actionTarget.h"
#include "pch.h"

class Player : public sf::Drawable, public ActionTarget{
public:
  Player(const Player &) = delete;
  Player &operator=(const Player &) = delete;
  Player();

  template <typename... Args> void setPosition(Args &&...args) { _shape.setPosition(std::forward<Args>(args)...); }
  void update(sf::Time deltaTime);
  bool _isMoving;
  int _rotation;

  void processEvent();
private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  sf::RectangleShape _shape;
  sf::Vector2f _velocity;
};
