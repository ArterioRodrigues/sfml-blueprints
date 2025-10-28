#include "pch.h"
#include "saucer.h"
#include <SFML/System/Time.hpp>

class SmallSaucer : public Saucer {
public:
  SmallSaucer(World &world);
  virtual int getPoints() const;
  virtual void update(sf::Time deltaTime);

private:
  sf::Time _timeSinceLastShoot;
};
