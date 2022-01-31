#include "pushback_common.h"
#include "executable.h"
#include <vector>

TEST(push_back) {
    Typegen t;

    std::vector<int> gt(last_idx, 0);

    {
        Memhook m;

        Vector<int> vec;
        int el;
        for(size_t p = 0, idx = 0; p < last_idx; p++) {
            const Memstate & s = state[idx];
            
            ASSERT_MEMSTATE(p, vec, s, gt, m, true);

            for(size_t i = 0; i < p; i++) {
                ASSERT_EQ(gt[i], vec[i]);
            }

            el = t.get<int>();
            gt[p] = el;
            vec.push_back(el);

            if(state[idx + 1].idx <= p + 1)
                idx++;
        }
    }
}
