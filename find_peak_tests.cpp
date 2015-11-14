#include <gtest/gtest.h>
#include <find_peak.hpp>

#include <algorithm>
#include <functional>


//-----------------------------------------------------------------------------

TEST(FindPeakTest, empty_vector)
{
   std::vector<int> empty;
   EXPECT_EQ(end(empty), find_peak_rec(empty));
   EXPECT_EQ(end(empty), find_peak_rec(begin(empty), end(empty)));
   EXPECT_EQ(end(empty), find_peak(empty));
   EXPECT_EQ(end(empty), find_peak(begin(empty), end(empty)));
}

TEST(FindPeakTest, filled_vector)
{
   std::vector<int> seq{ 1, 2, 3, 2, 4, 5, 6 };
   EXPECT_EQ(3, *find_peak_rec(seq));
   EXPECT_EQ(3, *find_peak(seq));
}

TEST(FindPeakTest, monotonous_vector)
{
   std::vector<int> seq{ 1, 2, 3, 4, 5, 6, 7, 8 };
   EXPECT_EQ(8, *find_peak_rec(seq));
   EXPECT_EQ(8, *find_peak(seq));

   EXPECT_EQ(1, *find_peak_rec(seq, std::greater<int>()));
   EXPECT_EQ(1, *find_peak(seq, std::greater<int>()));

   std::reverse(begin(seq), end(seq));
   EXPECT_EQ(8, *find_peak_rec(seq));
   EXPECT_EQ(8, *find_peak(seq));
}

//-----------------------------------------------------------------------------

