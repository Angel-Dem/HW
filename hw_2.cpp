#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

class Logger {
public:
    enum class Level {
        ERROR,
        WARNING,
        INFO,
        DEBUG
    };

    // Получение единственного экземпляра Singleton
    static Logger& getInstance(const std::string& filename = "log.txt") {
        static Logger instance(filename);  // создаётся один раз
        return instance;
    }

    // Запрет копирования и присваивания
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Установка текущего уровня логирования
    void setLevel(Level lvl) {
        currentLevel = lvl;
    }

    // Основная функция логирования
    void log(const std::string& message, Level msgLevel) {
        if (msgLevel > currentLevel) {
            return; // сообщение слишком подробное — пропускаем
        }

        if (!file.is_open()) {
            throw std::runtime_error("Logger file is not open!");
        }

        file << "[" << currentTime() << "] "
             << "[" << levelToString(msgLevel) << "] "
             << message << std::endl;
    }

private:
    std::ofstream file;
    Level currentLevel = Level::INFO;
    std::string filename;

    // Приватный конструктор — только Singleton может создать объект
    Logger(const std::string& fname) : filename(fname) {
        file.open(filename, std::ios::app);
        if (!file) {
            throw std::runtime_error("Cannot open log file: " + filename);
        }
    }

    // Деструктор: закрываем файл
    ~Logger() {
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


int main() {
    auto& logger = Logger::getInstance("logfile.txt");

    logger.setLevel(Logger::Level::DEBUG);

    logger.log("Старт программы", Logger::Level::INFO);
    logger.log("Предупреждение: что-то странное", Logger::Level::WARNING);
    logger.log("Ошибка: что-то сломалось", Logger::Level::ERROR);
    logger.log("Отладочная информация", Logger::Level::DEBUG);

    return 0;
}

