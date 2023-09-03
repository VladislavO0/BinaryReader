#include <iostream>
#include <fstream>
#include <cstddef>
//using namespace std;

#include "DataList.h"
#include "OrderedData.h"
#include "OpenData.h"

//const size_t RECORD_SIZE = 56;

int main()
{
    //cout << "Hello world!" << endl;


    //OrderedData<int> orderedData;//{};

//    OrderedData orderedData;
//    orderedData[0][0] = 3;
//
//    std::cout << orderedData[0][0] << "\n";
//
//    std::vector<int> && a = {10, 15, 11};
//
//    orderedData.addItem(std::move(a), 0);
//
//    std::cout << orderedData[0][0] << "\t" << a.size() << "\n";
//


    OpenData openedOscill("START.BSO");
    //OpenData openedOscill("2.BSO");
    //OrderedData<int> preparedOscill(std::move(openedOscill.get()));
    OrderedData preparedOscill(std::move(openedOscill.get()));

    std::cout << "TEST1\n" << preparedOscill[0][0] << "\t" << preparedOscill[0][500] << "\n";






    std::ofstream outfile("result.csv");


    for (size_t i = 0; i < 2000; ++i) {

        outfile << preparedOscill[0][i] << ";" << preparedOscill[2][i] << '\n';
    }

    outfile.close();


    return 0;
}
