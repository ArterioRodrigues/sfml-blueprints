#include "smallSaucer.h"
#include "configuration.h"
#include "saucer.h"
#include <SFML/System/Time.hpp>

SmallSaucer::SmallSaucer(World &world) : Saucer(Configuration::Textures::SmallSaucer, world) {
  _timeSinceLastShoot = sf::Time::Zero;
  _world.add(Configuration::SoundBuffers::SaucerSpawn2);
  _impulse *= 400.f;
}

int SmallSaucer::getPoints() const { return 200; };

void SmallSaucer::update(sf::Time deltaTime) {
  Saucer::update(deltaTime);
  _timeSinceLastShoot += deltaTime;
  if (_timeSinceLastShoot > sf::seconds(1.5)) {
    if (Configuration::player != nullptr) {
      _world.add(new ShootSaucer(*this));
    }
    _timeSinceLastShoot = sf::Time::Zero;
  }
}
