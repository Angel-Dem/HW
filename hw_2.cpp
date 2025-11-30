#pragma once
#include <string>
#include "singleton.h"
#include "wrapper.h"
#include <vector>
#include <iostream>

int TrackedString::counter = 0;
int main() {
    auto& logger = Singleton::getInstance("logfile.txt");

    logger.setLevel(Singleton::Level::DEBUG);

    // logger.log("Старт программы", Singleton::Level::INFO);
    // logger.log("Предупреждение: что-то странное", Singleton::Level::WARNING);
    // logger.log("Ошибка: что-то сломалось", Singleton::Level::ERROR);
    // logger.log("Отладочная информация", Singleton::Level::DEBUG);
    //
    TrackedString a;
    TrackedString b("hello");
    std::string s = "world";
    TrackedString c(s);
    TrackedString d = c;

    // Wrapper w1("hello");
    // Wrapper w2("world");

    // TrackedString x;        // вызывает delegating default → main
    // TrackedString y("test"); // вызывает delegating const char* → main

    // std::vector<TrackedString> vec;
    // vec.push_back(TrackedString("temp"));
    // TrackedString ts("str");
    // vec.push_back(ts);
    // vec.emplace_back("emplaced");

    // TrackedString a("hello");
    // TrackedString b("world");
    // std::cout << a << " " << b << std::endl;
    // auto c = a + b;

    return 0;
}

