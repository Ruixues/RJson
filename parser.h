#pragma once
#include <memory>
#include "RJsonObject.h"
namespace RJSON
{
    std::unique_ptr<RJsonObject> parseObject();
} // namespace RJSON