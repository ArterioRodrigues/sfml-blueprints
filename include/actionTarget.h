#pragma once
#include "action.h"
#include "actionMap.h"
#include "pch.h"

template <typename T = int> class ActionTarget {
public:
  ActionTarget(const ActionTarget<T> &) = delete;
  ActionTarget<T> &operator=(const ActionTarget<T> &) = delete;

  using FunctionType = std::function<void(const sf::Event &)>;
  ActionTarget(const ActionMap<T> &map) : _actionMap(map) {};

  bool processEvent(const sf::Event &event) const {
    bool result = false;
    for (auto &pair : _eventsPoll) {
      Action action = _actionMap.get(pair.first);
      if (action == event) {
        pair.second(event);
        result = true;
        break;
      }
    }
    return result;
  }

  void processEvents() const {
    for (auto &pair : _eventsRealTime) {
      Action action = _actionMap.get(pair.first);
      if (action.test()) {
        pair.second(action._event);
      }
    }
  }

  void bind(const T &key, const FunctionType &callback) {
    Action action = _actionMap.get(key);
    if (action._type == Action::Type::RealTime) {
      _eventsRealTime.emplace_back(key, callback);
    } else {
      _eventsPoll.emplace_back(key, callback);
    }
  }

  void unbind(const T &key) {
    auto removeFunction = [&key](const std::pair<Action, FunctionType> &pair) -> bool {
      return pair.first == key;
    };
    if (key & Action::Type::RealTime) {
      _eventsRealTime.remove_if(removeFunction);
    } else {
      _eventsPoll.remove_if(removeFunction);
    }
  }

private:
  std::list<std::pair<T, FunctionType>> _eventsRealTime;
  std::list<std::pair<T, FunctionType>> _eventsPoll;

  const ActionMap<T> &_actionMap;
};
