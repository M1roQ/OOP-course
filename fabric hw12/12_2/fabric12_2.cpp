#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Abstract class
class GenericCreature {
public:
    virtual ~GenericCreature() {}

    // Virtual function for eating
    virtual void eat() = 0;
};

// Base classes for different creature categories
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

// Specific creatures
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

class Duck : public Bird, public OceanCreature {
public:
    void eat() override {
        cout << "Duck eats aquatic plants." << endl;
    }

    void swim() {
        cout << "Duck swims in water." << endl;
    }
};

class Swan : public Bird, public OceanCreature {
public:
    void eat() override {
        cout << "Swan eats underwater vegetation." << endl;
    }

    void swim() {
        cout << "Swan swims gracefully." << endl;
    }
};

// Abstract Factory for creature creation
class CreatureFactory {
public:
    virtual ~CreatureFactory() {}
    virtual unique_ptr<GenericCreature> createShark() = 0;
    virtual unique_ptr<GenericCreature> createWhale() = 0;
    virtual unique_ptr<GenericCreature> createCrocodile() = 0;
    virtual unique_ptr<GenericCreature> createFrog() = 0;
    virtual unique_ptr<GenericCreature> createLion() = 0;
    virtual unique_ptr<GenericCreature> createElephant() = 0;
    virtual unique_ptr<GenericCreature> createPigeon() = 0;
    virtual unique_ptr<GenericCreature> createParrot() = 0;
    virtual unique_ptr<GenericCreature> createDuck() = 0;
    virtual unique_ptr<GenericCreature> createSwan() = 0;
};

// Specific factories for each creature category
class OceanFactory : public CreatureFactory {
public:
    unique_ptr<GenericCreature> createShark() override {
        return make_unique<Shark>();
    }
    unique_ptr<GenericCreature> createWhale() override {
        return make_unique<Whale>();
    }
    unique_ptr<GenericCreature> createCrocodile() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createFrog() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createLion() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createElephant() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createPigeon() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createParrot() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createDuck() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createSwan() override {
        return nullptr;
    }
};

class AmphibiousFactory : public CreatureFactory {
public:
    unique_ptr<GenericCreature> createShark() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createWhale() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createCrocodile() override {
        return make_unique<Crocodile>();
    }
    unique_ptr<GenericCreature> createFrog() override {
        return make_unique<Frog>();
    }
    unique_ptr<GenericCreature> createLion() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createElephant() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createPigeon() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createParrot() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createDuck() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createSwan() override {
        return nullptr;
    }
};

class TerrestrialFactory : public CreatureFactory {
public:
    unique_ptr<GenericCreature> createShark() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createWhale() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createCrocodile() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createFrog() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createLion() override {
        return make_unique<Lion>();
    }
    unique_ptr<GenericCreature> createElephant() override {
        return make_unique<Elephant>();
    }
    unique_ptr<GenericCreature> createPigeon() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createParrot() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createDuck() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createSwan() override {
        return nullptr;
    }
};

class BirdFactory : public CreatureFactory {
public:
    unique_ptr<GenericCreature> createShark() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createWhale() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createCrocodile() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createFrog() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createLion() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createElephant() override {
        return nullptr;
    }
    unique_ptr<GenericCreature> createPigeon() override {
        return make_unique<Pigeon>();
    }
    unique_ptr<GenericCreature> createParrot() override {
        return make_unique<Parrot>();
    }
    unique_ptr<GenericCreature> createDuck() override {
        return make_unique<Duck>();
    }
    unique_ptr<GenericCreature> createSwan() override {
        return make_unique<Swan>();
    }
};

// Client code
int main() {
    vector<unique_ptr<CreatureFactory>> factories;
    factories.push_back(make_unique<OceanFactory>());
    factories.push_back(make_unique<AmphibiousFactory>());
    factories.push_back(make_unique<TerrestrialFactory>());
    factories.push_back(make_unique<BirdFactory>());

    // Создаем и выводим по 3 существа каждого типа
    for (auto& factory : factories) {
        for (int i = 0; i < 3; ++i) {
            // Создание и вывод Shark
            auto shark = factory->createShark();
            if (shark) {
                shark->eat();
            }

            // Создание и вывод Whale
            auto whale = factory->createWhale();
            if (whale) {
                whale->eat();
            }

            // Создание и вывод Crocodile
            auto crocodile = factory->createCrocodile();
            if (crocodile) {
                crocodile->eat();
            }

            // Создание и вывод Frog
            auto frog = factory->createFrog();
            if (frog) {
                frog->eat();
            }

            // Создание и вывод Lion
            auto lion = factory->createLion();
            if (lion) {
                lion->eat();
            }

            // Создание и вывод Elephant
            auto elephant = factory->createElephant();
            if (elephant) {
                elephant->eat();
            }

            // Создание и вывод Pigeon
            auto pigeon = factory->createPigeon();
            if (pigeon) {
                pigeon->eat();
            }

            // Создание и вывод Parrot
            auto parrot = factory->createParrot();
            if (parrot) {
                parrot->eat();
            }

            // Создание и вывод Duck
            auto duck = factory->createDuck();
            if (duck) {
                duck->eat();
            }

            // Создание и вывод Swan
            auto swan = factory->createSwan();
            if (swan) {
                swan->eat();
            }
        }
        cout << endl;
    }

    return 0;
}

