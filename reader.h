#pragma once
#include <bits/stdint-intn.h>
#include <fstream>
#include <any>
#include <string>
#include <wchar.h>
#include <memory>
#include "number.h"
namespace RJSON
{
    enum Token {
        BEGIN_OBJECT,
        END_OBJECT,
        BEGIN_ARRAY,
        END_ARRAY,
        NULL_,
        NUMBER,
        STRING,
        BOOLEAN,
        SEP_COLON,
        SEP_COMMA,
    };
    
    
    class tokenElement {
    public:
        Token type;
        std::any data;
        tokenElement(Token type,std::any data):type(type),data(data){}
    };
    class Reader
    {
    private:
        std::shared_ptr<tokenElement> nowToken;
    public:
        virtual wchar_t getLastChar() = 0;
        virtual wchar_t read() = 0;
        // getNowToken have a default version.You can override it if you have a better one.
        virtual std::shared_ptr<tokenElement> getNowToken() { return this->nowToken; }
        // isWord have a default version.You can override it if you have a better one.
        virtual bool isWord(std::wstring str);
        // readAToken have a default version.You can override it if you have a better one.
        virtual std::shared_ptr<tokenElement> readAToken();
        // readString is a default version.You can override it if you have a better one.
        virtual std::wstring readString();
        // readNumber is a default version.You can override it if you have a better one.
        virtual class Number* readNumber();
    };
    class Writer
    {
    public:
        virtual bool write(wchar_t data) = 0;
    };
    class FileReaderWriter:public Reader,public Writer
    {
    private:
        std::wfstream f;
        wchar_t lastChar = L' ';
    public:
        FileReaderWriter(std::string fileName);
        wchar_t read ();
        bool write(wchar_t data);
        wchar_t getLastChar();
    };
} // namespace RJSON