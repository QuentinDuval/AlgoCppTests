#include <gtest/gtest.h>
#include <filtering.hpp>

#include <list>
#include <vector>

//-----------------------------------------------------------------------------

struct FilteringTest : public ::testing::Test
{
   static bool is_positive(int i) { return i > 0; }
};

//-----------------------------------------------------------------------------

TEST_F(FilteringTest, empty_input)
{
   std::vector<int> ints;
   ASSERT_EQ(begin(ints), filter_if(begin(ints), end(ints), is_positive));
   ASSERT_EQ(begin(ints), unstable_filter_if(begin(ints), end(ints), is_positive));
}

TEST_F(FilteringTest, stable_filtering)
{
   std::vector<int> ints = { 1, -2, 10, -5, 7 };
   auto last = filter_if(begin(ints), end(ints), is_positive);
   
   std::vector<int> expected = { 1, 10, 7 };
   ASSERT_TRUE(std::equal(begin(expected), end(expected), begin(ints), last));
}

TEST_F(FilteringTest, unstable_filtering)
{
   std::vector<int> ints = { 1, -2, 10, -5, 7 };
   auto last = unstable_filter_if(begin(ints), end(ints), is_positive);

   std::vector<int> expected = { 1, 7, 10 };
   ASSERT_TRUE(std::equal(begin(expected), end(expected), begin(ints), last));
}

//-----------------------------------------------------------------------------

