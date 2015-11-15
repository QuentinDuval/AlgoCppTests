#include <gtest/gtest.h>

#include <counting_sort.hpp>
#include <functional>
#include <string>

//-----------------------------------------------------------------------------

TEST(CountingSortTest, string_by_length)
{
   std::vector<std::string> strings{ "abcd", "ef", "ghi", "jklm", "" };
   std::vector<std::string> expected{ "", "ef", "ghi", "abcd", "jklm" };

   counting_sort(begin(strings), end(strings), std::mem_fn(&std::string::length));
   ASSERT_EQ(expected.size(), strings.size());
   for (size_t i = 0; i < expected.size(); ++i)
      EXPECT_EQ(expected[i], strings[i]);
}

//-----------------------------------------------------------------------------

