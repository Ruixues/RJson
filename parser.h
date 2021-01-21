#pragma once
#include <memory>
#include "RJsonObject.h"
#include "reader.h"
namespace RJSON
{
    class Parser {
    private:
        std::unique_ptr<Reader> reader;
        std::shared_ptr<RJsonValue> parsePrimary(std::shared_ptr<tokenElement>);
        std::shared_ptr<RJsonObject> parseObject();
        std::shared_ptr<RJsonArray> parseArray();
    public:
        Parser(std::unique_ptr<Reader> reader):reader(std::move(reader)){}
        std::shared_ptr<RJsonValue> StartParse();
    };
} // namespace RJSON