#include "entity.h"
#include "configuration.h"

Entity::Entity(Configuration::Textures textureId, World &world)
    : _sprite(Configuration::textures.get(textureId)),_world(world) , _alive(true) {
  sf::Texture texture = Configuration::textures.get(textureId);
  _sprite.setTexture(texture);
  _sprite.setOrigin({texture.getSize().x / 2.f, texture.getSize().y / 2.f});
}

Entity::~Entity() = default;

const sf::Vector2f Entity::getPosition() const { return _sprite.getPosition(); }

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(_sprite, states);
}

bool Entity::isAlive() { return _alive; }
void Entity::onDestroy() { _alive = false; }


