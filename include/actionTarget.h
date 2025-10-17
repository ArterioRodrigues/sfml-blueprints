#pragma once
#include "action.h"
#include "actionMap.h"
#include "pch.h"

template <typename T = int> class ActionTarget {
public:
  ActionTarget(const ActionTarget<T> &) = delete;
  ActionTarget<T> &operator=(const ActionTarget<T> &) = delete;

  using FunctionType = std::function<void(const sf::Event &)>;
  ActionTarget(const ActionMap<T> &map);

  bool processEvent(const sf::Event &event) const;
  void processEvents() const;

  void bind(const T &key, const FunctionType &callback);
  void unbind(const T &key);

private:
  std::list<std::pair<T, FunctionType>> _eventsRealTime;
  std::list<std::pair<T, FunctionType>> _eventsPoll;

  const ActionMap<T> &_actionMap;
};
