#include "executable.h"
#include "datum_utils.h"
#include <sstream>

TEST(datum_read_data) {
    Typegen t;
    for(int i = 0; i < 100; i++) {
        std::vector<DatumGT> gt_data = generate_file_data(t);
    
        std::stringstream ss;
        ss << gt_data;

        Vector<Datum> data = readData(ss);

        ASSERT_EQ(gt_data.size(), data.size());
        
        for(size_t i = 0; i < gt_data.size(); i++) {
            Datum const & datum = data[i];
            Datum const & gt_datum = gt_data[i].datum;

            ASSERT_TRUE(gt_datum.week == datum.week);
            ASSERT_EQ(gt_datum.negative,   datum.negative);
            ASSERT_EQ(gt_datum.positive,   datum.positive);
            ASSERT_EQ(gt_datum.total,      datum.total);
            ASSERT_NEAR(gt_datum.positivity, datum.positivity, 1e-2);
        }
    }
}
