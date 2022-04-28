#include "executable.h"

TEST(ec_optimized_list) {
    using iter = UnorderedMap<double, int>::iterator;

    ASSERT_TRUE(sizeof(iter) == sizeof(void *));
}