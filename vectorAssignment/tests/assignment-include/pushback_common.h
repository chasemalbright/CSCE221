#pragma once
#include <cstddef>

struct Memstate {
    size_t idx;
    size_t n_allocs;
    size_t n_frees;
    size_t capacity;
};

static const Memstate state[] = {
    // IDX  ALLOCS FREES CAPACITY
    {  0,   0,     0,    0      },
    {  1,   1,     0,    1      },
    {  2,   2,     1,    2      },
    {  3,   3,     2,    4      },
    {  5,   4,     3,    8      },
    {  9,   5,     4,    16     },
    { 17,   6,     5,    32     },
    { 32,   0,     0,    0      }
};

static const size_t n = sizeof(state) / sizeof(*state);
static const size_t last_idx = state[n - 1].idx;

#define ASSERT_MEMSTATE(pushes, vec, state, gt, memhook, check_cap) \
    do {                                                 \
        ASSERT_EQ(pushes,          vec.size());          \
        ASSERT_EQ(state.capacity,  vec.capacity());      \
        ASSERT_EQ(state.n_allocs,  m.n_allocs());        \
        ASSERT_EQ(state.n_frees,   m.n_frees());         \
                                                         \
        if(state.capacity != 0 && check_cap) {           \
            ASSERT_EQ(                                   \
                state.capacity * sizeof(gt[0]),          \
                memhook.last_alloc().size                \
            );                                           \
        }                                                \
                                                         \
    } while(0)
