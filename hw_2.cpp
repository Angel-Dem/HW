#pragma once
#include <string>
#include "singleton.h"
#include "wrapper.h"

int TrackedString::counter = 0;
int main() {
    auto& logger = Singleton::getInstance("logfile.txt");

    logger.setLevel(Singleton::Level::DEBUG);

    // logger.log("Старт программы", Singleton::Level::INFO);
    // logger.log("Предупреждение: что-то странное", Singleton::Level::WARNING);
    // logger.log("Ошибка: что-то сломалось", Singleton::Level::ERROR);
    // logger.log("Отладочная информация", Singleton::Level::DEBUG);
    //
    // TrackedString a;
    // TrackedString b("hello");
    // std::string s = "world";
    // TrackedString c(s);
    // TrackedString d = c;

    Wrapper w1("hello");
    Wrapper w2("world");

    return 0;
}

