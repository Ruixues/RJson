#pragma once
#include "type.h"
#include <cstddef>
#include <type_traits>
#include <string>
#include <memory>
#include <map>
#include <vector>
namespace RJSON {
    /*
        RJsonObject
    */
    class RJsonValue {
        virtual NodeType getType() = 0;
    };
    class RJsonObject:public RJsonValue {
    private:
        std::map<std::wstring,std::shared_ptr<RJsonValue>> kv;
    public:
        NodeType getType() { return TypeObject; }
        bool SetItem (std::wstring key,std::shared_ptr<RJsonValue> value);
        std::shared_ptr<RJsonValue> getItem(std::wstring key);
    };
    class RJsonArray:public RJsonValue {
    private:
        std::vector<std::shared_ptr<RJsonValue>> vals;
    public:
        NodeType getType() { return TypeArray; }
        void append(std::shared_ptr<RJsonValue> val);
        std::shared_ptr<RJsonValue> operator [](size_t index);
    };
}
template<typename T>
T GetValue() {

}