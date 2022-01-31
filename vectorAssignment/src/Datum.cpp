#include <cmath>
#include <fstream>
#include <sstream>

#include "Datum.h"

// You may want to write this function, but you do not have to
//[[nodiscard]] bool isBadDataEntry(const Datum& datum);

std::ostream &operator<<(std::ostream &out, const Datum &datum)
{
}

std::istream &operator>>(std::istream &in, Datum &datum)
{

    std::string week1;
    std::string negative1;
    std::string positive1;
    std::string total1;
    std::string percent1;

    getline(in, week1, ',');
    datum.week = week1;

    getline(in, negative1, ',');
    datum.negative = std::stoi(negative1);

    getline(in, positive1, ',');
    datum.positive = std::stoi(positive1);

    getline(in, total1, ',');
    //total1.pop_back();
    datum.total = std::stoi(total1);

    getline(in, percent1, '%');
    datum.positivity = std::stof(percent1);

    return in;
}

[[nodiscard]] Vector<Datum> readData(std::istream &file)
{

    // std::string fileName;
    // std::cin >> fileName;

    Vector<Datum> data;

    //std::ifstream ifs(fileName);
    int lines = 0;
    std::string line;

    while (getline(file, line))
    {
        if (lines >= 1)
        {
            if (file.eof())
                break;
            std::stringstream ss(line);

            Datum temp;
            ss >> temp;

            data.push_back(temp);
        }
        lines++;
    }

    return data;
}

[[nodiscard]] Vector<Datum> badDataEntries(const Vector<Datum> &data) noexcept {

    Vector<Datum> bad;

    for (size_t i = 0; i < data.size(); i++){

        Datum temp = data[i];
        float correctPos = ((float)temp.positive/(float)temp.total) * 100;
        int correctTotal = temp.positive + temp.negative;

        if (std::abs(correctPos - temp.positivity) > 0.1 || correctTotal != temp.total){
            bad.push_back(temp);
        }


    }

    return bad;

}

[[nodiscard]] bool goodData(const Vector<Datum> &data) noexcept {
    Vector<Datum> temp;

    temp = badDataEntries(data);

    if (temp.empty() == true){
        return true;
    } else {
        return false;
    }
}