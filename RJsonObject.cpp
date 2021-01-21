#include "RJsonObject.h"
#include <memory>

namespace RJSON {
    bool RJsonObject::SetItem (std::wstring key,std::shared_ptr<RJsonValue> value) {
        this->kv [key] = value;
        return true;
    }
    std::shared_ptr<RJsonValue> RJsonObject::getItem(std::wstring key) {
        if (this->kv.find(key) == this->kv.end()) {
            return nullptr;
        }
        return kv[key];
    }
    void RJsonArray::append(std::shared_ptr<RJsonValue> val) {
        this->vals.push_back(val);
    }
    std::shared_ptr<RJsonValue> RJsonArray::operator [](size_t index) {
        if (this->vals.size() <= index) {
            return nullptr;
        }
        return this->vals [index];
    }
}