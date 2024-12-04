#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

const std::vector<std::pair<int, int>> dir = {
  { 0,  1}, // 右
  { 0, -1}, // 左
  { 1,  0}, // 下
  {-1,  0}, // 上
  { 1,  1}, // 右下
  {-1, -1}, // 左上
  { 1, -1}, // 左下
  {-1,  1}, // 右上
};

bool find(const std::vector<std::string> &grid, int row, int col,
          const std::string &word, int dirRow, int dirCol) {
  int rows = grid.size();
  int cols = grid[0].size();

  for (int i = 0; i < word.size(); ++i) {
    int newRow = row + i * dirRow;
    int newCol = col + i * dirCol;

    if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols) {
      return false;
    }

    if (grid[newRow][newCol] != word[i]) {
      return false;
    }
  }

  return true;
}

int count(const std::vector<std::string> &grid, const std::string &word) {
  int rows = grid.size();
  int cols = grid[0].size();
  int cnt = 0;

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      for (const auto &[dirRow, dirCol] : dir) {
        if (find(grid, row, col, word, dirRow, dirCol)) {
          ++cnt;
        }
      }
    }
  }

  return cnt;
}

int main() {
  const std::string file = "../4.txt";
  std::string line;
  std::vector<std::string> grid;
  std::string word = "XMAS";

  std::ifstream f(file);
  if (!f.is_open()) {
    std::cerr << "ファイルを開くに失敗" << std::endl;
    return -1;
  }

  while (std::getline(f, line)) {
    grid.push_back(line);
  }

  int total = count(grid, word);
  std::cout << total << std::endl;

  f.close();
  return 0;
}
