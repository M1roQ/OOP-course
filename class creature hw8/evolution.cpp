#include <iostream>

using namespace std;

class GenericCreature {
public:
    GenericCreature() {}
    virtual ~GenericCreature() {}

    void exist() { cout << "I am a generic creature.\n"; }
};

// Класс для существ, умеющих плавать
class OceanCreature : public GenericCreature {
public:
    void swim() { cout << "I can swim.\n"; }
};

// Класс для существ, умеющих плавать и ходить
class Amphibious : public OceanCreature {
public:
    void walk() { cout << "I can walk.\n"; }
    using OceanCreature::swim;
};

// Класс для существ, которые не умеют плавать, но могут ходить
class TerrestrialCreature : protected Amphibious {
public:
    using Amphibious::walk;
};

// Класс для существ, которые могут ходить и летать
class Bird : public TerrestrialCreature {
public:
    void fly() { cout << "I can fly.\n"; }
};

// Класс для водоплавающих птиц, которые могут плавать, ходить и летать
class Waterfowl : public Bird{
public:
    using OceanCreature::swim;
};


int main() {
    cout << "OceanCreature abilities:" << endl;
    OceanCreature fish;
    fish.swim();

    cout << "\nAmphibious abilities:" << endl;
    Amphibious frog;
    frog.swim();
    frog.walk();

    cout << "\nTerrestrialCreature abilities:" << endl;
    TerrestrialCreature lion;
    lion.walk();

    cout << "\nBird abilities:" << endl;
    Bird sparrow;
    sparrow.walk();
    sparrow.fly();

    cout << "\nWaterfowl abilities:" << endl;
    Waterfowl duck;
    duck.walk();
    duck.fly();
    duck.swim();

    return 0;
}
