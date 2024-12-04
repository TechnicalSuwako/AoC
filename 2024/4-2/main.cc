#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

bool find(const std::vector<std::string> &grid, int row, int col) {
  int rows = grid.size();
  int cols = grid[0].size();

  if (row - 1 < 0 || row + 1 >= rows ||
      col - 1 < 0 || col + 1 >= cols) {
    return false;
  }

  if (grid[row][col] != 'A') return false;

  bool mas1 = grid[row - 1][col - 1] == 'M' &&
              grid[row + 1][col + 1] == 'S';
  bool mas2 = grid[row - 1][col + 1] == 'M' &&
              grid[row + 1][col - 1] == 'S';

  bool mas3 = grid[row + 1][col + 1] == 'M' &&
              grid[row - 1][col - 1] == 'S';
  bool mas4 = grid[row + 1][col - 1] == 'M' &&
              grid[row - 1][col + 1] == 'S';

  return (mas1 && mas2) || (mas3 && mas4) || (mas2 && mas3) || (mas1 && mas4);
}

int count(const std::vector<std::string> &grid) {
  int rows = grid.size();
  int cols = grid[0].size();
  int cnt = 0;

  for (int row = 1; row < rows - 1; ++row) {
    for (int col = 1; col < cols - 1; ++col) {
      if (find(grid, row, col)) {
        ++cnt;
      }
    }
  }

  return cnt;
}

int main() {
  const std::string file = "../4.txt";
  std::string line;
  std::vector<std::string> grid;

  std::ifstream f(file);
  if (!f.is_open()) {
    std::cerr << "ファイルを開くに失敗" << std::endl;
    return -1;
  }

  while (std::getline(f, line)) {
    grid.push_back(line);
  }

  int total = count(grid);
  std::cout << total << std::endl;

  f.close();
  return 0;
}
