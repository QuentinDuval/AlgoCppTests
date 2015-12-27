#include <gtest/gtest.h>

#include <counting_sort.hpp>
#include <functional>
#include <list>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------

struct CountingSortTest : public ::testing::Test
{
   template<typename LeftContainer, typename RightContainer, typename Projection>
   void counting_sort_test_impl(LeftContainer const& expected, RightContainer const& const_input, Projection proj)
   {
      {
         auto input = const_input;
         counting_sort(begin(input), end(input), proj);
         check_equal(expected, input);
      }
      {
         auto input = const_input;
         counting_sort_in_place(begin(input), end(input), proj);
         check_equal(expected, input);
      }
   }

   template<typename T, typename Projection>
   void counting_sort_test(std::vector<T> const& expected, std::vector<T> const& input, Projection proj)
   {
      counting_sort_test_impl(expected, input, proj);
      std::list<T> list_input(begin(input), end(input));
      counting_sort_test_impl(expected, list_input, proj);
   }

   template<typename LeftContainer, typename RightContainer>
   void check_equal(LeftContainer const& expected, RightContainer const& reached)
   {
      ASSERT_EQ(expected.size(), reached.size()) << "Sorting should not impact elements count.";
      EXPECT_EQ(true, std::equal(begin(expected), end(expected), begin(reached)));
   }
};

TEST_F(CountingSortTest, empty_list)
{
   std::vector<std::string> strings;
   std::vector<std::string> expected;
   counting_sort_test(expected, strings, std::mem_fn(&std::string::length));
}

TEST_F(CountingSortTest, string_by_length)
{
   std::vector<std::string> expected{ "", "ef", "ghi", "abcd", "jklm" };
   std::vector<std::string> strings{ "abcd", "ef", "ghi", "jklm", "" };
   counting_sort_test(expected, strings, std::mem_fn(&std::string::length));
}

TEST_F(CountingSortTest, string_by_first_char)
{
   std::vector<std::string> strings { "abcd", "phi", "gamma", "beta", "alpha" };
   std::vector<std::string> expected{ "abcd", "alpha", "beta", "gamma", "phi" };
   counting_sort_test(expected, strings, [] (auto const& s) { return s[0]; });
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

