#include <iostream>

class Time {

    int hours;
    int minutes;
    int seconds;

    void Normalize() {
        // Normalize seconds, minutes and hours
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

public:
    Time() : hours(0), minutes(0), seconds(0) {}
    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
        Normalize();
    }
    Time(const Time& t) : Time(t.hours, t.minutes, t.seconds) {}

    int GetHours() const { return hours; }
    int GetMinutes() const { return minutes; }
    int GetSeconds() const { return seconds; }

    void PrintTime() const {
        std::cout << "H:" << GetHours() << " M:" << GetMinutes() << " S:" << GetSeconds() << std::endl;
    }

    // Method to get the total seconds since the start
    int ToSeconds() const {
        return hours * 3600 + minutes * 60 + seconds;
    }

    // Operator =
    Time& operator=(const Time& other) {
        hours = other.hours;
        minutes = other.minutes;
        seconds = other.seconds;
        return *this;
    }

    // Operator +=
    Time& operator+=(int s) {
        seconds += s;
        Normalize();
        return *this;
    }

    // Operator +
    friend Time operator+(const Time& t, int s) {
        Time result = t;
        result += s;
        return result;
    }

    // Operator -=
    Time& operator-=(int s) {
        seconds -= s;
        Normalize();
        return *this;
    }

    // Operator -
    friend Time operator-(const Time& t, int s) {
        Time result = t;
        result -= s;
        return result;
    }

    // Operator ==
    friend bool operator==(const Time& t1, const Time& t2) {
        return t1.hours == t2.hours && t1.minutes == t2.minutes && t1.seconds == t2.seconds;
    }

    // Output 
    friend std::ostream& operator<<(std::ostream& out, const Time& t) {
        out << t.GetHours() << ":" << t.GetMinutes() << ":" << t.GetSeconds();
        return out;
    }

    // Input
    friend std::istream& operator>>(std::istream& in, Time& t) {
        int h, m, s;
        char tmp;
        in >> h >> tmp >> m >> tmp >> s;
        t = Time(h, m, s);
        return in;
    }

    ~Time() {} // Destructor
};
