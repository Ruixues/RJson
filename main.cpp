#include "RJsonObject.h"
#include "parser.h"
#include "reader.h"
#include "iostream"
#include "string.h"
int main () {
    auto reader = std::make_unique<RJSON::FileReaderWriter>("t.json");
    RJSON::Parser* parser = new RJSON::Parser(std::move(reader));
    auto v = parser->StartParse();
    std::wcout << ((RJSON::String*)(dynamic_cast<RJSON::RJsonObject*>(v.get())->getItem(L"main").get()))->getString() << std::endl;
    return 0;
}