#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Продукт 1 - Дом
class House {
private:
    std::vector<std::string> parts;
public:
    void addPart(const std::string& part) {
        parts.push_back(part);
    }

    void show() const {
        std::cout << "House parts:\n";
        for (const auto& part : parts) {
            std::cout << " - " << part << "\n";
        }
    }
};

// Продукт 2 - Документация
class Documentation {
private:
    std::vector<std::string> pages;
public:
    void addPage(const std::string& page) {
        pages.push_back(page);
    }

    void show() const {
        std::cout << "Documentation:\n";
        for (const auto& page : pages) {
            std::cout << " - " << page << "\n";
        }
    }
};

// Абстрактный строитель
class HouseBuilder {
protected:
    std::unique_ptr<House> house;
    std::unique_ptr<Documentation> documentation;
public:
    virtual ~HouseBuilder() {}

    void createNewHouse() {
        house = std::make_unique<House>();
        documentation = std::make_unique<Documentation>();
    }

    virtual void buildWalls() = 0;
    virtual void buildFloor() = 0;
    virtual void buildRoof() = 0;

    std::unique_ptr<House> getHouse() {
        return std::move(house);
    }

    std::unique_ptr<Documentation> getDocumentation() {
        return std::move(documentation);
    }
};

// Конкретный строитель - Деревянный дом
class WoodenHouseBuilder : public HouseBuilder {
public:
    void buildWalls() override {
        house->addPart("Wooden Walls");
        documentation->addPage("Wooden walls are made of oak.");
    }

    void buildFloor() override {
        house->addPart("Wooden Floor");
        documentation->addPage("Wooden floor is polished and insulated.");
    }

    void buildRoof() override {
        house->addPart("Wooden Roof");
        documentation->addPage("Wooden roof is weatherproof.");
    }
};

// Конкретный строитель - Кирпичный дом
class BrickHouseBuilder : public HouseBuilder {
public:
    void buildWalls() override {
        house->addPart("Brick Walls");
        documentation->addPage("Brick walls are solid and provide excellent insulation.");
    }

    void buildFloor() override {
        house->addPart("Concrete Floor");
        documentation->addPage("Concrete floor is durable and reinforced.");
    }

    void buildRoof() override {
        house->addPart("Tile Roof");
        documentation->addPage("Tile roof is durable and fireproof.");
    }
};

// Конкретный строитель - Бетонный дом
class ConcreteHouseBuilder : public HouseBuilder {
public:
    void buildWalls() override {
        house->addPart("Concrete Walls");
        documentation->addPage("Concrete walls provide high durability and soundproofing.");
    }

    void buildFloor() override {
        house->addPart("Concrete Floor");
        documentation->addPage("Concrete floor is polished and smooth.");
    }

    void buildRoof() override {
        house->addPart("Concrete Roof");
        documentation->addPage("Concrete roof is reinforced and weather-resistant.");
    }
};

// Директор, управляющий процессом строительства
class Director {
private:
    HouseBuilder* builder;
public:
    void setBuilder(HouseBuilder* b) {
        builder = b;
    }

    void constructHouse() {
        builder->createNewHouse();
        builder->buildWalls();
        builder->buildFloor();
        builder->buildRoof();
    }
};

int main() {
    Director director;

    WoodenHouseBuilder woodenBuilder;
    BrickHouseBuilder brickBuilder;
    ConcreteHouseBuilder concreteBuilder;

    // Строительство деревянного дома
    director.setBuilder(&woodenBuilder);
    director.constructHouse();

    std::unique_ptr<House> woodenHouse = woodenBuilder.getHouse();
    std::unique_ptr<Documentation> woodenDocs = woodenBuilder.getDocumentation();

    woodenHouse->show();
    woodenDocs->show();

    std::cout << "\n";

    // Строительство кирпичного дома
    director.setBuilder(&brickBuilder);
    director.constructHouse();

    std::unique_ptr<House> brickHouse = brickBuilder.getHouse();
    std::unique_ptr<Documentation> brickDocs = brickBuilder.getDocumentation();

    brickHouse->show();
    brickDocs->show();

    std::cout << "\n";

    // Строительство бетонного дома
    director.setBuilder(&concreteBuilder);
    director.constructHouse();

    std::unique_ptr<House> concreteHouse = concreteBuilder.getHouse();
    std::unique_ptr<Documentation> concreteDocs = concreteBuilder.getDocumentation();

    concreteHouse->show();
    concreteDocs->show();

    return 0;
}
