#include "mytime7_1.h"


int Watch::GetHours(const Time& t) const noexcept { return t.hours; }
int Watch::GetMinutes(const Time& t) const noexcept { return t.minutes; }
int Watch::GetSeconds(const Time& t) const noexcept { return t.seconds; }

Watch::Watch() : is24HourFormat(true) {}

void Watch::Set24HourFormat(bool is24Hour) {
    is24HourFormat = is24Hour;
}

void Watch::ShowTime(const Time& t) const {
    int hours = t.GetHours();
    std::string period = "";

    if (!is24HourFormat) {
        period = (hours >= 12) ? " PM" : " AM";
        hours = (hours % 12 == 0) ? 12 : hours % 12;
    }

    std::cout << "Watch shows time: " 
              << hours << ":" 
              << t.GetMinutes() << ":" 
              << t.GetSeconds() 
              << period << std::endl;
}

void Watch::SetTime(Time& t, int h, int m, int s) {
    t.hours = h;
    t.minutes = m;
    t.seconds = s;
    t.Normalize();
}


int Time::objectCount = 0;

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

Time::Time() : hours(0), minutes(0), seconds(0) {
    objectCount++;
    std::cout << "Time default constructor called" << std::endl;
}

Time::Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
    Normalize();
    objectCount++;
    std::cout << "Time parameterized constructor called" << std::endl;
}

Time::Time(const Time& t) : hours(t.hours), minutes(t.minutes), seconds(t.seconds) {
    objectCount++;
    std::cout << "Time copy constructor called" << std::endl;
}

int Time::GetHours() const noexcept { return hours; }
int Time::GetMinutes() const noexcept { return minutes; }
int Time::GetSeconds() const noexcept { return seconds; }

void Time::PrintTime() const noexcept {
    std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
}

int Time::ToSeconds() const noexcept {
    return hours * 3600 + minutes * 60 + seconds;
}

Time& Time::operator=(const Time& other) noexcept {
    if (this != &other) {
        hours = other.hours;
        minutes = other.minutes;
        seconds = other.seconds;
    }
    std::cout << "Time assignment operator called" << std::endl;
    return *this;
}

Time& Time::operator+=(int s) noexcept {
    seconds += s;
    Normalize();
    return *this;
}

Time& Time::operator-=(int s) noexcept {
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
    out << t.hours << ":" << t.minutes << ":" << t.seconds;
    return out;
}

std::istream& operator>>(std::istream& in, Time& t) {
    in >> t.hours >> t.minutes >> t.seconds;
    t.Normalize();
    return in;
}

int Time::GetObjectCount() {
    return objectCount;
}

Time::~Time() {
    objectCount--;
    std::cout << "Time destructor called" << std::endl;
}

void SimpleWatch::ShowTime(const Time& t) const {
    std::cout << "SimpleWatch shows time: " 
              << t.hours << ":" 
              << t.minutes << ":" 
              << t.seconds << std::endl;
}

void SimpleWatch::SetTime(Time& t, int h, int m, int s) {
    t.hours = h;
    t.minutes = m;
    t.seconds = s;
    t.Normalize();
}

