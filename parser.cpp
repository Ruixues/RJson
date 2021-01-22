#include "parser.h"
#include "RJsonObject.h"
#include "reader.h"
#include "type.h"
#include "number.h"
#include "string.h"
#include "bool.h"
#include "null.h"
#include <any>
#include <memory>
#include <string>
namespace RJSON {
    std::shared_ptr<RJsonValue> Parser::StartParse() {
        // Start to parse the document
        std::shared_ptr<tokenElement> token = this->reader->readAToken();
        return this->parsePrimary(token);
    }
    std::shared_ptr<RJsonObject> Parser::parseObject() {
        auto object = std::make_unique<RJsonObject>();
        auto token = this->reader->readAToken();
        while (token->type != END_OBJECT) {
            if (token->type != STRING) {
                throw ("it must be string for index");
            }
            std::wstring index = std::any_cast<std::wstring>(token->data);
            token = this->reader->readAToken();
            if (token->type != SEP_COLON) {
                throw ("need ':' to access");
            }
            auto val = this->parsePrimary(this->reader->readAToken());
            if (!val) {
                return nullptr;
            }
            // the next token must be , or }
            token = this->reader->getNowToken();
            if (token->type != END_OBJECT && token->type != SEP_COMMA) {
                throw ("unexpect value");
            }
            if (token->type == SEP_COMMA) {
                token = this->reader->readAToken(); //eat ,
            }
            // insert the value
            object->SetItem(index, val);
        }
        this->reader->readAToken(); // eat }
        return object;
    }
    std::shared_ptr<RJsonValue> Parser::parsePrimary(std::shared_ptr<tokenElement> token) {
        if (token->type == NUMBER) {
            this->reader->readAToken();
            return std::shared_ptr<Number>(std::any_cast<Number*>(token->data));
        }
        if (token->type == NULL_) {
            this->reader->readAToken();
            return std::make_shared<class NULL_>();
        }
        if (token->type == STRING) {
            this->reader->readAToken();
            return std::make_shared<String>(std::any_cast<std::wstring>(token->data));
        }
        if (token->type == BOOLEAN) {
            this->reader->readAToken();
            return std::make_shared<Bool>(std::any_cast<bool>(token->data));
        }
        if (token->type == BEGIN_OBJECT) {
            return this->parseObject();
        }
        if (token->type == BEGIN_ARRAY) {
            return this->parseArray();
        }
        return nullptr;
    }
    std::shared_ptr<RJsonArray> Parser::parseArray() {
        auto array = std::make_unique<RJsonArray>();
        while (this->reader->getNowToken()->type != END_ARRAY) {
            auto element = this->parsePrimary(this->reader->readAToken());
            if (!element) {
                return nullptr;
            }
            array->append(element);
            if (this->reader->getNowToken()->type == SEP_COMMA) {
                this->reader->readAToken();
                continue ;
            } else if (this->reader->getNowToken()->type != END_ARRAY) {
                throw ("expect , or ]");
            }
        }
        this->reader->readAToken(); // eat ]
        return array;
    }
} // namespace RJSON