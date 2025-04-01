#include <iostream>
#include <vector>
using namespace std;

// Абстрактный класс посетителя
class Visitor {
public:
    virtual void visitOceanCreature(class OceanCreature* creature) = 0;
    virtual void visitAmphibious(class Amphibious* creature) = 0;
    virtual void visitTerrestrialCreature(class TerrestrialCreature* creature) = 0;
    virtual void visitBird(class Bird* creature) = 0;
    virtual void visitWaterfowl(class Waterfowl* creature) = 0;
};

// Абстрактный класс для всех существ
class GenericCreature {
public:
    virtual ~GenericCreature() {}

    virtual void accept(Visitor* visitor) = 0;
    virtual void eat() = 0;
};

// Класс для морского существа
class OceanCreature : virtual public GenericCreature {
public:
    void eat() override {
        cout << "OceanCreature eats plankton." << endl;
    }

    void swim() {
        cout << "OceanCreature swims in the water." << endl;
    }

    void exploreCoralReef() {
        cout << "OceanCreature explores the coral reef." << endl;
    }

    void giveShelterAdvice() {
        cout << "Visitor gives advice to the OceanCreature on finding shelters underwater." << endl;
    }

    void observe() {
        cout << "Visitor observes the OceanCreature." << endl;
    }

    void accept(Visitor* visitor) override {
        visitor->visitOceanCreature(this);
    }
};

// Класс для амфибий
class Amphibious : public OceanCreature {
public:
    void eat() override {
        cout << "Amphibious eats both plants and small animals." << endl;
    }

    void walk() {
        cout << "Amphibious walks on land." << endl;
    }

    void swim() {
        cout << "Amphibious swims in water." << endl;
    }

    void climbToLand() {
        cout << "Amphibious climbs to land." << endl;
    }

    void observe() {
        cout << "Visitor observes the Amphibious creature." << endl;
    }

    void accept(Visitor* visitor) override {
        visitor->visitAmphibious(this);
    }
};

// Класс для наземных существ
class TerrestrialCreature : virtual public GenericCreature {
public:
    void eat() override {
        cout << "TerrestrialCreature eats plants or small animals." << endl;
    }

    void walk() {
        cout << "TerrestrialCreature walks on land." << endl;
    }

    void giveShelterAdvice() {
        cout << "Visitor gives advice to the TerrestrialCreature on finding shelters on land." << endl;
    }

    void observe() {
        cout << "Visitor observes the TerrestrialCreature." << endl;
    }

    void accept(Visitor* visitor) override {
        visitor->visitTerrestrialCreature(this);
    }
};

// Класс для птиц
class Bird : virtual public TerrestrialCreature {
public:
    void eat() override {
        cout << "Bird eats seeds and insects." << endl;
    }

    void fly() {
        cout << "Bird flies in the sky." << endl;
    }

    void clean() {
        cout << "Bird cleans its feathers." << endl;
    }

    void walk() {
        cout << "Bird walks on land." << endl;
    }

    void trainFlight() {
        cout << "Bird is trained for flying." << endl;
    }

    void instructFeatherCleaning() {
        cout << "Visitor gives instructions to the Bird for cleaning its feathers." << endl;
    }

    void observe() {
        cout << "Visitor observes the Bird." << endl;
    }

    void accept(Visitor* visitor) override {
        visitor->visitBird(this);
    }
};

// Класс для водоплавающих птиц
class Waterfowl : public Bird, public OceanCreature {
public:
    void eat() override {
        cout << "Waterfowl eats fish and plants from water." << endl;
    }

    void swim() {
        cout << "Waterfowl swims gracefully in the water." << endl;
    }

    void observe() {
        cout << "Visitor observes the Waterfowl." << endl;
    }

    void accept(Visitor* visitor) override {
        visitor->visitWaterfowl(this);
    }
};

// Конкретный посетитель, который выполняет манипуляции
class CreatureActionVisitor : public Visitor {
public:
    void visitOceanCreature(OceanCreature* creature) override {
        cout << "OceanCreature's actions:\n";
        creature->eat();
        creature->swim();
        creature->exploreCoralReef();
        creature->giveShelterAdvice();
        creature->observe();
        cout << "\n";
    }

    void visitAmphibious(Amphibious* creature) override {
        cout << "Amphibious's actions:\n";
        creature->eat();
        creature->walk();
        creature->swim();
        creature->climbToLand();
        creature->observe();
        cout << "\n";
    }

    void visitTerrestrialCreature(TerrestrialCreature* creature) override {
        cout << "TerrestrialCreature's actions:\n";
        creature->eat();
        creature->walk();
        creature->giveShelterAdvice();
        creature->observe();
        cout << "\n";
    }

    void visitBird(Bird* creature) override {
        cout << "Bird's actions:\n";
        creature->clean();
        creature->trainFlight();
        creature->instructFeatherCleaning();
        creature->walk();
        creature->observe();
        cout << "\n";
    }

    void visitWaterfowl(Waterfowl* creature) override {
        cout << "Waterfowl's actions:\n";
        creature->eat();
        creature->swim();
        creature->observe();
        cout << "\n";
    }
};

// Клиентский код
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

    // Создаем посетителя
    CreatureActionVisitor visitor;

    // Выполняем манипуляции с каждым существом
    for (GenericCreature* creature : creatures) {
        creature->accept(&visitor);
    }

    return 0;
}
