#include <fstream>
#include "NumberWithUnits.hpp"
#include <string>
using namespace std;


namespace ariel{

    NumberWithUnits::NumberWithUnits(double value,const std::string& units){
        if(data.count(units) == 0){
            throw invalid_argument {"unit isn't included in the file"};
        }
        this->val = value;
        this->unit = units;
    }

    void NumberWithUnits::read_units(ifstream & file){
        string first_elem;
        string eq;
        string sec_elem;
        double first_value = 0;
        double sec_value = 0;
        while(file >> first_value >> first_elem >> eq >> sec_value >> sec_elem) {
            data[first_elem][sec_elem] = sec_value;
            data[sec_elem][first_elem] = first_value/sec_value;

            for(auto &unit: data[sec_elem]) {
                double value = data[first_elem][sec_elem] * unit.second;
                if(value == 1){
                    continue;
                }
                data[first_elem][unit.first] = value;
                data[unit.first][first_elem] = 1/value;  
            }

            for(auto &unit : data[first_elem]) {
                double value = data[sec_elem][first_elem] * unit.second;
                if(value == 1){
                    continue;
                }
                data[sec_elem][unit.first] = value;
                data[unit.first][sec_elem] = 1/value; 
            }

        }
    }

    double conversion(const string& in ,const string& from ,double value) {
        if(from == in){
            return value;
        }
        try {
            return data.at(from).at(in)*value;
        }
        catch(const exception& e) {throw invalid_argument {"units aren't fit"};}
        }


    NumberWithUnits &NumberWithUnits::operator--(){
        this->val--;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int){
        NumberWithUnits copy = *this;
        --*this;
        return copy;
    }

    NumberWithUnits &NumberWithUnits::operator++(){
        this->val++;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++(int){
        NumberWithUnits copy = *this;
        ++*this;
        return copy;
    }

    NumberWithUnits operator*(const NumberWithUnits& n, double num){
        return NumberWithUnits{num*n.val,n.unit};
    }
    NumberWithUnits operator*(double num,const NumberWithUnits& n){
        return NumberWithUnits{num*n.val,n.unit};
    }


    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& other){
        double value = conversion(this->unit,other.unit,other.val);
        this->val += value;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator + (const NumberWithUnits& other)const{
        double value = conversion(this->unit,other.unit,other.val);
        return NumberWithUnits{this->val+value,this->unit};
    }
    NumberWithUnits NumberWithUnits::operator + ()const{
        return *this;
    }
    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& other){
        double value = conversion(this->unit,other.unit,other.val);
        this->val -= value;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator - (const NumberWithUnits& other)const{
        double value = conversion(this->unit,other.unit,other.val);
        return NumberWithUnits{this->val-value,this->unit};
    }
    NumberWithUnits NumberWithUnits::operator - ()const{
        return NumberWithUnits {this->val*(-1) , this->unit};
    }

    bool operator==(const NumberWithUnits& a, const NumberWithUnits& b){
        const double epsilon = 0.001;
        double value = conversion(a.unit,b.unit,b.val);
        return (abs(a.val-value)<epsilon);
    }
    bool operator!=(const NumberWithUnits& a, const NumberWithUnits& b){
        return !(a==b);
    }
    bool operator>(const NumberWithUnits& a, const NumberWithUnits& b){
        double value = conversion(a.unit,b.unit,b.val);
        return a.val>value;
    }
    bool operator>=(const NumberWithUnits& a, const NumberWithUnits& b){
        return !(a<b);
    }
    bool operator<(const NumberWithUnits& a, const NumberWithUnits& b){
        double value = conversion(a.unit,b.unit,b.val);
        return a.val<value;
    }
    bool operator<=(const NumberWithUnits& a, const NumberWithUnits& b){
        return !(a>b);
    }

    ostream& operator<< (ostream& os, const NumberWithUnits& num){
        return os << num.val << "[" << num.unit << "]";
    }

    istream& operator>> (istream& is, NumberWithUnits& num){
        char ch = ' ';
        char ch1 = ' ';
        string unit = " ";
        double value = 0;
        is >> skipws >> value >> ch >> unit;

        if (unit.at(unit.length() - 1) != ']'){
            is>>ch1;
        }
        else{
            unit = unit.substr(0, unit.length() - 1);
        }
        if (data.count(unit)==0){
            throw invalid_argument("units aren't fit");
        }
        num.val = value;
        num.unit = unit;
        return is;
    }

}
