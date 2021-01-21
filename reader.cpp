#include "reader.h"
#include "number.h"
#include "type.h"
#include <ios>
#include <memory>
#include <string>
namespace RJSON {
    FileReaderWriter::FileReaderWriter(std::string fileName) {
        this->f.open(fileName.c_str());
        if (this->f.bad ()) {
            throw ("error file");
        }
        this->f << std::noskipws;
    }
    wchar_t FileReaderWriter::read () {
        if (this->f.bad ()) {
            return WEOF;
        }
        wchar_t ret;
        this->f >> ret;
        return ret;
    }
    bool FileReaderWriter::write(wchar_t data) {
        this->f << data;
        return true;
    }
    bool Reader::isWord(std::wstring str) {
        auto it = str.begin();
        do {
            if (*it != read()) return false;
        } while ((++it) != str.end());
        return true;
    }
    class Number* Reader::readNumber() {
        // 解析数字
        std::wstring val;
        val += this->getLastChar();
        wchar_t c = this->read();
        while (iswdigit(c)) {
            val += c;
            c = this->read();
        }
        if (c != L'.') {
            return new class Number(int64_t(std::stoll(val)));
        }
        // 否则那就是小数
        val += L'.';
        while (iswdigit(c)) {
            val += c;
            c = this->read();
        }
        return new class Number(std::stod(val));
    }
    std::wstring Reader::readString() {
        std::wstring res;
        bool turn = false;
        wchar_t lastChar = this->read();
        while (lastChar != L'"') {
            if (lastChar == L'\\' || lastChar == L'"') {
                if (turn) {
                    turn = false;
                    res += lastChar;
                } else if (lastChar == L'\\') {
                    turn = true;
                }
            } else {
                res += lastChar;
            }
            lastChar = read();
        }
        return res;
    }
    wchar_t FileReaderWriter::getLastChar() {
        return this->lastChar;
    }
    std::shared_ptr<tokenElement> Reader::readAToken() {
        wchar_t lastChar = this->getLastChar();
        while (lastChar == L' ') {
            lastChar = read();
        }
        if (lastChar == L'{') {   //Start of object
            return this->nowToken = std::make_shared<tokenElement>(BEGIN_OBJECT,nullptr);
        }
        if (lastChar == L'}') {
            return this->nowToken = std::make_shared<tokenElement>(END_OBJECT,nullptr);
        }
        if (lastChar == L'[') {
            return this->nowToken = std::make_shared<tokenElement>(BEGIN_ARRAY,nullptr);
        }
        if (lastChar == L']') {
            return this->nowToken = std::make_shared<tokenElement>(END_ARRAY,nullptr);
        }
        if (lastChar == L':') {
            return this->nowToken = std::make_shared<tokenElement>(SEP_COLON,nullptr);
        }
        if (lastChar == L',') {
            return this->nowToken = std::make_shared<tokenElement>(SEP_COMMA,nullptr);
        }
        if (lastChar == L'n') {
            // Must be null
            if (!isWord(L"ull")) {
                return nullptr;
            }
            return this->nowToken = std::make_shared<tokenElement>(NULL_,nullptr);
        }
        if (lastChar == L't') {
            if (!isWord(L"rue")) {
                return nullptr;
            }
            return this->nowToken = std::make_shared<tokenElement>(BOOLEAN,true);
        }
        if (lastChar == L'f') {
            if (!isWord(L"alse")) {
                return nullptr;
            }
            return this->nowToken = std::make_shared<tokenElement>(BOOLEAN,false);
        }
        if (lastChar == L'"') {
            // String,start to read the string
            return this->nowToken = std::make_shared<tokenElement>(STRING,this->readString());
        }
        if (iswdigit(lastChar)) {
            return this->nowToken = std::make_shared<tokenElement>(NUMBER,this->readNumber());
        }
        return nullptr;
    }
}