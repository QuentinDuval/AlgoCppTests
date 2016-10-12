#include <gtest/gtest.h>
#include <timer.hpp>


TEST(TimerTest, time_it_test)
{
   auto r = time_it<std::milli>([] { std::cout << "Hello"; });
   std::cout << r.count() << std::endl;
}

TEST(TimerTest, timer_from_now_test)
{
   auto timer = timer_from_now<std::milli>();
   for (size_t i = 0; i < 10; ++i)
   {
      auto r = timer([] { std::cout << "Hello"; });
      std::cout << r.count() << std::endl;
   }
}
