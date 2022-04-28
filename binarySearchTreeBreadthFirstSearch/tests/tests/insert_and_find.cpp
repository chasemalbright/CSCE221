#include "generate_tree_data.h"
#include "executable.h"

TEST(insert_and_find) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {
        int lower = t.range(0, 250);
        int upper = lower + t.range(1, 250);

        depth_list<int> dlist = generate_tree_data(t, lower, upper);

        Memhook mh;
        
        {
            BinarySearchTree<int, int> tree;
            size_t expected_sz = 0;
            for(auto & [key, depth] : dlist) {
                int d = t.range(1, 10);

                {
                    Memhook mh;
                    tree.insert({key, d * key});
                    ASSERT_EQ(1ULL, mh.n_allocs());
                }
                
                {
                    Memhook mh;
                    ASSERT_VALUE_IN_TREE(d * key, tree, key);
                    
                    ASSERT_EQ(0ULL, mh.n_allocs());
                    ASSERT_EQ(0ULL, mh.n_frees());
                }

                ASSERT_EQ(++expected_sz, tree.size());
            }
        }
        
        ASSERT_EQ(mh.n_allocs(), mh.n_frees());
    }
}