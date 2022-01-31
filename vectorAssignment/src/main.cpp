#include "Datum.h"
#include "Vector.h"
#include <fstream>

int main() {
    Vector<Datum> data;
    std::string filepath;
    std::cout << "Enter Path to COVID-19 Data File: ";
    std::cin >> filepath;

    std::ifstream file(filepath.c_str());

    if(!file.is_open()) {
        std::cerr << "Could not open the file " << filepath << std::endl;
        return 1;
    }

    try {
        data = readData(file);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "It appears that the file could not be read." << std::endl;
        return 1;
    }

    bool dataIsGood = goodData(data);
    std::cout << "Data Audit for '" << filepath << '\''
            << "\n\tNumber of Entries: " << data.size()
            << "\n\tAll Entries Are Good?: " << std::boolalpha << dataIsGood
            << (dataIsGood ? "" : "\n\tListing Bad Entries:");
    if (!dataIsGood) {
        for (auto& entry : badDataEntries(data)) {
            std::cout << "\n\t\t" << entry;
        }
    }
    return 0;
}
