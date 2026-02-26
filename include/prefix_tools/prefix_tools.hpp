/**
 * @file prefix_tools.hpp
 * @brief Prefix sums and difference array utilities for modern C++.
 *
 * Provides:
 *  - PrefixSum1D<T> for O(1) range sum queries after O(n) build
 *  - DiffArray1D<T> for O(1) range add updates after O(n) build
 *
 * Deterministic and explicit:
 *  - No hidden allocations beyond internal vectors
 *  - No exceptions (unless T operations throw)
 */

#pragma once

#include <cstddef>
#include <vector>

namespace prefix_tools
{

  /**
   * @brief Prefix sum for 1D arrays.
   *
   * Builds an internal prefix array p such that:
   *  p[0] = 0
   *  p[i+1] = sum_{k=0..i} a[k]
   *
   * Range sum on [l, r) is:
   *  p[r] - p[l]
   *
   * @tparam T Numeric-like type supporting + and -
   */
  template <typename T>
  class PrefixSum1D final
  {
  public:
    PrefixSum1D() = default;

    /**
     * @brief Build prefix sums from input values.
     *
     * @param values Input array
     *
     * @complexity O(n)
     */
    explicit PrefixSum1D(const std::vector<T> &values)
    {
      build(values);
    }

    /**
     * @brief Build prefix sums from input values.
     *
     * @param values Input array
     *
     * @complexity O(n)
     */
    void build(const std::vector<T> &values)
    {
      prefix_.assign(values.size() + 1, T{});
      for (std::size_t i = 0; i < values.size(); ++i)
        prefix_[i + 1] = prefix_[i] + values[i];
    }

    /**
     * @brief Returns the sum of values in [l, r).
     *
     * Preconditions:
     *  - l <= r
     *  - r <= size()
     *
     * @param l Left index (inclusive)
     * @param r Right index (exclusive)
     *
     * @return Sum of interval
     *
     * @complexity O(1)
     */
    T range_sum(std::size_t l, std::size_t r) const
    {
      return prefix_[r] - prefix_[l];
    }

    /**
     * @brief Returns number of original elements.
     */
    std::size_t size() const
    {
      return prefix_.empty() ? 0 : (prefix_.size() - 1);
    }

    /**
     * @brief Exposes internal prefix array p of size n+1.
     */
    const std::vector<T> &prefix() const
    {
      return prefix_;
    }

  private:
    std::vector<T> prefix_{};
  };

  /**
   * @brief Difference array for 1D range add updates.
   *
   * Maintains diff such that for applying add(v) on [l, r):
   *  diff[l] += v
   *  diff[r] -= v (if r < n)
   *
   * After all updates, build values by prefixing diff:
   *  a[i] = a[i-1] + diff[i]
   *
   * @tparam T Numeric-like type supporting + and -
   */
  template <typename T>
  class DiffArray1D final
  {
  public:
    DiffArray1D() = default;

    /**
     * @brief Construct with size n, initial values assumed to be 0.
     */
    explicit DiffArray1D(std::size_t n)
    {
      reset(n);
    }

    /**
     * @brief Reset to size n (clears all updates).
     */
    void reset(std::size_t n)
    {
      n_ = n;
      diff_.assign(n_ + 1, T{});
    }

    /**
     * @brief Apply delta to interval [l, r) in O(1).
     *
     * Preconditions:
     *  - l <= r
     *  - r <= size()
     */
    void range_add(std::size_t l, std::size_t r, const T &delta)
    {
      diff_[l] = diff_[l] + delta;
      diff_[r] = diff_[r] - delta; // r can be n (sentinel)
    }

    /**
     * @brief Build final array after all updates.
     *
     * @return Vector of size n.
     *
     * @complexity O(n)
     */
    std::vector<T> build() const
    {
      std::vector<T> out;
      out.resize(n_, T{});

      T cur{};
      for (std::size_t i = 0; i < n_; ++i)
      {
        cur = cur + diff_[i];
        out[i] = cur;
      }

      return out;
    }

    /**
     * @brief Returns size n.
     */
    std::size_t size() const
    {
      return n_;
    }

    /**
     * @brief Exposes internal diff array of size n+1 (includes sentinel).
     */
    const std::vector<T> &diff() const
    {
      return diff_;
    }

  private:
    std::size_t n_{0};
    std::vector<T> diff_{};
  };

} // namespace prefix_tools
