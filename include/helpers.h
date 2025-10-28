#pragma once
#include "pch.h"
template<typename T> 
T randomTemplate(T start, T end) {
  std::mt19937 engine(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  std::uniform_int_distribution<int> dist(start, end);
  return dist(engine);
}
