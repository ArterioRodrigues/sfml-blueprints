#include "actionTarget.h"

ActionTarget::ActionTarget() {};

bool ActionTarget::processEvent(const sf::Event &event) const {
  bool result = false;
  for (auto &action : _eventsPoll) {
    if (action.first == event) {
      action.second(event);
      result = true;
      break;
    }
  }
  return result;
}

void ActionTarget::processEvents() const {
  for (auto &action : _eventsRealTime) {
    if (action.first.test()) {
      action.second(action.first._event);
    }
  }
}

void ActionTarget::bind(const Action &action, const FunctionType &callback) {
  if (action._type & Action::Type::RealTime) {
    _eventsRealTime.emplace_back(action, callback);
  } else {
    _eventsPoll.emplace_back(action, callback);
  }
}

void ActionTarget::unbind(const Action &action) {
  auto removeFunction = [&action](const std::pair<Action, FunctionType> &pair) -> bool {
    return pair.first == action;
  };
  if (action._type & Action::Type::RealTime) {
    _eventsRealTime.remove_if(removeFunction);
  } else {
    _eventsPoll.remove_if(removeFunction);
  }
}
