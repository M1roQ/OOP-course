#include <iostream>
#include <vector>

class Time {
    int hours;
    int minutes;
    int seconds;

    static int objectCount;

    void Normalize();

public:
    Time();  // Конструктор по умолчанию
    Time(int h, int m, int s);  // Параметрический конструктор
    Time(const Time& t);  // Конструктор копирования

    // Конструктор перемещения
    Time(Time&& t) noexcept;

    // Оператор присваивания
    Time& operator=(const Time& other);
    
    // Оператор присваивания с перемещением
    Time& operator=(Time&& other) noexcept;

    Time& operator+=(int s);  // Оператор +=
    Time& operator-=(int s);  // Оператор -=

    friend Time operator+(const Time& t, int s);  // Оператор +
    friend Time operator-(const Time& t, int s);  // Оператор -

    friend bool operator==(const Time& t1, const Time& t2);  // Оператор ==

    friend std::ostream& operator<<(std::ostream& out, const Time& t);  // Оператор вывода
    friend std::istream& operator>>(std::istream& in, Time& t);  // Оператор ввода

    static int GetObjectCount();  // Статический метод для получения количества объектов

    void PrintTime() const;  // Метод для печати времени

    ~Time();  // Деструктор
};

int Time::objectCount = 0;

void Time::Normalize() {
    if (seconds >= 60) {
        minutes += seconds / 60;
        seconds %= 60;
    }
    else if (seconds < 0) {
        minutes += (seconds / 60) - 1;
        seconds = 60 + (seconds % 60);
    }

    if (minutes >= 60) {
        hours += minutes / 60;
        minutes %= 60;
    }
    else if (minutes < 0) {
        hours += (minutes / 60) - 1;
        minutes = 60 + (minutes % 60);
    }

    if (hours >= 24) {
        hours %= 24;
    }
    else if (hours < 0) {
        hours = 24 + (hours % 24);
    }
}

Time::Time() : hours(0), minutes(0), seconds(0) {
    objectCount++;
    std::cout << "Default constructor called. Current object count: " << objectCount << std::endl;
}

Time::Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
    Normalize();
    objectCount++;
    std::cout << "Parameterized constructor called. Current object count: " << objectCount << std::endl;
}

Time::Time(const Time& t) : Time(t.hours, t.minutes, t.seconds) {
    std::cout << "Copy constructor called. Current object count: " << objectCount << std::endl;
}

// Конструктор перемещения
Time::Time(Time&& t) noexcept : hours(t.hours), minutes(t.minutes), seconds(t.seconds) {
    t.hours = 0;
    t.minutes = 0;
    t.seconds = 0;
    objectCount++;
    std::cout << "Move constructor called. Current object count: " << objectCount << std::endl;
}

Time& Time::operator=(const Time& other) {
    hours = other.hours;
    minutes = other.minutes;
    seconds = other.seconds;
    return *this;
}

// Оператор присваивания с перемещением
Time& Time::operator=(Time&& other) noexcept {
    if (this != &other) {
        hours = other.hours;
        minutes = other.minutes;
        seconds = other.seconds;

        other.hours = 0;
        other.minutes = 0;
        other.seconds = 0;
    }
    return *this;
}

Time& Time::operator+=(int s) {
    seconds += s;
    Normalize();
    return *this;
}

Time& Time::operator-=(int s) {
    seconds -= s;
    Normalize();
    return *this;
}

Time operator+(const Time& t, int s) {
    Time result = t;
    result += s;
    return result;
}

Time operator-(const Time& t, int s) {
    Time result = t;
    result -= s;
    return result;
}

bool operator==(const Time& t1, const Time& t2) {
    return t1.hours == t2.hours && t1.minutes == t2.minutes && t1.seconds == t2.seconds;
}

std::ostream& operator<<(std::ostream& out, const Time& t) {
    out << (t.hours < 10 ? "0" : "") << t.hours << ":"
        << (t.minutes < 10 ? "0" : "") << t.minutes << ":"
        << (t.seconds < 10 ? "0" : "") << t.seconds;
    return out;
}


std::istream& operator>>(std::istream& in, Time& t) {
    int h, m, s;
    char tmp;
    in >> h >> tmp >> m >> tmp >> s;
    t = Time(h, m, s);
    return in;
}

int Time::GetObjectCount() {
    return objectCount;
}

Time::~Time() {
    objectCount--;
    std::cout << "Destructor called. Current object count: " << objectCount << std::endl;
}

void Time::PrintTime() const {
    // Форматируем вывод времени в виде hh:mm:ss
    std::cout << (hours < 10 ? "0" : "") << hours << ":"
              << (minutes < 10 ? "0" : "") << minutes << ":"
              << (seconds < 10 ? "0" : "") << seconds << std::endl;
}

int main() {
    // Пример использования конструктора перемещения и оператора присваивания с перемещением
    Time t1(23, -10, 5);
    std::cout << "t1: ";
    t1.PrintTime();

    Time t2 = std::move(t1);  // Конструктор перемещения
    std::cout << "t2 after move from t1: ";
    t2.PrintTime();

    t1 = Time(10, 20, 30);  // Оператор присваивания с перемещением
    std::cout << "t1 after move assignment: ";
    t1.PrintTime();

    std::vector<Time> timeVec;
    timeVec.push_back(std::move(t2));  // Добавление rvalue в vector
    timeVec.push_back(Time(12, 34, 56));  // Добавление rvalue в vector

    std::cout << "Vector size after adding elements: " << timeVec.size() << std::endl;

    // Дополнительные операции с объектами
    Time t3(12, 0, 0);
    t3 = t2;  // Присваивание lvalue
    std::cout << "t3 = t2: ";
    t3.PrintTime();

    std::cout << "Final object count: " << Time::GetObjectCount() << std::endl;

    return 0;
}
