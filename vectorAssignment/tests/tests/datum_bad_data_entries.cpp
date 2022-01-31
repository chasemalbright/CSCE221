#include "executable.h"
#include "datum_utils.h"

TEST(datum_bad_data_entries) {
    Typegen t;

    for(int i = 0; i < 100; i++) {
        std::vector<DatumGT> gt_data = generate_file_data(t);
        Vector<Datum> data = get_data_vector(gt_data);
        std::vector<Datum> known_bad_data = get_bad_entires(gt_data);


        Vector<Datum> bad_entries = badDataEntries(data);

        ASSERT_EQ(known_bad_data.size(), bad_entries.size());

        for(size_t i = 0; i < known_bad_data.size(); i++) {
            Datum const & datum = bad_entries[i];
            Datum const & gt_datum = known_bad_data[i];

            ASSERT_TRUE(gt_datum.week == datum.week);
            ASSERT_EQ(gt_datum.negative,   datum.negative);
            ASSERT_EQ(gt_datum.positive,   datum.positive);
            ASSERT_EQ(gt_datum.total,      datum.total);
            ASSERT_NEAR(gt_datum.positivity, datum.positivity, 1e-4);
        }
    }
}
