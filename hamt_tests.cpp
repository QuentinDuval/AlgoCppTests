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


//-----------------------------------------------------------------------------
// PERFORMANCE
//-----------------------------------------------------------------------------

TEST(HamtTest, perf_no_collisions)
{
   std::vector<std::pair<int, int>> inputs;
   hash_array_mapped_trie<int, int> hamt;
   static const std::size_t SIZE = 1000000;

   show_time(std::cout, "1,000,000 int inserts in ms", 1, [&]()
   {
      for (size_t i = 0; i < SIZE; ++i)
         hamt.insert(i, i);
   });

   show_time(std::cout, "1,000,000 int searches in ms", 1, [&]()
   {
      for (size_t i = 0; i < SIZE; ++i)
         EXPECT_TRUE(hamt.contains(i));
   });

   show_time(std::cout, "1,000,000 int misses in ms", 1, [&]()
   {
      for (size_t i = 0; i < SIZE; ++i)
         EXPECT_FALSE(hamt.contains(SIZE + i));
   });
}

TEST(HamtTest, perf_lots_of_collisions)
{
   std::vector<std::pair<std::string, std::string>> inputs;
   std::vector<std::pair<std::string, std::string>> misses;
   for (char c : "abcdefghijklmnopqrstuvwxyz")
   {
      inputs.emplace_back(std::string(10, c), std::string(50, c));
      misses.emplace_back(std::string(9, c), std::string(50, c));
   }

   hash_array_mapped_trie<std::string, std::string> hamt;

   show_time(std::cout, "1,000,000 string inserts in ms", 1, [&]()
   {
      for (size_t i = 0; i < 1000000; ++i)
      {
         size_t p = i % inputs.size();
         hamt.insert(inputs[p].first, inputs[p].second);
      }
   });

   show_time(std::cout, "1,000,000 string searches in ms", 1, [&]()
   {
      for (size_t i = 0; i < 1000000; ++i)
      {
         size_t p = i % inputs.size();
         EXPECT_TRUE(hamt.contains(inputs[p].first));
      }
   });

   show_time(std::cout, "1,000,000 string misses in ms", 1, [&]()
   {
      for (size_t i = 0; i < 1000000; ++i)
      {
         size_t p = i % misses.size();
         EXPECT_FALSE(hamt.contains(misses[p].first));
      }
   });
}

//-----------------------------------------------------------------------------

