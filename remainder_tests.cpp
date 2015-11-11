#include <gtest/gtest.h>
#include <arithmetic.hpp>


//-----------------------------------------------------------------------------

auto remainder_functions = {
   slow_remainder, fast_remainder_rec,
   fast_remainder_iter, fast_remainder_half,
   fast_remainder_cps
};

TEST(ReminderTest, remainder_not_null)
{
   for (auto fun: remainder_functions)
      EXPECT_EQ(9, fun(14219, 10));
}

TEST(ReminderTest, remainder_is_null)
{
   for (auto fun : remainder_functions)
      EXPECT_EQ(0, fun(14220, 10));
}

//-----------------------------------------------------------------------------

auto quotient_functions = {
   slow_quotient, fast_quotient_rec,
   fast_quotient_iter, fast_quotient_half
};

TEST(QuotientTest, remainder_not_null)
{
   for (auto fun : quotient_functions)
      EXPECT_EQ(std::make_pair(1421, 9), fun(14219, 10));
}

TEST(QuotientTest, remainder_is_null)
{
   for (auto fun : quotient_functions)
      EXPECT_EQ(std::make_pair(1422, 0), fun(14220, 10));
}

//-----------------------------------------------------------------------------

