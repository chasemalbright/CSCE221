#include "executable.h"
#include "datum_utils.h"

TEST(datum_good) {
    Typegen t;

    for(int i = 0; i < 100; i++) {
        std::vector<DatumGT> gt_data = generate_file_data(t, true);
        Vector<Datum> data = get_data_vector(gt_data);

        ASSERT_TRUE(goodData(data));
    }
}