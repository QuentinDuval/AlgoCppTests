#include <gtest/gtest.h>
#include <hamt.hpp>
#include <timer.hpp>

#include <map>
#include <string>
#include <unordered_map>

//-----------------------------------------------------------------------------

TEST(HamtTest, empty_map)
{
   hash_array_mapped_trie<std::string, std::string> hamt;
   EXPECT_EQ(0, hamt.size());
}

TEST(HamtTest, add_key)
{
   hash_array_mapped_trie<std::string, std::string> hamt;
   hamt.insert({ "a", "alpha" });
   hamt.insert({ "b", "beta" });
   
   EXPECT_EQ(2, hamt.size());
   EXPECT_EQ(1, hamt.count("a"));
   EXPECT_EQ(1, hamt.count("b"));
   EXPECT_EQ("alpha", hamt.find("a").second);
   EXPECT_EQ("beta", hamt.find("b").second);
}

TEST(HamtTest, collide_key)
{
   hash_array_mapped_trie<std::string, std::string> hamt;
   hamt.insert({ "a", "alpha" });
   hamt.insert({ "a", "alpha-beta" });

   EXPECT_EQ(1, hamt.size());
   EXPECT_EQ(1, hamt.count("a"));
   EXPECT_EQ("alpha-beta", hamt.find("a").second);
}


//-----------------------------------------------------------------------------
// PERFORMANCE
//-----------------------------------------------------------------------------

template<typename AssociativeCont>
void perf_no_collisions_test(AssociativeCont& c, std::size_t size)
{
   show_time(std::cout, "1,000,000 int inserts in ms", 1, [&]()
   {
      for (size_t i = 0; i < size; ++i)
         c.insert({ size - i - 1, i });
   });

   show_time(std::cout, "1,000,000 int searches in ms", 1, [&]()
   {
      for (size_t i = 0; i < size; ++i)
         EXPECT_EQ(1, c.count(i));
   });

   show_time(std::cout, "1,000,000 int misses in ms", 1, [&]()
   {
      for (size_t i = 0; i < size; ++i)
         EXPECT_EQ(0, c.count(size + i));
   });
}

TEST(HamtTest, perf_no_collisions)
{
   static const std::size_t SIZE = 1000000;

   std::cout << "HAMT" << std::endl;
   hash_array_mapped_trie<int, int> hamt;
   perf_no_collisions_test(hamt, SIZE);

   std::cout << "STD::MAP" << std::endl;
   std::map<int, int> omap;
   perf_no_collisions_test(omap, SIZE);

   std::cout << "STD::UNORDERED_MAP" << std::endl;
   std::unordered_map<int, int> umap;
   perf_no_collisions_test(umap, SIZE);
}

//-----------------------------------------------------------------------------

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
         hamt.insert(inputs[p]);
      }
   });

   show_time(std::cout, "1,000,000 string searches in ms", 1, [&]()
   {
      for (size_t i = 0; i < 1000000; ++i)
      {
         size_t p = i % inputs.size();
         EXPECT_EQ(1, hamt.count(inputs[p].first));
      }
   });

   show_time(std::cout, "1,000,000 string misses in ms", 1, [&]()
   {
      for (size_t i = 0; i < 1000000; ++i)
      {
         size_t p = i % misses.size();
         EXPECT_EQ(0, hamt.count(misses[p].first));
      }
   });
}

//-----------------------------------------------------------------------------

