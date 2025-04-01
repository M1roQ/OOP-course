#include "mytime.h"

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

int Time::GetHours() const { return hours; }
int Time::GetMinutes() const { return minutes; }
int Time::GetSeconds() const { return seconds; }

void Time::PrintTime() const {
    std::cout << "H:" << GetHours() << " M:" << GetMinutes() << " S:" << GetSeconds() << std::endl;
}

int Time::ToSeconds() const {
    return ((hours * 3600) + (minutes * 60) + seconds);
}

Time& Time::operator=(const Time& other) {
    if (this != &other) {
        hours = other.hours;
        minutes = other.minutes;
        seconds = other.seconds;
    }
    return *this;
}

Time& Time::operator+=(int s) {
    seconds += s;  
    int totalSeconds = ToSeconds();
    hours = (totalSeconds / 3600) % 24; 
    minutes = (totalSeconds % 3600) / 60; 
    seconds = totalSeconds % 60; 
    Normalize();
    return *this;
}

Time& Time::operator-=(int s) {
    int totalSeconds = ToSeconds();
    totalSeconds -= s;
    hours = totalSeconds / 3600;
    minutes = (totalSeconds % 3600) / 60;
    seconds = totalSeconds % 60;
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
    out << t.GetHours() << ":" << t.GetMinutes() << ":" << t.GetSeconds();
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
