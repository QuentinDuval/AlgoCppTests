#include <gtest/gtest.h>
#include <cycles.hpp>

#include <list>
#include <vector>

//-----------------------------------------------------------------------------

TEST(CyclesTest, module_function)
{
   auto modulo_five = [](int i) { return i % 5; };
   auto always_true = [](int i) { return true; };
   ASSERT_EQ(true, is_cyclic(12, modulo_five, always_true));
}

TEST(CyclesTest, linked_list)
{
   std::vector<size_t> my_list = { 0, 2, 3, 1, 5, 6, 7, 8 };
   auto next_elem = [&](size_t i) { return my_list[i]; };
   auto in_bounds = [&](size_t i) { return i < my_list.size(); };

   ASSERT_EQ(true, is_cyclic(0, next_elem, in_bounds));
   ASSERT_EQ(true, is_cyclic(2, next_elem, in_bounds));
   ASSERT_EQ(false, is_cyclic(5, next_elem, in_bounds));

   ASSERT_EQ(false, is_cyclic(10, next_elem, in_bounds));
   ASSERT_EQ(false, is_cyclic(-1, next_elem, in_bounds));
}

//-----------------------------------------------------------------------------

