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
    //
    // // Основной конструктор — сюда делегируют другие
    // TrackedString(const std::string& s)
    //     : value(s)
    // {
    //     Singleton::getInstance().log(
    //         "[TrackedString ctor main] this=" + pointerToString(this) +
    //         " data=\"" + value + "\"",
    //         Singleton::Level::INFO
    //     );
    // }
    //
    // // Делегирование к основному конструктору
    // TrackedString()
    //     : TrackedString(std::string(""))
    // {
    //     Singleton::getInstance().log(
    //         "[TrackedString ctor delegating default] this=" + pointerToString(this),
    //         Singleton::Level::INFO
    //     );
    // }
    //
    // // Делегирование через const char* → std::string → основной ctor
    // TrackedString(const char* s)
    //     : TrackedString(std::string(s))
    // {
    //     Singleton::getInstance().log(
    //         "[TrackedString ctor delegating const char*] this=" +
    //         pointerToString(this) + " arg=\"" + s + "\"",
    //         Singleton::Level::INFO
    //     );
    // }
    //
    // //копирующий конструктор
    // TrackedString(const TrackedString& other) {
    //     this->value = other.value;
    //     this->id = other.id;
    //     Singleton::getInstance().log(
    //     "[copy ctor] id= " + std::to_string(id)+
    //     " this= " + pointerToString(this) +
    //     " from id = " + std::to_string(other.id),
    //     Singleton::Level::INFO
    //     );
    // }
    //
    // friend std::ostream& operator<<(std::ostream& os, const TrackedString& ts) {
    //     Singleton::getInstance().log(
    //         "[operator<<] id=" + std::to_string(ts.id) +
    //         " this=" + pointerToString(&ts) +
    //         " value=\"" + ts.value + "\"",
    //         Singleton::Level::INFO
    //     );
    //
    //     os << ts.value; // в поток выводим только сам текст
    //     return os;
    // }
    //
    // friend bool operator==(const TrackedString& a, const TrackedString& b) {
    //     Singleton::getInstance().log(
    //         "[operator==] a.id=" + std::to_string(a.id) +
    //         " b.id=" + std::to_string(b.id) +
    //         " a.value=\"" + a.value + "\"" +
    //         " b.value=\"" + b.value + "\"",
    //         Singleton::Level::INFO
    //     );
    //
    //     return a.value == b.value;
    // }
    //
    // friend bool operator!=(const TrackedString& a, const TrackedString& b) {
    //     Singleton::getInstance().log(
    //         "[operator!=] a.id=" + std::to_string(a.id) +
    //         " b.id=" + std::to_string(b.id) +
    //         " a.value=\"" + a.value + "\"" +
    //         " b.value=\"" + b.value + "\"",
    //         Singleton::Level::INFO
    //     );
    //
    //     return a.value != b.value;
    // }
    //
    // friend bool operator<(const TrackedString& a, const TrackedString& b) {
    //     Singleton::getInstance().log(
    //         "[operator<] a.id=" + std::to_string(a.id) +
    //         " b.id=" + std::to_string(b.id) +
    //         " a.value=\"" + a.value + "\"" +
    //         " b.value=\"" + b.value + "\"",
    //         Singleton::Level::INFO
    //     );
    //
    //     return a.value < b.value;
    // }
    // friend TrackedString operator+(const TrackedString& a, const TrackedString& b) {
    //     Singleton::getInstance().log(
    //         "[operator+] begin a.id=" + std::to_string(a.id) +
    //         " b.id=" + std::to_string(b.id) +
    //         " a.value=\"" + a.value + "\"" +
    //         " b.value=\"" + b.value + "\"",
    //         Singleton::Level::INFO
    //     );
    //
    //     TrackedString result(a.value + b.value);
    //
    //     Singleton::getInstance().log(
    //         "[operator+] result id=" + std::to_string(result.id) +
    //         " this=" + pointerToString(&result) +
    //         " value=\"" + result.value + "\"",
    //         Singleton::Level::INFO
    //     );
    //
    //     return result;
    // }

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