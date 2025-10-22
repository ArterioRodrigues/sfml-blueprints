#include "configuration.h"

ResourceManager<sf::Texture, int> Configuration::textures;
ActionMap<int> Configuration::playerInputs;

void Configuration::initialize() {
  initTextures();
  initPlayerInputs();
}

void Configuration::initTextures() {
  textures.load(Textures::Player, "media/player/ship.png");
  textures.load(Textures::PlayerSprite, "media/player/ship-sprite-sheet.png");
}
void Configuration::initPlayerInputs() {
  playerInputs.map(PlayerInputs::Up, Action(sf::Keyboard::Key::Up));
  playerInputs.map(PlayerInputs::Right, Action(sf::Keyboard::Key::Right));
  playerInputs.map(PlayerInputs::Left, Action(sf::Keyboard::Key::Left));
}
