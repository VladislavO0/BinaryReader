#ifndef OPENDATA_H
#define OPENDATA_H

#include <string>
#include <fstream>
#include <vector>

#include "DataList.h"


class OpenData final
{
    using type_t        = int;
    using type_vec_t    = std::vector<int>;
    using type_matrix_t = std::vector<type_vec_t>;


public:

    OpenData(const std::string& openFile);

    ~OpenData();

    type_matrix_t& get();

    type_matrix_t open(const std::string& openFile);


private:

    type_matrix_t data;


    ///Чтение, интерпретация и запись блока данных в матрицу значений
    void readRecord(std::ifstream&, type_matrix_t&, size_t, size_t, size_t);


    ///Количество записей в одной осциллограмме
    size_t getRecordsNumber() {
        return 2000;
    };

    ///Размер одной записи в осциллограмме
    size_t getRecordsSize() {
        return 56;
    };

    ///Количество пропущенных байт с самого начала
    size_t getSkipSize() {
        return 8;
    };

    ///Номер высокочастотной гармоники
    size_t getHarmonicalNumber() {
        return 6;
    };


};

#endif // OPENDATA_H

