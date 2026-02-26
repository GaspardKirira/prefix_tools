#include <prefix_tools/prefix_tools.hpp>
#include <iostream>
#include <vector>

void run_example()
{
  prefix_tools::DiffArray1D<int> diff(6);

  // +5 on [1, 5) => indices 1..4
  diff.range_add(1, 5, 5);

  // +2 on [0, 3) => indices 0..2
  diff.range_add(0, 3, 2);

  // -4 on [2, 6) => indices 2..5
  diff.range_add(2, 6, -4);

  auto result = diff.build();

  std::cout << "final values: ";
  for (int x : result)
    std::cout << x << " ";
  std::cout << "\n";
}

int main()
{
  run_example();
}
