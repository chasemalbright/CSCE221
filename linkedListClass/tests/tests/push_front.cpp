#include "executable.h"
#include "box.h"

#include <vector>

TEST(push_front) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {

        const size_t n = t.range(0x999ULL);
        std::vector<int> gt(n);
        t.fill(gt.begin(), gt.end());

        {
            // uses modified new to catch uninitalized memory
            List<int> * ll = new List<int>();

            Memhook mh;

            for(size_t i = 0; i < n; i++)
                ll->push_front(gt[i]);

            // Ensure nodes have been allocated
            ASSERT_EQ(n, mh.n_allocs());
            ASSERT_EQ(n, ll->size());

            auto it = ll->cend();
            size_t j = 0;
            while(it != ll->cbegin())
                ASSERT_EQ_(gt[j++], (*--it), "An inconsistency was found when iterating forward");

            while(it != ll->cend())
                ASSERT_EQ_(gt[--j], (*it++), "An inconsistency was found when iterating backward");

            delete ll;

            // Allocated memory should be freed
            ASSERT_EQ(n, mh.n_scoped_frees());
        }

        {
            // uses modified new to catch uninitalized memory
            List<Box<int>> * ll = new List<Box<int>>();

            std::vector<Box<int>> boxes(n);
            for(size_t i = 0; i < n; i++)
                boxes[i] = gt[i];

            Memhook mh;

            for(size_t i = 0; i < n; i++)
                ll->push_front(std::move(boxes[i]));

            // Ensure nodes have been allocated
            // Allocations shouldn't occur for other
            // memory
            ASSERT_EQ(n, mh.n_allocs());
            ASSERT_EQ(n, ll->size());

            auto it = ll->cend();
            size_t j = 0;
            while(it != ll->cbegin())
                ASSERT_EQ_(gt[j++], **--it, "An inconsistency was found when iterating forward");

            while(it != ll->cend())
                ASSERT_EQ_(gt[--j], **it++, "An inconsistency was found when iterating backward");
            
            delete ll;

            // Allocated memory should be freed
            ASSERT_EQ(n, mh.n_scoped_frees());
            ASSERT_EQ(2 * n + 1, mh.n_frees());
        }
    }
    
}
