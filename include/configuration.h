#pragma once
#include "actionMap.h"
#include "pch.h"
#include "resourceManager.h"

class Configuration {
public:
  Configuration() = delete;
  Configuration(const Configuration &) = delete;
  Configuration &operator=(const Configuration) = delete;

  enum Textures : int {
    Player,
    PlayerSprite,
    ShootPlayer,
    ShootSaucer,
    SmallSaucer,
    BigMeteor,
    BigMeteor4,
    MediumMeteor,
    MediumMeteor4
  };
  static ResourceManager<sf::Texture, int> textures;

  enum PlayerInputs : int { Up, Left, Right, Shoot, Hyperspace };
  static ActionMap<int> playerInputs;

  enum SoundBuffers : int { Jump, Boom, Boom2, SaucerSpawn2, Explosion1, LaserPlayer, LaserEnemy };
  static ResourceManager<sf::SoundBuffer, int> soundBuffers;

  static World* world;
  static int lives;
  static void addScore(int point);
  static int getScore();
  static void initialize();

private:
  static void initTextures();
  static void initPlayerInputs();
  static int _points;
};
