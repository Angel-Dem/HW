#include "tracket_string.h"
#include "singleton.h"

class Wrapper {
    TrackedString str;
public:
    //без списка инициализации
    //Wrapper(const std::string& s); //конструктор при вызове этого класса
    //первое - имя класса, второя - имя конструктора как раз для объявления
    Wrapper(const std::string& s):str(s)
    {
        Singleton::getInstance().log(
            "[Wrapper ctor A] this=" + TrackedString::pointerToString(this),
            Singleton::Level::INFO
        );

        //str = TrackedString(s);  // ← ключевая проблемная строка
    }

};