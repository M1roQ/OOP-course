#include "mytime7_2.h"

int main() {
    Time t(23, 59, 59);

    WallClock wallClock;
    wallClock.SetTime(t);
    wallClock.ShowTime();

    Watch watch;
    watch.SetTime(t);
    watch.Set24HourFormat(false);
    watch.ShowTime();

    SmartWatch smartWatch;
    smartWatch.SetTime(t);
    smartWatch.ShowTime();

    CuckooClock cuckooClock;
    cuckooClock.SetTime(t);
    cuckooClock.ShowTime();

    return 0;
}
