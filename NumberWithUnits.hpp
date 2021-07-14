#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>

namespace ariel{

    static std::unordered_map<std::string,std::unordered_map<std::string,double>> data;

    class NumberWithUnits
    {
    private:
        double val;
        std::string unit;
    public:
        NumberWithUnits(double value,const std::string& units);
        static void read_units(std::ifstream& units_file);
      
        NumberWithUnits& operator--();
        NumberWithUnits operator--(int);
        NumberWithUnits& operator++();
        NumberWithUnits operator++(int);

        friend NumberWithUnits operator*(const NumberWithUnits& con, double num);
        friend NumberWithUnits operator*(double num,const NumberWithUnits& con);

        NumberWithUnits& operator+=(const NumberWithUnits& other);
        NumberWithUnits& operator-=(const NumberWithUnits& other);
        NumberWithUnits operator + (const NumberWithUnits& other)const;
        NumberWithUnits operator + ()const;
        NumberWithUnits operator - (const NumberWithUnits& other)const;
        NumberWithUnits operator - ()const;


        friend bool operator==(const NumberWithUnits& tr, const NumberWithUnits& fls);
        friend bool operator!=(const NumberWithUnits& tr, const NumberWithUnits& fls);
        friend bool operator>(const NumberWithUnits& tr, const NumberWithUnits& fls);
        friend bool operator>=(const NumberWithUnits& tr, const NumberWithUnits& fls);
        friend bool operator<(const NumberWithUnits& tr, const NumberWithUnits& fls);
        friend bool operator<=(const NumberWithUnits& tr, const NumberWithUnits& fls);


        friend std::ostream& operator << (std::ostream& os_str, const NumberWithUnits& num);
        friend std::istream& operator >> (std::istream& is_str, NumberWithUnits& num);
    };     
}
