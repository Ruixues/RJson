#include "reader.h"
#include <ios>
#include <memory>
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
    std::unique_ptr<Number> Reader::readNumber() {
        // 解析数字
        
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
    std::unique_ptr<tokenElement> FileReaderWriter::readAToken() {
        while (this->lastChar == L' ') {
            this->lastChar = read();
        }
        if (this->lastChar == L'{') {   //Start of object
            return std::make_unique<tokenElement>(BEGIN_OBJECT,nullptr);
        }
        if (this->lastChar == L'}') {
            return std::make_unique<tokenElement>(END_OBJECT,nullptr);
        }
        if (this->lastChar == L'[') {
            return std::make_unique<tokenElement>(BEGIN_ARRAY,nullptr);
        }
        if (this->lastChar == L']') {
            return std::make_unique<tokenElement>(END_ARRAY,nullptr);
        }
        if (this->lastChar == L'n') {
            // Must be null
            if (!isWord(L"ull")) {
                return nullptr;
            }
            return std::make_unique<tokenElement>(NULL_,nullptr);
        }
        if (this->lastChar == L't') {
            if (!isWord(L"rue")) {
                return nullptr;
            }
            return std::make_unique<tokenElement>(BOOLEAN,true);
        }
        if (this->lastChar == L'f') {
            if (!isWord(L"alse")) {
                return nullptr;
            }
            return std::make_unique<tokenElement>(BOOLEAN,false);
        }
        if (this->lastChar == L'"') {
            // String,start to read the string
            
        }
        return nullptr;
    }
}