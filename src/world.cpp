#include "world.h"
#include "configuration.h"

World::World(float x, float y) : _x(x), _y(y) {}
World::World(const World &world) : _x(world.getX()), _y(world.getY()) {}
World::~World() { clear(); }

void World::add(Entity *entity) { _entitiesTmp.push_back(entity); }

void World::clear() {
  for (Entity *entity : _entities) {
    delete entity;
  }

  _entities.clear();

  for (Entity *entity : _entitiesTmp) {
    delete entity;
  }

  _entitiesTmp.clear();
  _sounds.clear();
}

void World::add(Configuration::SoundBuffers soundId) {
  std::unique_ptr<sf::Sound> sound(new sf::Sound(Configuration::soundBuffers.get(soundId)));
  sound->setAttenuation(0);
  sound->play();
  _sounds.emplace_back(std::move(sound));
}

bool World::isCollide(const Entity &other) {
  for (Entity *entity_ptr : _entities) {
    if (other.isCollide(*entity_ptr)) return true;
  }
  return false;
}

int World::size() { return _entities.size() + _entitiesTmp.size(); };
int World::getX() const { return _x; };
int World::getY() const { return _y; };

const std::list<Entity *> World::getEntities() const { return _entities; };

void World::update(sf::Time deltaTime) {
  if (_entitiesTmp.size() > 0) {
    _entities.merge(_entitiesTmp);
  }

  for (Entity *entityPtr : _entities) {
    Entity &entity = *entityPtr;
    entity.update(deltaTime);
    sf::Vector2f position = entity.getPosition();

    if (position.x < 0) {
      position.x = _x;
      position.y = _y - position.y;
    } else if (position.x > _x) {
      position.x = 0;
      position.y = _y - position.y;
    }

    if (position.y < 0) {
      position.y = _y;
    } else if (position.y > _y) {
      position.y = 0;
    }

    entity.setPosition(position);
  }

  const auto end = _entities.end();

  for (auto i = _entities.begin(); i != end; i++) {
    Entity &entityI = **i;
    auto j = i;
    j++;

    for (; j != end; j++) {
      Entity &entityJ = **j;

      if (entityI.isAlive() and entityI.isCollide(entityJ)) {
        entityI.onDestroy();
      }

      if (entityJ.isAlive() and entityJ.isCollide(entityI)) {
        entityJ.onDestroy();
      }
    }
  }

  for (auto i = _entities.begin(); i != _entities.end();) {
    if (not(*i)->isAlive()) {
      delete *i;
      i = _entities.erase(i);
    } else {
      i++;
    }
  }

  _sounds.remove_if([](const std::unique_ptr<sf::Sound> &sound) -> bool {
    return sound->getStatus() != sf::SoundSource::Status::Playing;
  });
};

void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (Entity *entity : _entities) {
    target.draw(*entity, states);
  }
}
