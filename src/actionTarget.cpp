#include "actionTarget.h"

template<typename T>
bool ActionTarget<T>::processEvent(const sf::Event &event) const {
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

template<typename T>
void ActionTarget<T>::processEvents() const {
  for (auto &action : _eventsRealTime) {
    if (action.first.test()) {
      action.second(action.first._event);
    }
  }
}

template<typename T>
void ActionTarget<T>::bind(const T& key, const FunctionType &callback) {
  if (key._type & Action::Type::RealTime) {
    _eventsRealTime.emplace_back(key, callback);
  } else {
    _eventsPoll.emplace_back(key, callback);
  }
}

template<typename T>
void ActionTarget<T>::unbind(const T& key) {
  auto removeFunction = [&key](const std::pair<Action, FunctionType> &pair) -> bool {
    return pair.first == key;
  };
  if (key._type & Action::Type::RealTime) {
    _eventsRealTime.remove_if(removeFunction);
  } else {
    _eventsPoll.remove_if(removeFunction);
  }
}
