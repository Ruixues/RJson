#pragma once
#include "RJsonObject.h"
#include "type.h"
namespace RJSON {
class String:public RJSON::RJsonValue{
private:
    std::wstring data;
public:
    NodeType getType() { return TypeString; }
    std::wstring getString() { return data; }
    String(std::wstring data):data(data){}
};
}