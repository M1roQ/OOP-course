#include <iostream>
using namespace std;

// Base class: generic creature
class GenericCreature {
public:
    void exist() const {
        cout << "I am exist." << endl;
    }
};

// Derived class: ocean creature (can swim)
class OceanCreature : public GenericCreature {
public:
    void swim() const {
        cout << "I can swim." << endl;
    }
};

// Derived class: amphibious (can swim and walk)
class Amphibious : public OceanCreature {
public:
    void walk() const {
        cout << "I can walk." << endl;
    }
};

// Derived class: terrestrial creature (can walk)
class TerrestrialCreature : public Amphibious {
public:
    void swim() const = delete;
};

// Derived class: bird (can walk and fly)
class Bird : public TerrestrialCreature {
public:
    void fly() const {
        cout << "I can fly." << endl;
    }
};

// Derived class: waterfowl (can do everything: walk, fly, swim)
class Waterfowl : public Bird {
public:
    using OceanCreature::swim;
};

int main() {
    cout << "OceanCreature abilities:" << endl;
    OceanCreature fish;
    fish.exist();
    fish.swim();

    cout << "\nAmphibious abilities:" << endl;
    Amphibious frog;
    frog.exist();
    frog.swim();
    frog.walk();

    cout << "\nTerrestrialCreature abilities:" << endl;
    TerrestrialCreature lion;
    lion.exist();
    lion.walk();

    cout << "\nBird abilities:" << endl;
    Bird sparrow;
    sparrow.exist();
    sparrow.walk();
    sparrow.fly();

    cout << "\nWaterfowl abilities:" << endl;
    Waterfowl duck;
    duck.exist();
    duck.walk();
    duck.fly();
    duck.swim();


    return 0;
}
