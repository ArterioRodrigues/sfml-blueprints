#pragma once
#include "action.h"
#include "pch.h"

template <typename T = int> class ActionMap {
public:
  ActionMap(const ActionMap<T> &) = delete;
  ActionMap<T> &operator=(const ActionMap<T> &) = delete;

  ActionMap() = default;

  void map(const T &key, const Action &action) { _map.emplace(key, action); }
  const Action get(const T &key) const { return _map.at(key); }

private:
  std::unordered_map<T, Action> _map;
};
