#pragma once

#include "typegen.h"
#include "Datum.h"

#include <ostream>
#include <vector>

struct DatumGT {
    Datum datum;
    
    bool bad;
    float real_positivity;
    unsigned int real_total;

    static DatumGT generate(Typegen & t, bool all_good = false);
};

std::ostream & operator<<(std::ostream & s, const DatumGT & gt);
std::ostream & operator<<(std::ostream & s, const std::vector<DatumGT> & gts);

std::vector<DatumGT> generate_file_data(Typegen & t, bool all_good = false);
Vector<Datum> get_data_vector(std::vector<DatumGT> const & gt_data);
std::vector<Datum> get_bad_entires(std::vector<DatumGT> const & gt_data);