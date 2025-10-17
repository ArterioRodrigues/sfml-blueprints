#include "../include/action.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstring>

Action::Action(const Action &other) : _event(other._event) {}

Action &Action::operator=(const Action &other) {
  _event = other._event;
  _type = other._type;
  return *this;
}

Action::Action(const sf::Keyboard::Key &key, int type) :_type(type), _event(sf::Event::KeyPressed{.code = key}) {}

Action::Action(const sf::Mouse::Button &button, int type)
    :_type(type), _event(sf::Event::MouseButtonPressed{.button = button}) {}

bool Action::operator==(const sf::Event &event) const {
  if (_event.is<sf::Event::KeyPressed>() && event.is<sf::Event::KeyPressed>()) {
    return _event.getIf<sf::Event::KeyPressed>()->code ==
           event.getIf<sf::Event::KeyPressed>()->code;
  }

  else if (_event.is<sf::Event::KeyReleased>() && event.is<sf::Event::KeyReleased>()) {
    return _event.getIf<sf::Event::KeyReleased>()->code ==
           event.getIf<sf::Event::KeyReleased>()->code;
  }

  else if (_event.is<sf::Event::MouseButtonPressed>() &&
           event.is<sf::Event::MouseButtonPressed>()) {
    return _event.getIf<sf::Event::MouseButtonPressed>()->button ==
           event.getIf<sf::Event::MouseButtonPressed>()->button;
  }

  else if (_event.is<sf::Event::MouseButtonReleased>() &&
           event.is<sf::Event::MouseButtonReleased>()) {
    return _event.getIf<sf::Event::MouseButtonReleased>()->button ==
           event.getIf<sf::Event::MouseButtonReleased>()->button;
  }
  return false;
}

bool Action::operator==(const Action &other) const { return other == _event; }

bool Action::test() const {
  if (_event.is<sf::Event::KeyPressed>()) {
    return sf::Keyboard::isKeyPressed(_event.getIf<sf::Event::KeyPressed>()->code);
  }

  if (_event.is<sf::Event::MouseButtonPressed>()) {
    return sf::Mouse::isButtonPressed(_event.getIf<sf::Event::MouseButtonPressed>()->button);
  }

  return false;
}
