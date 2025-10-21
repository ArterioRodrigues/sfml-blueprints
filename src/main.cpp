#include "game.h"
#include "pch.h"

int main() {
  Player::setDefaultsInput();
  Game game;
  game.run();
  return 0;
}
