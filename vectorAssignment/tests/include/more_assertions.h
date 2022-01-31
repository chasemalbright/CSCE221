#pragma once

#define ASSERT_THROWS(statement, exception) \
    do {                                    \
        try {                               \
            (statement);                    \
            ASSERT_TRUE(false);             \
        } catch (const exception & e) {     \
            ASSERT_TRUE(true);              \
        }                                   \
    } while(0)
