#include "mytime7_1.h"

int main() {
    Time t(23, 59, 59);
    SimpleWatch sw;
    Watch w;

    sw.ShowTime(t);

    w.Set24HourFormat(false);
    w.ShowTime(t);

    w.SetTime(t, 10, 30, 45);
    w.Set24HourFormat(true);
    w.ShowTime(t);

    return 0;
}
