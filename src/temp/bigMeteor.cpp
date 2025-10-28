#include "bigMeteor.h"
#include "mediumMeteor.h"
#include "configuration.h"
#include "helpers.h"

BigMeteor::BigMeteor(World &world)
    : Meteor((Configuration::Textures)randomTemplate<int>(Configuration::Textures::BigMeteor,
                                                          Configuration::Textures::BigMeteor4),
             world) {
  _impulse *= 100.f;
}

int BigMeteor::getPoints() const { return 20; }

void BigMeteor::onDestroy() {
  Meteor::onDestroy();
  int nb = randomTemplate<int>(2, 3);
  for(int i = 0; i < nb; i++){ 
    MediumMeteor* meteor = new MediumMeteor(_world);
    meteor->setPosition(getPosition());
    _world.add(meteor);
  }

  _world.add(Configuration::SoundBuffers::Explosion1);
}
