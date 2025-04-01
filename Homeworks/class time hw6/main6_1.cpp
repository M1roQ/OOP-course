#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include "mytime.h"

int main() {
    std::cout << "\nDynamic memory: One object\n";
    Time* dynamicTime = new Time(10, 15, 30);
    dynamicTime->PrintTime();
    delete dynamicTime;

    std::cout << "\nDynamic memory: Array of objects\n";
    Time* dynamicTimeArr = new Time[3]{
        Time(1, 10, 10),
        Time(2, 20, 20),
        Time(3, 30, 30)
    };
    for (int i = 0; i < 3; ++i) {
        dynamicTimeArr[i].PrintTime();
    }
    delete[] dynamicTimeArr;


    std::cout << "\nStandard container: Vector\n";
    std::vector<Time> timeVector;
    timeVector.emplace_back(5, 50, 50);
    timeVector.emplace_back(6, 40, 40);
    for (const auto& time : timeVector) {
        time.PrintTime();
    }

    std::cout << "\nStandard container: List\n";
    std::list<Time> timeList;
    timeList.emplace_back(7, 30, 30);
    timeList.emplace_back(8, 20, 20);
    for (const auto& time : timeList) {
        time.PrintTime();
    }


    std::cout << "\n-- Smart pointer: Unique pointer --\n";
    std::unique_ptr<Time> uniqueTime = std::make_unique<Time>(9, 10, 10);
    uniqueTime->PrintTime();

    std::cout << "\n-- Smart pointer: Shared pointer --\n";
    std::shared_ptr<Time> sharedTime1 = std::make_shared<Time>(11, 11, 11);
    {
        std::shared_ptr<Time> sharedTime2 = sharedTime1;
        sharedTime2->PrintTime();
    }
    sharedTime1->PrintTime();


    return 0;
}
