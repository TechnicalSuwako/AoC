#include <unordered_map>
#include <iostream>
#include <sstream>
#include <vector>

int calcDist(std::vector<int> &leftList, std::vector<int> &rightList) {
  std::unordered_map<int, int> freq;
  for (int num : rightList) freq[num]++;

  long long sim = 0;
  for (int num : leftList) sim += num * freq[num];

  return sim;
}

int main() {
  std::string line;
  std::vector<int> leftList;
  std::vector<int> rightList;

  while (std::getline(std::cin, line)) {
    std::istringstream stream(line);
    int left, right;
    if (stream >> left >> right) {
      leftList.push_back(left);
      rightList.push_back(right);
    }
  }

  long long sim = calcDist(leftList, rightList);
  std::cout << sim << std::endl;

  return 0;
}
