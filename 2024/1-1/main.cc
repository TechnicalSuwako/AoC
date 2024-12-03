#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

int calcDist(std::vector<int> &leftList, std::vector<int> &rightList) {
  std::sort(leftList.begin(), leftList.end());
  std::sort(rightList.begin(), rightList.end());

  int total = 0;
  for (size_t i = 0; i < leftList.size(); ++i)
    total += std::abs(leftList[i] - rightList[i]);

  return total;
}

int main() {
  std::string line;
  std::vector<int> leftList;
  std::vector<int> rightList;

  // コマンドラインで「./a.out < ../1.txt」を実効出来る様になる
  while (std::getline(std::cin, line)) {
    std::istringstream stream(line);
    int left, right;
    if (stream >> left >> right) {
      leftList.push_back(left);
      rightList.push_back(right);
    }
  }

  int total = calcDist(leftList, rightList);
  std::cout << total << std::endl;

  return 0;
}
