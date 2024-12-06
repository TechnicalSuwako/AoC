#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <utility>
#include <vector>

const int dx[] = { -1,  0,  1,  0 };
const int dy[] = {  0,  1,  0, -1 };
const char dirs[] = { '^', '>', 'v', '<' };

bool isBounds(int x, int y, int rows, int cols) {
  return x >= 0 && x < rows && y >= 0 && y < cols;
}

int drawPath(std::vector<std::string> &map) {
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
          map[i][j] = '.';
        }
      }
    }
  }

  std::set<std::pair<int, int>> visited;
  visited.insert({x, y});

  while (true) {
    int nx = x + dx[dir];
    int ny = y + dy[dir];
    if (!isBounds(nx, ny, rows, cols)) break;

    if (map[nx][ny] == '#') {
      dir = (dir + 1) % 4;
    } else {
      x = nx;
      y = ny;
      visited.insert({x, y});
    }
  }

  return visited.size();
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
