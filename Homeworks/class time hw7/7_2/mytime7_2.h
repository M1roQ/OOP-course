#pragma once

#include <iostream>
#include <string>

class Time {
    int hours;
    int minutes;
    int seconds;

    void Normalize();

public:
    Time();
    Time(int h, int m, int s);
    Time(const Time& t);

    int GetHours() const noexcept;
    int GetMinutes() const noexcept;
    int GetSeconds() const noexcept;

    void PrintTime() const noexcept;
    ~Time();
};

class Clock {
protected:
    Time time;
    std::string name;

public:
    Clock(const std::string& clockName = "Clock");
    virtual void ShowTime() const = 0;
    void SetTime(const Time& t);
    virtual ~Clock();
};

class CuckooClock : public Clock {
public:
    CuckooClock();
    void ShowTime() const override;
    ~CuckooClock() override;
};

class WallClock : public Clock {
public:
    WallClock();
    void ShowTime() const override;
    ~WallClock() override;
};

class Watch : public Clock {
    bool is24HourFormat;

public:
    Watch();
    void Set24HourFormat(bool is24Hour);
    void ShowTime() const override;
    ~Watch() override;
};

class SmartWatch : public Watch {
public:
    SmartWatch();
    void ShowTime() const override;
    ~SmartWatch() override;
};
