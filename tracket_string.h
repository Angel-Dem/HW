#include <string>
#include "singleton.h"

class TrackedString {
    std::string value;
    static int counter; //счетчик создаваемых объктов
    int id;
public:
    //конструктор по умолчанию
    TrackedString() : value(""), id(counter) {
        //в логер передаем какое-то инфо - мэсседж
        //
        Singleton::getInstance().log(
            "[default ctor] id= " + std::to_string(id) +
            " this= " + pointerToString(this),
            Singleton::Level::INFO
        );
    }
    //конструктор из std::string;
    TrackedString(const std::string& str) : value(str), id(counter) {
        Singleton::getInstance().log(
            "[string ctor] id= " + std::to_string(id)+
            " this= " + pointerToString(this) +
            " value=" + value,
            Singleton::Level::INFO
        );
    }
    //конструктор из const char*;
    TrackedString(const char* str) : value(str), id(counter) {
        Singleton::getInstance().log(
            "[char ctor] id= " + std::to_string(id)+
            " this= " + pointerToString(this) +
            " value=" + value,
            Singleton::Level::INFO
        );
    }
    //копирующий конструктор
    TrackedString(const TrackedString& other) {
        this->value = other.value;
        this->id = other.id;
        Singleton::getInstance().log(
        "[copy ctor] id= " + std::to_string(id)+
        " this= " + pointerToString(this) +
        " from id = " + std::to_string(other.id),
        Singleton::Level::INFO
        );
    }
    ~TrackedString() {
        Singleton::getInstance().log(
            "[dtor] id=" + std::to_string(id) +
            " this=" + pointerToString(this),
            Singleton::Level::INFO
        );
    }
    // вывод адреса
    static std::string pointerToString(const void* p) {
        std::ostringstream oss;
        oss << p;
        return oss.str();
    }
};