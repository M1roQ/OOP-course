#include "mytime7_2.h"

// Реализация класса Time
void Time::Normalize() {
    if (seconds >= 60) {
        minutes += seconds / 60;
        seconds %= 60;
    }
    if (minutes >= 60) {
        hours += minutes / 60;
        minutes %= 60;
    }
    if (seconds < 0) {
        minutes -= 1 + (-seconds) / 60;
        seconds = 60 - (-seconds) % 60;
    }
    if (minutes < 0) {
        hours -= 1 + (-minutes) / 60;
        minutes = 60 - (-minutes) % 60;
    }
    if (hours >= 24 || hours < 0) {
        hours = (hours + 24) % 24;
    }
}

Time::Time() : hours(0), minutes(0), seconds(0) {}

Time::Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
    Normalize();
}

Time::Time(const Time& t) : hours(t.hours), minutes(t.minutes), seconds(t.seconds) {}

int Time::GetHours() const noexcept { return hours; }
int Time::GetMinutes() const noexcept { return minutes; }
int Time::GetSeconds() const noexcept { return seconds; }

void Time::PrintTime() const noexcept {
    std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
}

Time::~Time() {}

// Реализация класса Clock
Clock::Clock(const std::string& clockName) : name(clockName) {
    std::cout << name << " constructor called" << std::endl;
}

void Clock::SetTime(const Time& t) {
    time = t;
}

Clock::~Clock() {
    std::cout << name << " destructor called" << std::endl;
}

// Реализация класса CuckooClock
CuckooClock::CuckooClock() : Clock("CuckooClock") {}

void CuckooClock::ShowTime() const {
    std::cout << "CuckooClock shows time: ";
    time.PrintTime();
    std::cout << "Cuckoo! Cuckoo!" << std::endl;
}

CuckooClock::~CuckooClock() = default;

// Реализация класса WallClock
WallClock::WallClock() : Clock("WallClock") {}

void WallClock::ShowTime() const {
    std::cout << "WallClock shows time: ";
    time.PrintTime();
}

WallClock::~WallClock() = default;

// Реализация класса Watch
Watch::Watch() : Clock("Watch"), is24HourFormat(true) {}

void Watch::Set24HourFormat(bool is24Hour) {
    is24HourFormat = is24Hour;
}

void Watch::ShowTime() const {
    int hours = time.GetHours();
    std::string period = "";

    if (!is24HourFormat) {
        period = (hours >= 12) ? " PM" : " AM";
        hours = (hours % 12 == 0) ? 12 : hours % 12;
    }

    std::cout << "Watch shows time: " 
              << hours << ":" 
              << time.GetMinutes() << ":" 
              << time.GetSeconds() 
              << period << std::endl;
}

Watch::~Watch() = default;

// Реализация класса SmartWatch
SmartWatch::SmartWatch() {
    name = "SmartWatch";
    std::cout << name << " constructor called" << std::endl;
}

void SmartWatch::ShowTime() const {
    std::cout << "SmartWatch shows time: ";
    time.PrintTime();
}

SmartWatch::~SmartWatch() {
    std::cout << name << " destructor called" << std::endl;
}
