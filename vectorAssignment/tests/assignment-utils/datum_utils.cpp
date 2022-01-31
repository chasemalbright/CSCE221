#include "datum_utils.h"

#include <array>
#include <sstream>

std::ostream & operator<<(std::ostream & s, DatumGT const & gt) {
    Datum const & d = gt.datum;
    return (
        s << d.week << "," 
        << d.negative << "," 
        << d.positive << ","
        << d.total << ","
        << d.positivity << "%\n"
    );
}

std::vector<DatumGT> generate_file_data(Typegen & t, bool all_good) {
    size_t points = t.range<size_t>(0, 200);
    std::vector<DatumGT> data(points);
    for(size_t i = 0; i < points; i++)
        data.push_back(DatumGT::generate(t, all_good));
    return data;
}


DatumGT DatumGT::generate(Typegen & t, bool all_good) {
    static std::array dates {
        "Aug",
        "Sept",
        "Oct",
        "Nov",
        "Dec"
    };

    DatumGT gt;

    std::stringstream ss;
    ss << t.sample(dates.begin(), dates.end());
    ss << " ";
    ss << t.range<unsigned int>(0, 29);

    Datum & d = gt.datum;

    d.week = ss.str();
    d.negative = t.range<unsigned int>(0, 2000);
    d.positive = t.range<unsigned int>(0, 100);
    gt.real_total = d.total = d.negative + d.positive;
    gt.real_positivity = static_cast<float>(d.positive) * 100.0 / d.total;

    gt.bad = all_good ? false : t.get<bool>(0.2);

    d.positivity = gt.real_positivity;

    if(gt.bad) {
        
        if(t.get<bool>()) {
            d.positivity += t.range<float>(0.1, 0.4);
        }else {
            d.total += t.range<unsigned int>(1, 100);
        }

    } else {
        d.positivity += t.range<float>(0, 0.1);
    }

    return gt;
}



std::ostream & operator<<(std::ostream & s, const std::vector<DatumGT> & data) {
    s << "week ending,negative,positive,total,positivity (%)\n";

    for(const DatumGT & row : data)
        s << row;
    
    return s;
}

Vector<Datum> get_data_vector(std::vector<DatumGT> const & gt_data) {
    Vector<Datum> data;
    
    for(DatumGT const & d : gt_data)
        data.push_back(d.datum);
    
    return data;
}

std::vector<Datum> get_bad_entires(std::vector<DatumGT> const & gt_data) {
    std::vector<Datum> data;

    for(DatumGT const & d : gt_data) {
        if(d.bad)
            data.push_back(d.datum);
    }

    return data;
}