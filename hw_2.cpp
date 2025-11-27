#pragma once
#include <string>
#include "singleton.h"


int main() {
    auto& logger = Singleton::getInstance("logfile.txt");

    logger.setLevel(Singleton::Level::DEBUG);

    logger.log("Старт программы", Singleton::Level::INFO);
    logger.log("Предупреждение: что-то странное", Singleton::Level::WARNING);
    logger.log("Ошибка: что-то сломалось", Singleton::Level::ERROR);
    logger.log("Отладочная информация", Singleton::Level::DEBUG);

    return 0;
}

