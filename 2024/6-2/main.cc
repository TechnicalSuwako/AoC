#include <cstdio>
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <tuple>
#include <vector>

const int dx[] = { -1,  0,  1,  0 };
const int dy[] = {  0,  1,  0, -1 };
const char dirs[] = { '^', '>', 'v', '<' };

bool isBounds(int x, int y, int rows, int cols) {
  return x >= 0 && x < rows && y >= 0 && y < cols;
}

std::set<std::pair<int, int>> findPos(std::vector<std::string> &map) {
  int rows = map.size();
  int cols = map[0].size();
  int x, y, dir;

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      for (int d = 0; d < 4; ++d) {
        if (map[i][j] == dirs[d]) {
          x = i;
          y = j;
          dir = d;
        }
      }
    }
  }

  std::set<std::pair<int, int>> reach;
  std::set<std::tuple<int, int, int>> visited;
  visited.insert({x, y, dir});
  reach.insert({x, y});

  while (true) {
    int nx = x + dx[dir];
    int ny = y + dy[dir];

    if (!isBounds(nx, ny, rows, cols)) break;

    if (map[nx][ny] == '#') {
      dir = (dir + 1) % 4;
    } else {
      x = nx;
      y = ny;
    }

    if (visited.count({x, y, dir})) break;
    visited.insert({x, y, dir});
    reach.insert({x, y});
  }

  return reach;
}

bool isObstruct(const std::vector<std::string> &map, int obsX, int obsY) {
  int rows = map.size();
  int cols = map[0].size();
  int x, y, dir;

  std::vector<std::string> mapCpy = map;
  mapCpy[obsX][obsY] = '#';

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      for (int d = 0; d < 4; ++d) {
        if (map[i][j] == dirs[d]) {
          x = i;
          y = j;
          dir = d;
        }
      }
    }
  }

  std::set<std::tuple<int, int, int>> visited;
  visited.insert({x, y, dir});

  while (true) {
    int nx = x + dx[dir];
    int ny = y + dy[dir];

    if (!isBounds(nx, ny, rows, cols)) return false;

    if (mapCpy[nx][ny] == '#') {
      dir = (dir + 1) % 4;
    } else {
      x = nx;
      y = ny;
    }

    if (visited.count({x, y, dir})) return true;
    visited.insert({x, y, dir});
  }
}

int drawPath(std::vector<std::string> map) {
  std::set<std::pair<int, int>> reach = findPos(map);
  int pos = 0;

  for (const auto &[x, y] : reach) {
    if (map[x][y] == '^' || map[x][y] == '>' || map[x][y] == 'v' || map[x][y] == '<') {
      continue;
    }

    if (isObstruct(map, x, y)) ++pos;
  }

  return pos;
}

int main() {
  const std::string file = "../6.txt";
  std::ifstream f(file);
  if (!f.is_open()) {
    std::cerr << "ファイルを開くに失敗" << std::endl;
    return -1;
  }

  std::string line;
  std::vector<std::string> map;
  while (std::getline(f, line)) {
    map.push_back(line);
  }

  int res = drawPath(map);
  std::cout << res << std::endl;

  return 0;
}
