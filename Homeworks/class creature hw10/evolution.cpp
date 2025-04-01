#include <iostream>
#include <vector>
using namespace std;

// abstruct class
class GenericCreature {
public:
    virtual ~GenericCreature() {}  

    // virtual function
    virtual void eat() = 0;
};

class OceanCreature : virtual public GenericCreature {  
public:
    void eat() override {
        cout << "OceanCreature eats plankton." << endl;
    }

    void swim() {
        cout << "OceanCreature swims in the water." << endl;
    }
};

class Amphibious : public OceanCreature {
public:
    void eat() override {
        cout << "Amphibious eats both plants and small animals." << endl;
    }

    void walk() {
        cout << "Amphibious walks on land." << endl;
    }
};

class TerrestrialCreature : virtual public GenericCreature {  
public:
    void eat() override {
        cout << "TerrestrialCreature eats plants or small animals." << endl;
    }

    void walk() {
        cout << "TerrestrialCreature walks on land." << endl;
    }
};

class Bird : virtual public TerrestrialCreature { 
public:
    void eat() override {
        cout << "Bird eats seeds and insects." << endl;
    }

    void fly() {
        cout << "Bird flies in the sky." << endl;
    }
};

class Waterfowl : public Bird, public OceanCreature {
public:
    void eat() override {
        cout << "Waterfowl eats fish and plants from water." << endl;
    }

    void swim() {
        cout << "Waterfowl swims gracefully in the water." << endl;
    }
};

int main() {
    vector<GenericCreature*> creatures;

    OceanCreature ocean;
    Amphibious amphibious;
    TerrestrialCreature terrestrial;
    Bird bird;
    Waterfowl waterfowl;

    creatures.push_back(&ocean);
    creatures.push_back(&amphibious);
    creatures.push_back(&terrestrial);
    creatures.push_back(&bird);
    creatures.push_back(&waterfowl);

    for (GenericCreature* creature : creatures) {
        creature->eat();  
    }

    cout << "\nDemonstrating non-polymorphic behavior:\n";
    ocean.swim();
    amphibious.walk();
    terrestrial.walk();
    bird.fly();
    waterfowl.swim();

    return 0;
}
