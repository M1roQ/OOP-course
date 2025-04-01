#pragma once

#include <iostream>

class Time {
    int hours;
    int minutes;
    int seconds;

    static int objectCount;

    void Normalize();

public:
    Time();
    Time(int h, int m, int s);
    Time(const Time& t);

    int GetHours() const;
    int GetMinutes() const;
    int GetSeconds() const;

    void PrintTime() const;

    int ToSeconds() const;

    Time& operator=(const Time& other);
    Time& operator+=(int s);
    Time& operator-=(int s);

    friend Time operator+(const Time& t, int s);
    friend Time operator-(const Time& t, int s);

    friend bool operator==(const Time& t1, const Time& t2);

    friend std::ostream& operator<<(std::ostream& out, const Time& t);
    friend std::istream& operator>>(std::istream& in, Time& t);

    static int GetObjectCount();

    ~Time();
};