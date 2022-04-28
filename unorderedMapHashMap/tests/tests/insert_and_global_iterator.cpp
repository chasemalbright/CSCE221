#include "executable.h"
#include <unordered_map>

TEST(insert_and_global_iterator) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        using iter = typename UnorderedMap<double, double>::iterator;

        size_t n_pairs = t.range(400ul);
        size_t n = t.range(1000ull);

        std::vector<std::pair<double, double>> pairs(n_pairs);
        t.fill(pairs.begin(), pairs.end());

        std::unordered_map<double, double> shadow_map;
        UnorderedMap<double, double> map(n);

        for(auto const & pair: pairs) {
            auto [it, inserted] = shadow_map.insert(pair);
            
            std::pair<iter, bool> ret;
            
            {
                Memhook mh;
                ret = map.insert(pair);
                ASSERT_EQ(inserted, mh.n_allocs());
            }

            ASSERT_EQ(inserted, ret.second);
            ASSERT_EQ(shadow_map.size(), map.size());
            ASSERT_EQ(pair.first, ret.first->first);

            for(iter it = map.begin(); it != map.end(); it++) {
                auto found = shadow_map.find(it->first);

                tdbg << "Value with key " << it->first << " could not be found in your map.";
                ASSERT_TRUE(found != shadow_map.end());
                
                tdbg << "Key " << it->first << " has wrong value " << it->second;
                ASSERT_EQ(found->second, it->second);
            }
        }  
    }
}
