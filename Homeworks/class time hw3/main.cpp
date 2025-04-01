#include<iostream>
#include"mytime.cpp"

int main() {
    Time t(23, -10, 5); 
    std::cout << "t: " << std::endl;
    t.PrintTime(); 

    t += 3600;
    std::cout << "t + 1h: " << std::endl;
    t.PrintTime();

    t -= 3661;
    std::cout << "t - 1h 1s: " << std::endl;
    t.PrintTime();

    std::cout << "Seconds since start of day: " << t.ToSeconds() << std::endl;

    Time t2(23, 49, 5);
    std::cout << "t2: " << std::endl;
    t2.PrintTime();

    t2 = t;
    std::cout << "t2 = t: " << std::endl;
    t2.PrintTime();

    Time t3;
    t3 = t2 - 10800;
    std::cout << "t3 = t2 - 3h: " << std::endl;
    t3.PrintTime();

    std::cout << "t = t2? " << (t == t2 ? "Yes" : "No") << std::endl;
    std::cout << "t2 = t3? " << (t2 == t3 ? "Yes" : "No") << std::endl;
}
