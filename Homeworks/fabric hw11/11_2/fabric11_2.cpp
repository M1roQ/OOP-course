#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Abstract class
class GenericCreature {
public:
    virtual ~GenericCreature() {}

    // Virtual function
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

class Shark : public OceanCreature {
public:
    void eat() override {
        cout << "Shark eats fish." << endl;
    }
};

class Whale : public OceanCreature {
public:
    void eat() override {
        cout << "Whale eats krill." << endl;
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

class Crocodile : public Amphibious {
public:
    void eat() override {
        cout << "Crocodile eats large prey." << endl;
    }
};

class Frog : public Amphibious {
public:
    void eat() override {
        cout << "Frog eats insects." << endl;
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

class Lion : public TerrestrialCreature {
public:
    void eat() override {
        cout << "Lion eats meat." << endl;
    }
};

class Elephant : public TerrestrialCreature {
public:
    void eat() override {
        cout << "Elephant eats plants." << endl;
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

class Pigeon : public Bird {
public:
    void eat() override {
        cout << "Pigeon eats grains." << endl;
    }
};

class Parrot : public Bird {
public:
    void eat() override {
        cout << "Parrot eats fruits." << endl;
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

class Duck : public Waterfowl {
public:
    void eat() override {
        cout << "Duck eats aquatic plants." << endl;
    }
};

class Swan : public Waterfowl {
public:
    void eat() override {
        cout << "Swan eats underwater vegetation." << endl;
    }
};

// Creator class
class Creator {
public:
    virtual ~Creator() {}
    virtual unique_ptr<GenericCreature> createCreature() = 0;
};

class SharkCreator : public Creator {
public:
    unique_ptr<GenericCreature> createCreature() override {
        return make_unique<Shark>();
    }
};

class WhaleCreator : public Creator {
public:
    unique_ptr<GenericCreature> createCreature() override {
        return make_unique<Whale>();
    }
};

class CrocodileCreator : public Creator {
public:
    unique_ptr<GenericCreature> createCreature() override {
        return make_unique<Crocodile>();
    }
};

class FrogCreator : public Creator {
public:
    unique_ptr<GenericCreature> createCreature() override {
        return make_unique<Frog>();
    }
};

class LionCreator : public Creator {
public:
    unique_ptr<GenericCreature> createCreature() override {
        return make_unique<Lion>();
    }
};

class ElephantCreator : public Creator {
public:
    unique_ptr<GenericCreature> createCreature() override {
        return make_unique<Elephant>();
    }
};

class PigeonCreator : public Creator {
public:
    unique_ptr<GenericCreature> createCreature() override {
        return make_unique<Pigeon>();
    }
};

class ParrotCreator : public Creator {
public:
    unique_ptr<GenericCreature> createCreature() override {
        return make_unique<Parrot>();
    }
};

class DuckCreator : public Creator {
public:
    unique_ptr<GenericCreature> createCreature() override {
        return make_unique<Duck>();
    }
};

class SwanCreator : public Creator {
public:
    unique_ptr<GenericCreature> createCreature() override {
        return make_unique<Swan>();
    }
};

int main() {
    vector<unique_ptr<Creator>> creators;
    creators.push_back(make_unique<SharkCreator>());
    creators.push_back(make_unique<WhaleCreator>());
    creators.push_back(make_unique<CrocodileCreator>());
    creators.push_back(make_unique<FrogCreator>());
    creators.push_back(make_unique<LionCreator>());
    creators.push_back(make_unique<ElephantCreator>());
    creators.push_back(make_unique<PigeonCreator>());
    creators.push_back(make_unique<ParrotCreator>());
    creators.push_back(make_unique<DuckCreator>());
    creators.push_back(make_unique<SwanCreator>());


    for (auto& creator : creators) {
        vector<unique_ptr<GenericCreature>> creatures;
        for (int i = 0; i < 3; ++i) {
            creatures.push_back(creator->createCreature());
        }
        for (auto& creature : creatures) {
            creature->eat();
        }
        cout << endl;
    }

    return 0;
}
