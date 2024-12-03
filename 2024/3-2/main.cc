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

  std::regex mulPat(R"(mul\((\d+),(\d+)\))");
  std::regex ctrlPat(R"((do\(\))|(don't\(\)))");
  std::string input((std::istreambuf_iterator<char>(f)),
      std::istreambuf_iterator<char>());
  f.close();

  std::regex combPat(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");
  std::sregex_iterator begin(input.begin(), input.end(), combPat);
  std::sregex_iterator end;

  int total = 0;
  bool enable = true;

  for (auto it = begin; it != end; ++it) {
    auto match = *it;

    if (match[0].str() == "do()") {
      enable = true;
    } else if (match[0].str() == "don't()") {
      enable = false;
    } else if (match[1].matched && match[2].matched) {
      if (enable) {
        int x = std::stoi(match[1].str());
        int y = std::stoi(match[2].str());
        total += x * y;
      }
    }
  }

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
