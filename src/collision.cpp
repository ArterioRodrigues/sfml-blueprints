#include "collision.h"

bool Collision::circleTest(const sf::Sprite &first, const sf::Sprite &second) {
  sf::Vector2f firstRect(first.getTextureRect().size);
  firstRect.x *= first.getScale().x;
  firstRect.y *= first.getScale().y;

  sf::Vector2f secondRect(second.getTextureRect().size);
  secondRect.x *= second.getScale().x;
  secondRect.y *= first.getScale().y;

  float radius1 = (firstRect.x + firstRect.y) / 4;
  float radius2 = (secondRect.x + secondRect.y) / 4;

  float xd = first.getPosition().x - second.getPosition().x;
  float yd = first.getPosition().y - second.getPosition().y;

  return std::sqrt(xd * xd + yd * yd) <= radius1 + radius2;
}
