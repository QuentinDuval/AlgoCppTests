#include <gtest/gtest.h>

#include <counting_sort.hpp>
#include <functional>
#include <string>

//-----------------------------------------------------------------------------

struct CountingSortTest : public ::testing::Test
{
   template<typename T>
   void check_equal(std::vector<T> const& expected, std::vector<T> const& reached)
   {
      ASSERT_EQ(expected.size(), reached.size()) << "Sorting should not impact elements count.";
      for (size_t i = 0; i < expected.size(); ++i)
         EXPECT_EQ(expected[i], reached[i]);
   }
};

TEST_F(CountingSortTest, empty_list)
{
   std::vector<std::string> strings;
   std::vector<std::string> expected;
   counting_sort(begin(strings), end(strings), std::mem_fn(&std::string::length));
   check_equal(expected, strings);
}

TEST_F(CountingSortTest, string_by_length)
{
   std::vector<std::string> strings{ "abcd", "ef", "ghi", "jklm", "" };
   std::vector<std::string> expected{ "", "ef", "ghi", "abcd", "jklm" };
   counting_sort(begin(strings), end(strings), std::mem_fn(&std::string::length));
   check_equal(expected, strings);
}

TEST_F(CountingSortTest, string_by_first_char)
{
   std::vector<std::string> strings { "abcd", "phi", "gamma", "beta", "alpha" };
   std::vector<std::string> expected{ "abcd", "alpha", "beta", "gamma", "phi" };
   counting_sort(begin(strings), end(strings), [](auto& s) { return s[0]; });
   check_equal(expected, strings);
}

TEST_F(CountingSortTest, string_with_associated_value)
{
   std::vector<std::string> strings    { "abcd", "ef", "ghi", "jklm", "" };
   std::vector<int>         preferences{ 11,     1,     -1,   10,     2  };
   std::vector<std::string> expected   { "ghi", "ef", "", "jklm", "abcd" };

   counting_sort(begin(strings), end(strings), begin(preferences), end(preferences));
   check_equal(expected, strings);
}

//-----------------------------------------------------------------------------

