#pragma once

// COMMON HEADER FOR ISOLATED EXECUTABLE
// E.G. TESTS ISOLATED TO THEIR OWN TRANSLATION
// UNIT TO RELAX LINKAGE REQUIREMENTS

// Include utilities from utest
#include "utest.h"
// Include custom insertions
#include "assertions.h"
// Track memory allocations
#include "memhook.h"
// Deterministic type generator
#include "typegen.h"
// Include source file
#include "List.h"
// Additional iterator method
#include "pace.h"
// Override random generator for testing
#include "deck.h"

#define TEST(name) UTEST(SORT, name)

size_t constexpr TEST_ITER = 100;

// Setup main file
UTEST_MAIN()