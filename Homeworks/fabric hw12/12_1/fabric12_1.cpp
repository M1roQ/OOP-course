#include <iostream>
#include <vector>

// Абстрактные классы продуктов (House, Fence, Barn)
class House {
protected:
    static unsigned id_counter;
public:
    virtual ~House() {}
    virtual void construct() const = 0; // Метод теперь const
};

unsigned House::id_counter = 1;

class Fence {
protected:
    static unsigned id_counter;
public:
    virtual ~Fence() {}
    virtual void construct() const = 0; // Метод теперь const
};

unsigned Fence::id_counter = 1;

class Barn {
protected:
    static unsigned id_counter;
public:
    virtual ~Barn() {}
    virtual void construct() const = 0; // Метод теперь const
};

unsigned Barn::id_counter = 1;

// Конкретные классы продуктов - дома
class WoodenHouse : public House {
public:
    void construct() const override { // Метод теперь const
        std::cout << "Constructing wooden house with ID [" << id_counter++ << "]...\n";
    }
};

class BrickHouse : public House {
public:
    void construct() const override { // Метод теперь const
        std::cout << "Constructing brick house with ID [" << id_counter++ << "]...\n";
    }
};

class ConcreteHouse : public House {
public:
    void construct() const override { // Метод теперь const
        std::cout << "Constructing concrete house with ID [" << id_counter++ << "]...\n";
    }
};

// Конкретные классы продуктов - заборы
class WoodenFence : public Fence {
public:
    void construct() const override { // Метод теперь const
        std::cout << "Constructing wooden fence with ID [" << id_counter++ << "]...\n";
    }
};

class BrickFence : public Fence {
public:
    void construct() const override { // Метод теперь const
        std::cout << "Constructing brick fence with ID [" << id_counter++ << "]...\n";
    }
};

class ConcreteFence : public Fence {
public:
    void construct() const override { // Метод теперь const
        std::cout << "Constructing concrete fence with ID [" << id_counter++ << "]...\n";
    }
};

// Конкретные классы продуктов - сараи
class WoodenBarn : public Barn {
public:
    void construct() const override { // Метод теперь const
        std::cout << "Constructing wooden barn with ID [" << id_counter++ << "]...\n";
    }
};

class BrickBarn : public Barn {
public:
    void construct() const override { // Метод теперь const
        std::cout << "Constructing brick barn with ID [" << id_counter++ << "]...\n";
    }
};

class ConcreteBarn : public Barn {
public:
    void construct() const override { // Метод теперь const
        std::cout << "Constructing concrete barn with ID [" << id_counter++ << "]...\n";
    }
};

// Абстрактная фабрика - застройщик
class Developer {
public:
    virtual ~Developer() {}
    virtual House* buildHouse() = 0;
    virtual Fence* buildFence() = 0;
    virtual Barn* buildBarn() = 0;
};

// Конкретные создатели (деревянный, кирпичный, бетонный застройщики)
class WoodenDeveloper : public Developer {
public:
    House* buildHouse() override {
        return new WoodenHouse();
    }

    Fence* buildFence() override {
        return new WoodenFence();
    }

    Barn* buildBarn() override {
        return new WoodenBarn();
    }
};

class BrickDeveloper : public Developer {
public:
    House* buildHouse() override {
        return new BrickHouse();
    }

    Fence* buildFence() override {
        return new BrickFence();
    }

    Barn* buildBarn() override {
        return new BrickBarn();
    }
};

class ConcreteDeveloper : public Developer {
public:
    House* buildHouse() override {
        return new ConcreteHouse();
    }

    Fence* buildFence() override {
        return new ConcreteFence();
    }

    Barn* buildBarn() override {
        return new ConcreteBarn();
    }
};

// Класс для участка, который строится
class Neighborhood {
private:
    std::vector<House*> houses;
    std::vector<Fence*> fences;
    std::vector<Barn*> barns;
public:
    ~Neighborhood() {
        for (House* house : houses) delete house;
        for (Fence* fence : fences) delete fence;
        for (Barn* barn : barns) delete barn;
    }

    void addHouse(House* house) {
        houses.push_back(house);
    }

    void addFence(Fence* fence) {
        fences.push_back(fence);
    }

    void addBarn(Barn* barn) {
        barns.push_back(barn);
    }

    void construct() const {
        // Вызов конструктора для всех объектов
        for (const House* house : houses) house->construct();
        for (const Fence* fence : fences) fence->construct();
        for (const Barn* barn : barns) barn->construct();
    }
};

int main() {
    // Создаем конкретных застройщиков
    WoodenDeveloper woodenDeveloper;
    BrickDeveloper brickDeveloper;
    ConcreteDeveloper concreteDeveloper;

    // Создаем участок и добавляем объекты
    Neighborhood neighborhood;

    // Строим дома, заборы и сараи из разных материалов
    neighborhood.addHouse(woodenDeveloper.buildHouse());
    neighborhood.addFence(woodenDeveloper.buildFence());
    neighborhood.addBarn(woodenDeveloper.buildBarn());

    neighborhood.addHouse(brickDeveloper.buildHouse());
    neighborhood.addFence(brickDeveloper.buildFence());
    neighborhood.addBarn(brickDeveloper.buildBarn());

    neighborhood.addHouse(concreteDeveloper.buildHouse());
    neighborhood.addFence(concreteDeveloper.buildFence());
    neighborhood.addBarn(concreteDeveloper.buildBarn());

    // Строительство завершено, выводим результат
    std::cout << "\nConstruction completed for the neighborhood:\n";
    neighborhood.construct();

    return 0;
}
