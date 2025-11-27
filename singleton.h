#pragma once
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "singleton.h"


class Singleton {
public:
    enum class Level {
        ERROR,
        WARNING,
        INFO,
        DEBUG
    };

    // Получение единственного экземпляра Singleton - не требует создание объекта и всегда возращает один и тот же объект
    //вне зависимости
    static Singleton& getInstance(const std::string& filename = "log.txt") { //
        static Singleton instance(filename);  // создаётся один раз - один логгер на всю программу
        return instance; //возвращается ссылка на этот объект
    }

    // Запрет копирования и присваивания
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Установка текущего уровня логирования
    void setLevel(Level lvl) {
        currentLevel = lvl;
    }

    // Основная функция логирования
    void log(const std::string& message, Level l) {
        if (l > currentLevel) {
            return; // сообщение слишком подробное — пропускаем
        }

        if (!file.is_open()) {
            throw std::runtime_error("Logger file is not open!");
        }

        file << "[" << currentTime() << "] "
             << "[" << levelToString(l) << "] "
             << message <<'\n';
    }

private:
    std::ofstream file;
    Level currentLevel = Level::INFO;
    std::string filename;

    // Приватный конструктор — только Singleton может создать объект
    Singleton(const std::string& fname) : filename(fname) { //объект создаваемый при инициализации функции
        // принимает имя файла для записи логов
        //std::ios::app — режим добавления в конец файла
        file.open(filename, std::ios::app);
        if (!file) {
            throw std::runtime_error("Cannot open log file: " + filename);
        }
    }

    // Деструктор: закрываем файл
    ~Singleton() {
        if (file.is_open()) {
            file.close();
        }
    }

    // Преобразование уровня в текст
    std::string levelToString(Level lvl) {
        switch (lvl) {
            case Level::ERROR:   return "ERROR";
            case Level::WARNING: return "WARNING";
            case Level::INFO:    return "INFO";
            case Level::DEBUG:   return "DEBUG";
        }
        return "UNKNOWN";
    }

    // Получение текущего времени
    std::string currentTime() {
        std::time_t t = std::time(nullptr);
        std::tm tm{};
#ifdef _WIN32
        localtime_s(&tm, &t);
#else
        localtime_r(&t, &tm);
#endif
        std::ostringstream oss;
        oss << std::put_time(&tm, "%H:%M:%S");
        return oss.str();
    }
};