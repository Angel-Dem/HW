#include <iostream>
#include <vector>

class Counter {
    int value;
public:
    struct LogEntry {
        std::string action;
        int oldValue;
        int newValue;
    };
    std::vector<LogEntry> log;
    Counter(int initial = 0) {
        this->value = initial;
    }
    Counter& inc(int delta = 1) {
        auto old = this->value;
        this->value += delta;
        log.push_back(LogEntry{"inc", old, this->value});
        return *this;
    }
    Counter& dec(int delta = 1) {
        auto old = this->value;
        this->value -= delta;
        log.push_back(LogEntry{"dec", old, this->value});
        return *this;
    }
    Counter& set(int newValue) {
        auto old = this->value;
        this->value = newValue;
        log.push_back(LogEntry{"dec", old, this->value});
        return *this;
    }
    void printLog() const {
        for (auto l : log) {
            std::cout << "Action "<<l.action<<'\n';
            std::cout << "Old value "<<l.oldValue<<'\n';
            std::cout << "New value "<<l.newValue<<'\n';
        }
    }
};

int main() {
    Counter counter;
    counter.inc(5).dec(2).set(10).inc();
    counter.printLog();
}