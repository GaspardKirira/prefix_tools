#include <prefix_tools/prefix_tools.hpp>

#include <cassert>
#include <iostream>
#include <vector>

using namespace prefix_tools;

static void test_prefix_sum_basic()
{
  std::vector<int> v{1, 2, 3, 4, 5};

  PrefixSum1D<int> ps(v);

  assert(ps.size() == 5);
  assert(ps.range_sum(0, 5) == 15);
  assert(ps.range_sum(0, 1) == 1);
  assert(ps.range_sum(1, 3) == 5); // 2 + 3
  assert(ps.range_sum(2, 2) == 0); // empty range
  assert(ps.range_sum(4, 5) == 5);
}

static void test_prefix_sum_rebuild()
{
  PrefixSum1D<long long> ps;
  ps.build(std::vector<long long>{10, 20, 30});

  assert(ps.size() == 3);
  assert(ps.range_sum(0, 3) == 60);
  assert(ps.range_sum(1, 3) == 50);
}

static void test_diff_array_basic()
{
  DiffArray1D<int> d(5);

  // add +3 to [1,4) => indices 1,2,3
  d.range_add(1, 4, 3);

  // add +2 to [0,2) => indices 0,1
  d.range_add(0, 2, 2);

  // expected:
  // idx: 0 1 2 3 4
  // val: 2 5 3 3 0
  auto out = d.build();

  assert(out.size() == 5);
  assert(out[0] == 2);
  assert(out[1] == 5);
  assert(out[2] == 3);
  assert(out[3] == 3);
  assert(out[4] == 0);
}

static void test_diff_array_full_range()
{
  DiffArray1D<long long> d(4);
  d.range_add(0, 4, 7);

  auto out = d.build();
  assert(out[0] == 7);
  assert(out[1] == 7);
  assert(out[2] == 7);
  assert(out[3] == 7);
}

int main()
{
  test_prefix_sum_basic();
  test_prefix_sum_rebuild();
  test_diff_array_basic();
  test_diff_array_full_range();

  std::cout << "prefix_tools tests passed\n";
  return 0;
}
