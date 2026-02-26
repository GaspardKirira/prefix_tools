#include <prefix_tools/prefix_tools.hpp>
#include <iostream>
#include <vector>

void run_example()
{
  std::vector<int> values{1, 2, 3, 4, 5};

  prefix_tools::PrefixSum1D<int> ps(values);

  std::cout << "prefix array (n+1): ";
  for (int x : ps.prefix())
    std::cout << x << " ";
  std::cout << "\n";
}

int main()
{
  run_example();
}
