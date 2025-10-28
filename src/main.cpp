#include "configuration.h"
#include "pch.h"
#include "game.h"

int main() {
  Configuration::initialize();
  Game game;
  game.run();
  return 0;
}
