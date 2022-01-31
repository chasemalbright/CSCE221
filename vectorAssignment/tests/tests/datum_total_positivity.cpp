#include "executable.h"
#include "datum_utils.h"

TEST(datum_total_positivity) {
    Typegen t;

    for(int i = 0; i < 100; i++) {
        DatumGT const gt_datum = DatumGT::generate(t);

        ASSERT_EQ(gt_datum.real_total, gt_datum.datum.compute_total());
        ASSERT_NEAR((gt_datum.real_positivity / 100.0), gt_datum.datum.compute_positivity(), 1e-2);
    }
}
