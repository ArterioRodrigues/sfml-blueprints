#pragma once
#include "pch.h"
#include "player.h"

class Game {
public:
  Game(const Game &) = delete;
  Game &operator=(const Game &) = delete;
  Game(int x = 800, int y = 600);
  void run(int frame_per_seconds = 6000);

private:
  void processEvents();
  void update(sf::Time deltaTime);
  void render();

  sf::RenderWindow _window;
  Player _player;
  int _x;
  int _y;
};
