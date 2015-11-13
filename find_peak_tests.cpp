#include <gtest/gtest.h>
#include <find_peak.hpp>

#include <algorithm>
#include <functional>


//-----------------------------------------------------------------------------

TEST(FindPeakTest, empty_vector)
{
   std::vector<int> empty;
   auto it = find_peak(begin(empty), end(empty));
   EXPECT_EQ(end(empty), it);
   EXPECT_EQ(end(empty), find_peak(empty));
}

TEST(FindPeakTest, filled_sequence)
{
   std::vector<int> seq{ 1, 2, 3, 2, 4, 5, 6 };
   auto it = find_peak(begin(seq), end(seq));
   EXPECT_EQ(3, *it);
   EXPECT_EQ(it, find_peak(seq));
}

TEST(FindPeakTest, monotonous_sequence)
{
   std::vector<int> seq{ 1, 2, 3, 4, 5, 6, 7, 8 };
   auto it1 = find_peak(begin(seq), end(seq), std::less<int>());
   EXPECT_EQ(8, *it1);

   auto it2 = find_peak(begin(seq), end(seq), std::greater<int>());
   EXPECT_EQ(1, *it2);
}

//-----------------------------------------------------------------------------

