#pragma once
#include "action.h"
#include "pch.h"

class ActionTarget {
public:
  using FunctionType = std::function<void(const sf::Event &)>;
  ActionTarget();

  bool processEvent(const sf::Event &event) const;
  void processEvents() const;

  void bind(const Action &action, const FunctionType &callback);
  void unbind(const Action &action);

private:
  std::list<std::pair<Action, FunctionType>> _eventsRealTime;
  std::list<std::pair<Action, FunctionType>> _eventsPoll;
};
