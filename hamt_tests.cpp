#include <gtest/gtest.h>
#include <hamt.hpp>
#include <timer.hpp>

#include <string>


//-----------------------------------------------------------------------------

TEST(HamtTest, empty_map)
{
   hash_array_mapped_trie<std::string, std::string> hamt;
   EXPECT_EQ(0, hamt.size());
}

TEST(HamtTest, add_key)
{
   hash_array_mapped_trie<std::string, std::string> hamt;
   hamt.insert("a", "alpha");
   hamt.insert("b", "beta");
   
   EXPECT_EQ(2, hamt.size());
   EXPECT_EQ(true, hamt.contains("a"));
   EXPECT_EQ(true, hamt.contains("b"));
   EXPECT_EQ("alpha", hamt.find("a").second);
   EXPECT_EQ("beta", hamt.find("b").second);
}

TEST(HamtTest, collide_key)
{
   hash_array_mapped_trie<std::string, std::string> hamt;
   hamt.insert("a", "alpha");
   hamt.insert("a", "alpha-beta");

   EXPECT_EQ(1, hamt.size());
   EXPECT_EQ(true, hamt.contains("a"));
   EXPECT_EQ("alpha-beta", hamt.find("a").second);
}

TEST(HamtTest, perf_insert)
{
   show_time(std::cout, "2,000,000 inserts in ms", 1, []() {
      hash_array_mapped_trie<std::string, std::string> hamt;
      for (size_t i = 0; i < 1000000; ++i)
      {
         hamt.insert("a", "alpha");
         hamt.insert("a", "alpha-beta");
      }
   });
}

//-----------------------------------------------------------------------------

