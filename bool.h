#pragma once

#include "RJsonObject.h"
#include "type.h"
namespace RJSON {
class Bool:public RJsonValue{
private:
    bool val;
public:
    NodeType getType() { return TypeBool; }
    Bool (bool val):val(val) {}
    explicit operator bool() { return this->val; }
    Bool operator =(bool val) {
        this->val = val;
        return *this;
    }
};
}