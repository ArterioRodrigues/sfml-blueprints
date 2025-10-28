#include "configuration.h"
#include "world.h"

ResourceManager<sf::Texture, int> Configuration::textures;
ResourceManager<sf::SoundBuffer, int> Configuration::soundBuffers;
ActionMap<int> Configuration::playerInputs;

World* Configuration::world = nullptr;
int Configuration::lives = 0;
int Configuration::_points = 0;

void Configuration::initialize() {
  world = new World(0, 0);
  lives = 3;
  initTextures();
  initPlayerInputs();
}

void Configuration::initTextures() {
  textures.load(Textures::Player, "media/player/ship.png");
  textures.load(Textures::PlayerSprite, "media/player/ship-sprite-sheet.png");
  textures.load(Textures::ShootPlayer, "media/player/ship.png");
} 

void Configuration::initPlayerInputs() {
  playerInputs.map(PlayerInputs::Up, Action(sf::Keyboard::Key::W));
  playerInputs.map(PlayerInputs::Right, Action(sf::Keyboard::Key::D));
  playerInputs.map(PlayerInputs::Left, Action(sf::Keyboard::Key::A));
  playerInputs.map(PlayerInputs::Shoot, Action(sf::Keyboard::Key::Space));
  playerInputs.map(PlayerInputs::Hyperspace, Action(sf::Keyboard::Key::J));
}

void Configuration::addScore(int points) {
  _points += points;
}

int Configuration::getScore() {
  return _points; 
}
