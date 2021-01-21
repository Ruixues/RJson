#pragma once
#include "RJsonObject.h"
#include <any>
#include <bits/stdint-intn.h>
#include "type.h"
namespace RJSON {
enum NumberType {
    Int64,
    Double,
};
class Number:public RJsonValue {
private:
    NumberType NumberType;
    std::any data;
public:
    NodeType getType() { return TypeNumber; }
    Number (int64_t data):data(data){
        NumberType = Int64;
    }
    Number (double data):data(data){
        NumberType = Double;
    }
    enum NumberType GetType () {
        return this->NumberType;
    }
    double ToDouble() {
        if (this->NumberType == Double) {
            return std::any_cast<double>(this->data);
        }
        if (this->NumberType == Int64) {
            return std::any_cast<int64_t>(this->data);
        }
        return 0;
    }
    int64_t ToInt64() {
        if (this->NumberType == Double) {
            return std::any_cast<double>(this->data);
        }
        if (this->NumberType == Int64) {
            return std::any_cast<int64_t>(this->data);
        }
        return 0;
    }
};
}