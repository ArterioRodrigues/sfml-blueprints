#include "action.h"
#include "actionTarget.h"
#include "pch.h"

void testActionTarget() {
  ActionMap map;
  Action up(sf::Keyboard::Key::Up, Action::Type::Pressed);
  Action down(sf::Keyboard::Key::Down, Action::Type::Pressed);
  Action left(sf::Keyboard::Key::Left, Action::Type::Pressed);
  Action right(sf::Keyboard::Key::Right, Action::Type::Pressed);

  map.map(0, up);
  map.map(1, down);
  map.map(2, left);
  map.map(3, right);

  // ActionTarget(const ActionMap<T> &map): _actionMap(map) {};
  ActionTarget actionTarget(map);
  // void bind(const T &key, const FunctionType &callback) {
  actionTarget.bind(
      0, [](const sf::Event &event) { std::cout << "Up is calling to process" << std::endl; });
  actionTarget.bind(
      1, [](const sf::Event &event) { std::cout << "Down is calling to process" << std::endl; });
  actionTarget.bind(
      2, [](const sf::Event &event) { std::cout << "Left is calling to process" << std::endl; });
  actionTarget.bind(
      3, [](const sf::Event &event) { std::cout << "Right is calling to process" << std::endl; });

  // bool processEvent(const sf::Event &event) const {
  // void processEvents() const {
  // void unbind(const T &key) {
  actionTarget.processEvent(sf::Event::KeyPressed{.code = sf::Keyboard::Key::Up});
  // actionTarget.processEvent(sf::Event::KeyPressed{.code = sf::Keyboard::Key::Down});
  // actionTarget.processEvent(sf::Event::KeyPressed{.code = sf::Keyboard::Key::Left});
  // actionTarget.processEvent(sf::Event::KeyPressed{.code = sf::Keyboard::Key::Right});
}

void testAction() {

  double index = 0;
  // Action(const sf::Keyboard::Key &key, int type=Type::RealTime|Type::Pressed);
  Action up(sf::Keyboard::Key::Up, Action::Type::Pressed);
  Action down(sf::Keyboard::Key::Down, Action::Type::Pressed);

  // Action(const sf::Mouse::Button &button, int type=Type::RealTime|Type::Pressed);
  Action mouseRight(sf::Mouse::Button::Right, Action::Type::Pressed);
  Action mouseLeft(sf::Mouse::Button::Left, Action::Type::Pressed);

  // Action(const Action &other);
  Action up2(up);
  Action mouseRight2(mouseRight);

  // Action &operator=(const Action &other);
  if (up == down) {
    std::cout << "UP and DOWN: " << "These actions match" << std::endl;
  } else if (up == up2) {
    std::cout << "UP and UP2: " << "These actions match" << std::endl;
  }

  // Action &operator=(const Action &other);
  if (mouseRight == mouseLeft) {
    std::cout << "MOUSERGIHT and MOUSELEFT: " << "These actions match" << std::endl;
  } else if (mouseRight == mouseRight2) {
    std::cout << "MOUSERIGHT and MOUSERIGHT2: " << "These actions match" << std::endl;
  }

  while (false) {
    if (up.test()) {
      std::cout << index << " UP KEY PRESSED" << std::endl;
      index += 1;
    }

    if (down.test()) {
      std::cout << index << " DOWN KEY PRESSED" << std::endl;
      index += 1;
    }
    if (mouseLeft.test()) {
      std::cout << index << " MOUSE LEFT KEY PRESSED" << std::endl;
      index += 1;
    }
    if (mouseRight.test()) {
      std::cout << index << " MOUSE RIGHT KEY PRESSED" << std::endl;
      index += 1;
    }
  }
  // bool operator==(const sf::Event &event) const;
  sf::Event upEvent(sf::Event::KeyPressed{.code = sf::Keyboard::Key::Up});
  sf::Event downEvent(sf::Event::KeyPressed{.code = sf::Keyboard::Key::Down});

  if (up == downEvent) {
    std::cout << " UP EVENT" << std::endl;
  }
  // bool operator==(const Action &other) const;
}
