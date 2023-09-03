#ifndef ORDEREDDATA_H_INCLUDED
#define ORDEREDDATA_H_INCLUDED

#include <vector>
#include <algorithm>
#include <cmath>

#include "DataList.h"


#include <iostream>

//template <typename T>
class OrderedData
{
    using type_t        = int;//T;
    using type_vec_t    = std::vector<type_t>;
    using type_matrix_t = std::vector<type_vec_t>;

public:
    OrderedData()
    : data(std::move(defaultData()))
    {
        std::cout << "Here0\n";
    };

    OrderedData(const type_matrix_t& input)
    : data(input)
    {
        std::cout << "Here1\n";
    };


    OrderedData(type_matrix_t&& input)
    : data(std::move(input))
    {
        std::cout << "Here2\n";
    };

    virtual ~OrderedData(){ };

    void calculate() {

        using namespace WAVETYPE;

        for (size_t i = 0; i < RECORDS; ++i) {

            //Вычисленные значения косинусов
            data[static_cast<size_t>(CALC::COS)][i] =
                getCos(data[static_cast<size_t>(BASE::ANGLE_VALUE)][i]);

            //Вычисленные значения синусов
            data[static_cast<size_t>(CALC::SIN)][i] =
                getSin(data[static_cast<size_t>(BASE::ANGLE_VALUE)][i]);

            //Активная составляющая тока
            data[static_cast<size_t>(CALC::CURRENT_STATOR_RE)][i]  =
                data[static_cast<size_t>(BASE::CURRENT_STATOR)][i] *
                data[static_cast<size_t>(CALC::COS)][i]            ;

            //Реактивная составляющая тока
            data[static_cast<size_t>(CALC::CURRENT_STATOR_IM)][i]  =
                data[static_cast<size_t>(BASE::CURRENT_STATOR)][i] *
                data[static_cast<size_t>(CALC::SIN)][i]            ;

            //Полная мощность
            data[static_cast<size_t>(CALC::POWER_STATOR_FULL)][i]  =
                data[static_cast<size_t>(BASE::VOLTAGE_STATOR)][i] *
                data[static_cast<size_t>(BASE::CURRENT_STATOR)][i] *
                getSqrt3();

            //Активная мощность
            data[static_cast<size_t>(CALC::POWER_STATOR_RE)][i]       =
                data[static_cast<size_t>(CALC::POWER_STATOR_FULL)][i] *
                data[static_cast<size_t>(CALC::COS)][i];

            //Реактивная мощность
            data[static_cast<size_t>(CALC::POWER_STATOR_RE)][i]       =
                data[static_cast<size_t>(CALC::POWER_STATOR_FULL)][i] *
                data[static_cast<size_t>(CALC::SIN)][i];

        }
    };


    void addItem(const type_vec_t& input, size_t index) {
        data[index] = input;
    };
    void addItem(type_vec_t&& input, size_t index) {
        std::swap(data[index], input);
    };
    void addItem(type_matrix_t&& input) {
        std::swap(data, input);
    };

    std::vector<type_t>& operator[](size_t index) {
        return data[index];
    };

private:

    type_matrix_t data;

    //Вычисление значения косинуса
    double getCos(double input) {
        return std::cos(input * degToRad()) ;
    };

    //Вычисление значения синуса
    double getSin(double input) {
        return std::sin(input * degToRad()) ;
    };

    //Дефолтное значение вектора
    type_matrix_t defaultData() {

        using namespace WAVETYPE;

        type_matrix_t output(static_cast<size_t>(CALC::LAST));

        for (BASE i = BASE::FIRST; i < BASE::LAST; ++i) {
            output[static_cast<size_t>(i)] = type_vec_t(getDataSize(), 0);
        }

        for (HIGH i = HIGH::FIRST; i < HIGH::LAST; ++i) {
            output[static_cast<size_t>(i)] = type_vec_t(getHighSize(), 0);
        }

        for (CALC i = CALC::FIRST; i < CALC::LAST; ++i) {
            output[static_cast<size_t>(i)] = type_vec_t(getDataSize(), 0);
        }

        return output;

    };

    //Множитель для пересчета градусов в радианы
    static constexpr double degToRad() {
        return std::acos(-1.0) / 180.0;
    };

   //Размер обычного вектора сигналов
    static constexpr size_t getDataSize() {
        return 2000;
    };

    //Размер вектора сигналов 6-й гармоники
    static constexpr size_t getHighSize() {
        return 6 * getDataSize();
    };

    static constexpr double getSqrt3() {
        return std::sqrt(3.0);
    }


};


#endif // ORDEREDDATA_H_INCLUDED
