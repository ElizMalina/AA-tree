#include <fstream>
#include <iostream>

#include "aatree.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Argc!=3";
    return 1;
  }

  std::ifstream input(argv[1]);
  if (!input.is_open()) {
    std::cerr << "Can not open input file";
    return 2;
  }

  std::ofstream output(argv[2]);
  if (!output.is_open()) {
    std::cerr << "Can not open output file";
    return 3;
  }

  int n = 0;
  input >> n;

  AATree tree;
  char sign;
  int x;
  for (int i = 0; i < n; ++i) {
    input >> sign >> x;
    if (sign == '+') {
      tree.add(x);
      output << tree.getRootLevel() << '\n';
    } else if (sign == '-') {
      tree.erase(x);
      output << tree.getRootLevel() << '\n';
    } else if (sign == '?') {
      output << (tree.finde(x) ? "true" : "false") << '\n';
    } else {
      std::cerr << "No correct sign";
      return 4;
    }
  }

  input.close();
  output.close();
  return 0;
}
