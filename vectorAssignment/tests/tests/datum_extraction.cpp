#include "executable.h"
#include "datum_utils.h"
#include <sstream>

TEST(datum_extraction) {
    Typegen t;
    
    for(int i = 0; i < 100; i++) {
        DatumGT const gt = DatumGT::generate(t);
        
        std::stringstream ss;
        ss << gt;

        Datum datum;
        ss >> datum;

        Datum const & gt_datum = gt.datum;

        ASSERT_TRUE(gt_datum.week == datum.week);
        ASSERT_EQ(gt_datum.negative,   datum.negative);
        ASSERT_EQ(gt_datum.positive,   datum.positive);
        ASSERT_EQ(gt_datum.total,      datum.total);
        ASSERT_NEAR(gt_datum.positivity, datum.positivity, 1e-2);
    }
}
