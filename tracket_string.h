#include <string>
#include "Logger.h"

class TrackedString {
    std::string value;
    static int counter;
    int id;
public:
    TrackedString() : value(""), id(counter) {
        Logger::getInstance().log(
        Logger::Level::INFO,
            "[default ctor] id=" + std::to_string(id) +
            " this=" + pointerToString(this)
        );
    }
};