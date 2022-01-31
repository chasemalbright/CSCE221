#include "executable.h"
#include <string>
#include <vector>

TEST(erase) {
    Typegen t;

    for(int j = 0; j < 100; j++) {
        size_t sz = t.range<size_t>(1, 0xFFF);
        
        Vector<std::string> vec(sz);
        std::vector<std::string> gt(sz);

        using iter = typename Vector<std::string>::iterator;
        
        for(size_t i = 0; i < sz; i++)
            vec[i] = gt[i] = t.get<std::string>(100);
        
        ptrdiff_t i = t.range<ptrdiff_t>(0, sz);

        gt.erase(gt.begin() + i);
 
        size_t init_cap = vec.capacity();
        {
            Memhook mh;

            iter pos = vec.erase(vec.begin() + i);
            
            ASSERT_EQ(i, static_cast<ptrdiff_t>(pos - vec.begin()));
            ASSERT_EQ(0UL, mh.n_allocs());
        }

        ASSERT_EQ(gt.size(), vec.size());
        ASSERT_EQ(init_cap,  vec.capacity());
        
        for(size_t i = 0; i < gt.size(); i++)
            ASSERT_TRUE(gt[i] == vec[i]);
    }
}
