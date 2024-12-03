#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool isSafe(const std::vector<int> &level) {
  if (level.size() < 2) return true;
  bool inc = true, dec = true;

  for (size_t i = 1; i < level.size(); ++i) {
    int diff = level[i] - level[i - 1];
    if (std::abs(diff) < 1 || std::abs(diff) > 3) return false;
    if (diff < 0) inc = false;
    if (diff > 0) dec = false;
  }

  return inc || dec;
}

bool isSafeR(const std::vector<int> &level) {
  if (isSafe(level)) return true;

  for (size_t i = 0; i < level.size(); ++i) {
    std::vector<int> mod = level;
    mod.erase(mod.begin() + i);
    if (isSafe(mod)) return true;
  }

  return false;
}

int main() {
  std::string line;
  int safeCnt = 0;

  while (std::getline(std::cin, line)) {
    std::vector<int> level;
    std::istringstream stream(line);
    int lvl;

    while (stream >> lvl) level.push_back(lvl);
    if (isSafeR(level)) ++safeCnt;
    std::cout << safeCnt << std::endl;
  }

  return 0;
}
