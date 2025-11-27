#include <string>
#include "Logger.h"

class TrackedString {
    std::string value;
    static int counter; //счетчик создаваемых объктов
    int id;
public:
    //конструктор по умолчанию
    TrackedString() : value(""), id(counter) {
        //в логер передаем какое-то инфо - мэсседж
        //
        Logger::getInstance().log(
            "[default ctor] id=" + std::to_string(id) +
            " this=" + pointerToString(this),
            Logger::Level::INFO
        );
    }
    //конструктор из std::string;
    TrackedString(const std::string& str) : value(str), id(counter) {
        Logger::getInstance().log(
            "[string ctor] id=" + std::to_string(id)+

        );
    }

};