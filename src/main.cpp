#include "configuration.h"
#include "game.h"
#include "pch.h"

int main() {
  Configuration::initialize();
  Game game;
  game.run();
  return 0;
}
