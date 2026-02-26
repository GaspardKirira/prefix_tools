# prefix_tools

Prefix sum and difference array utilities for modern C++.

`prefix_tools` provides deterministic 1D prefix sums and difference
array helpers for efficient range queries and range updates.

Header-only. Zero external dependencies.

## Download

https://vixcpp.com/registry/pkg/gaspardkirira/prefix_tools

## Why prefix_tools?

Many competitive programming and backend problems require:

-   Fast range sum queries
-   Efficient interval updates
-   O(1) query after O(n) preprocessing
-   Deterministic, explicit behavior

Rewriting prefix sum logic repeatedly is error-prone.

This library provides:

-   `PrefixSum1D<T>` for O(1) range queries
-   `DiffArray1D<T>` for O(1) range updates
-   Explicit interval semantics `[l, r)`

No hidden state\
No implicit resizing

No segment tree.\
No Fenwick tree.\
No abstraction overhead.

Just explicit linear preprocessing utilities.

## Installation

### Using Vix Registry

``` bash
vix add gaspardkirira/prefix_tools
vix deps
```

### Manual

``` bash
git clone https://github.com/GaspardKirira/prefix_tools.git
```

Add the `include/` directory to your project.

## Dependency

Requires C++17 or newer.

No external dependencies.

## Quick Examples

### Prefix Sum

``` cpp
#include <prefix_tools/prefix_tools.hpp>
#include <vector>
#include <iostream>

int main()
{
  std::vector<int> values{1, 2, 3, 4, 5};

  prefix_tools::PrefixSum1D<int> ps(values);

  std::cout << ps.range_sum(1, 4) << "\n"; // 2 + 3 + 4
}
```

### Range Sum Queries

``` cpp
#include <prefix_tools/prefix_tools.hpp>
#include <vector>
#include <iostream>

int main()
{
  std::vector<int> values{10, 20, 30, 40, 50};

  prefix_tools::PrefixSum1D<int> ps(values);

  std::cout << "sum[0,5) = " << ps.range_sum(0, 5) << "\n";
  std::cout << "sum[2,4) = " << ps.range_sum(2, 4) << "\n";
}
```

### Difference Array (Range Add)

``` cpp
#include <prefix_tools/prefix_tools.hpp>
#include <vector>
#include <iostream>

int main()
{
  prefix_tools::DiffArray1D<int> diff(5);

  diff.range_add(1, 4, 3); // +3 on indices 1,2,3
  diff.range_add(0, 2, 2); // +2 on indices 0,1

  auto result = diff.build();

  for (int x : result)
    std::cout << x << " ";
}
```

## API Overview

``` cpp
prefix_tools::PrefixSum1D<T>
  .build(values)
  .range_sum(l, r)
  .size()
  .prefix()

prefix_tools::DiffArray1D<T>
  .reset(n)
  .range_add(l, r, delta)
  .build()
  .size()
  .diff()
```

## Interval Convention

All intervals use half-open notation:

`[l, r)`

-   `l` is inclusive
-   `r` is exclusive

This matches STL conventions.

## Complexity

### PrefixSum1D

-   Build: O(n)
-   Range query: O(1)

### DiffArray1D

-   Range update: O(1)
-   Final build: O(n)

## Design Principles

-   Explicit interval semantics
-   Deterministic behavior
-   Minimal surface API
-   No dynamic resizing during operations
-   Competitive-programming friendly
-   Backend-safe

This module is intentionally small.

If you need:

-   2D prefix sums
-   Fenwick tree
-   Segment tree
-   Lazy propagation

Build those as separate modules.

## Tests

Run:

``` bash
vix build
vix tests
```

Tests verify:

-   Correct prefix computation
-   Range sum correctness
-   Difference array correctness
-   Full range updates
-   Edge intervals

## License

MIT License
Copyright (c) Gaspard Kirira

