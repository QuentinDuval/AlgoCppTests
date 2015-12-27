#include <gtest/gtest.h>

#include <counting_sort.hpp>
#include <functional>
#include <string>

//-----------------------------------------------------------------------------

TEST(CountingSortTest, empty_list)
{
   std::vector<std::string> strings;
   std::vector<std::string> expected;

   counting_sort(begin(strings), end(strings), std::mem_fn(&std::string::length));
   ASSERT_EQ(expected.size(), strings.size());
}

TEST(CountingSortTest, string_by_length)
{
   std::vector<std::string> strings{ "abcd", "ef", "ghi", "jklm", "" };
   std::vector<std::string> expected{ "", "ef", "ghi", "abcd", "jklm" };

   counting_sort(begin(strings), end(strings), std::mem_fn(&std::string::length));
   ASSERT_EQ(expected.size(), strings.size());
   for (size_t i = 0; i < expected.size(); ++i)
      EXPECT_EQ(expected[i], strings[i]);
}

TEST(CountingSortTest, string_with_associated_value)
{
   std::vector<std::string> strings    { "abcd", "ef", "ghi", "jklm", "" };
   std::vector<int>         preferences{ 11,     1,     -1,   10,     2  };
   std::vector<std::string> expected   { "ghi", "ef", "", "jklm", "abcd" };

   counting_sort(begin(strings), end(strings), begin(preferences), end(preferences));
   ASSERT_EQ(expected.size(), strings.size());
   for (size_t i = 0; i < expected.size(); ++i)
      EXPECT_EQ(expected[i], strings[i]);
}

//-----------------------------------------------------------------------------

