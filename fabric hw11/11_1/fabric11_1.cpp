#include <iostream>
#include <vector>

class Building {
protected:
    static unsigned id_counter;
public:
    virtual ~Building() {}
    virtual void construct() = 0;
};

unsigned Building::id_counter = 1;

class WoodenHouse : public Building {
public:
    void construct() override {
        std::cout << "Constructing wooden house with ID [" << id_counter++ << "]...\n";
    }
};

class BrickHouse : public Building {
public:
    void construct() override {
        std::cout << "Constructing brick house with ID [" << id_counter++ << "]...\n";
    }
};

class ConcreteHouse : public Building {
public:
    void construct() override {
        std::cout << "Constructing concrete house with ID [" << id_counter++ << "]...\n";
    }
};

class Builder {
public:
    virtual ~Builder() {}
    virtual Building* createBuilding() = 0;
};

class WoodenBuilder : public Builder {
public:
    Building* createBuilding() override {
        return new WoodenHouse();
    }
};

class BrickBuilder : public Builder {
public:
    Building* createBuilding() override {
        return new BrickHouse();
    }
};

class ConcreteBuilder : public Builder {
public:
    Building* createBuilding() override {
        return new ConcreteHouse();
    }
};

class Neighborhood {
private:
    std::vector<Building*> buildings;
public:
    Neighborhood(const std::vector<Building*>& building_list) : buildings(building_list) {}

    ~Neighborhood() {
        for (Building* building : buildings) {
            delete building;
        }
        buildings.clear();
    }

    Building* getBuilding(int index) const {
        return buildings[index];
    }

    const std::vector<Building*>& getAllBuildings() const {
        return buildings;
    }
};

Neighborhood createNeighborhood(Builder* builder, int count) {
    if (count < 4 || count > 16) {
        throw std::invalid_argument("Invalid number of buildings. Must be between 4 and 16.");
    }

    std::cout << "Starting construction of a neighborhood with " << count << " buildings:\n";
    std::vector<Building*> building_list;

    for (int i = 0; i < count; ++i) {
        Building* building = builder->createBuilding();
        building->construct();
        building_list.push_back(building);
    }

    std::cout << "Neighborhood construction complete.\n\n";
    return Neighborhood(building_list);
}

int main() {
    WoodenBuilder woodenBuilder;
    BrickBuilder brickBuilder;
    ConcreteBuilder concreteBuilder;

    try {
        createNeighborhood(&woodenBuilder, 5);
        createNeighborhood(&brickBuilder, 7);
        createNeighborhood(&concreteBuilder, 10);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
