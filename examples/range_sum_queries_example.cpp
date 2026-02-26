#include <prefix_tools/prefix_tools.hpp>
#include <iostream>
#include <vector>

void run_example()
{
  std::vector<int> values{10, 20, 30, 40, 50};

  prefix_tools::PrefixSum1D<int> ps(values);

  std::cout << "sum[0,5) = " << ps.range_sum(0, 5) << "\n";
  std::cout << "sum[1,4) = " << ps.range_sum(1, 4) << "\n";
  std::cout << "sum[2,3) = " << ps.range_sum(2, 3) << "\n";
}

int main()
{
  run_example();
}
