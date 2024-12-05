#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

std::vector<int> parseUpdate(const std::string &line) {
  std::vector<int> update;
  std::stringstream ss(line);
  std::string token;
  while (std::getline(ss, token, ',')) update.push_back(std::stoi(token));
  return update;
}

std::pair<int, int> parseRule(const std::string &line) {
  size_t delim = line.find('|');
  int x = std::stoi(line.substr(0, delim));
  int y = std::stoi(line.substr(delim + 1));
  return {x, y};
}

bool isValid(const std::vector<int> &update,
             const std::unordered_map<int, std::unordered_set<int>> &rules) {
  std::unordered_map<int, int> position;
  for (size_t i = 0; i < update.size(); ++i) position[update[i]] = i;
  for (const auto &rule : rules) {
    int x = rule.first;
    for (int y : rule.second) {
      if (position.count(x) && position.count(y)) {
        if (position[x] > position[y]) return false;
      }
    }
  }

  return true;
}

int main() {
  const std::string file = "../5.txt";
  std::ifstream f(file);
  if (!f.is_open()) {
    std::cerr << "ファイルを開くに失敗" << std::endl;
    return -1;
  }

  std::string line;
  std::vector<std::string> rrule;
  std::vector<std::string> rupdate;


  bool isEndRule = false;
  while (std::getline(f, line)) {
    if (line.empty()) {
      isEndRule = true;
      continue;
    }

    if (!isEndRule) rrule.push_back(line);
    else rupdate.push_back(line);
  }

  std::unordered_map<int, std::unordered_set<int>> rule;
  for (const auto &r : rrule) {
    auto parsedRule = parseRule(r);
    rule[parsedRule.first].insert(parsedRule.second);
  }

  std::vector<std::vector<int>> update;
  for (const auto &u : rupdate) {
    update.push_back(parseUpdate(u));
  }

  int total = 0;

  for (const auto &u : update) {
    if (isValid(u, rule)) {
      int middleIdx = u.size() / 2;
      total += u[middleIdx];
    }
  }

  std::cout << total << std::endl;

  return 0;
}
