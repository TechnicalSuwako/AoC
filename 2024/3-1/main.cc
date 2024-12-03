#include <iostream>
#include <regex>
#include <fstream>
#include <string>

int calc(const std::string &filename) {
  std::ifstream f(filename);
  if (!f.is_open()) {
    std::cerr << "ファイルを開くに失敗" << std::endl;
    return -1;
  }

  std::regex pattern(R"(mul\((\d+),(\d+)\))");
  std::smatch match;
  int total = 0;
  std::string line;

  while (std::getline(f, line)) {
    auto srch = line.cbegin();

    while (std::regex_search(srch, line.cend(), match, pattern)) {
      int x = std::stoi(match[1].str());
      int y = std::stoi(match[2].str());
      total += x * y;
      srch = match.suffix().first;
    }
  }

  f.close();
  return total;
}

int main() {
  const std::string file = "../3.txt";

  int total = calc(file);
  if (total != -1) {
    std::cout << total << std::endl;
  }

  return 0;
}
