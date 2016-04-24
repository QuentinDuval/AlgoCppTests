#include <gtest/gtest.h>
#include <persistent_vector.hpp>
#include <timer.hpp>

#include <numeric>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------

TEST(PersistentVectorTest, empty_map)
{
   persistent_vector<std::string> v;
   EXPECT_EQ(0, v.size());
}

TEST(PersistentVectorTest, few_push_back)
{
   auto v1 = persistent_vector<std::string>();
   auto v2 = v1.push_back("a");
   auto v3 = v1.push_back("a").push_back("b");
   auto v4 = v2.push_back("b").push_back("c");

   EXPECT_EQ(0, v1.size());
   EXPECT_EQ(1, v2.size());
   EXPECT_EQ(2, v3.size());
   EXPECT_EQ(3, v4.size());
}

TEST(PersistentVectorTest, lots_push_back)
{
   std::vector<persistent_vector<int>> vs(1);
   for (int i = 0; i < 1000; i++)
      vs.push_back(vs.back().push_back(i));
   for (int i = 0; i < 1000; i++)
      EXPECT_EQ(i, vs[i].size());
}

//-----------------------------------------------------------------------------

