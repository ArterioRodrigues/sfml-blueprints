#pragma once
#include "configuration.h"
#include "pch.h"
#include "world.h"

class Entity : public sf::Drawable {
public:
  Entity(const Entity &) = delete;
  Entity &operator=(const Entity &) = delete;
  Entity(Configuration::Textures textureId, World &world);
  virtual ~Entity();

  bool isAlive();

  const sf::Vector2f getPosition() const;

  template <typename... Args> void setPosition(Args &&...args) {
    _sprite.setPosition(std::forward<Args>(args)...);
  }

  virtual bool isCollide(const Entity &entity) const = 0;
  virtual void update(sf::Time deltaTime) = 0;
  virtual void onDestroy();

  sf::Sprite _sprite;
  World &_world;

protected:
  sf::Vector2f _impulse;
  bool _alive;

private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
