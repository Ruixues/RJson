#pragma once
#include "RJsonObject.h"
namespace RJSON {
    class NULL_:public RJsonValue {
    public:
        NodeType getType() { return TypeNULL; }
    };
}