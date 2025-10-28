#include "mediummeteor.h"
#include "helpers.h"

MediumMeteor::MediumMeteor(World &world)
    : Meteor((Configuration::Textures)randomTemplate<int>(Configuration::Textures::MediumMeteor,
                                                          Configuration::Textures::MediumMeteor4),
             world) {
  _impulse *= 100.f;
}

int MediumMeteor::getPoints() const { return 20; }

void MediumMeteor::onDestroy() {
  Meteor::onDestroy();
  int nb = randomTemplate<int>(2, 3);
  for(int i = 0; i < nb; i++){ 
    MediumMeteor* meteor = new MediumMeteor(_world);
    meteor->setPosition(getPosition());
    _world.add(meteor);
  }

  _world.add(Configuration::SoundBuffers::Explosion1);
}
