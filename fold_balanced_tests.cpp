#include <gtest/gtest.h>
#include <fold_balanced.hpp>


//-----------------------------------------------------------------------------

TEST(FoldBalancedTest, summation)
{
   std::vector<int> values{ 1, 5, 2, 0, 9, 7, 1 };
   EXPECT_EQ(30, fold_balanced(values, 5, std::plus<int>()));

   values.clear();
   EXPECT_EQ(5, fold_balanced(values, 5, std::plus<int>()));
}

TEST(FoldBalancedTest, string_concat)
{
   std::vector<std::string> values{ "this", " is ", "a", " ", "simple ", "concat test" };
   EXPECT_EQ(std::string("Go: this is a simple concat test"),
             fold_balanced(values, std::string("Go: "), std::plus<std::string>()));
}

//-----------------------------------------------------------------------------

