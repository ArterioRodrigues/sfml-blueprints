#pragma once
#include "actionTarget.h"
#include "pch.h"

class Player : public sf::Drawable, public ActionTarget<int> {
public:
  Player(const Player &) = delete;
  Player &operator=(const Player &) = delete;
  Player();

  template <typename... Args> void setPosition(Args &&...args) {
    _shape.setPosition(std::forward<Args>(args)...);
  }

  void processEvent();
  void update(sf::Time deltaTime);

  enum PlayerInputs { Up, Left, Right }; 
  static void setDefaultsInput();

  bool _isMoving;
  int _rotation;
private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  sf::RectangleShape _shape;
  sf::Vector2f _velocity;

  static ActionMap<int> _playerInputs;
};
