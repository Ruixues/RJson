#pragma once
#include "type.h"
#include <type_traits>
namespace RJSON {
    /*
        RJsonObject
    */
    class Parser {
    private:
        wchar_t readChar();
    public:
    };
    class RJsonObject {
    private:
        NodeType type;
    public:
        NodeType Type() { return type; }
        template<typename T>
        T GetValue();
    };
}
template<typename T>
T GetValue() {

}