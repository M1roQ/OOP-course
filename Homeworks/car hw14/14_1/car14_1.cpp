#include <iostream>
#include <memory>
#include <stdexcept>

// Абстрактный класс Стратегия для расчёта скорости
class GearStrategy {
public:
    virtual ~GearStrategy() = default;
    virtual double calculateSpeed(double rpm) const = 0;
    virtual int getGearNumber() const = 0;
};

// Конкретные стратегии для каждой передачи
class NeutralGear : public GearStrategy {
public:
    double calculateSpeed(double rpm) const override {
        return 0.0; // Нейтральная передача - скорость всегда 0
    }

    int getGearNumber() const override {
        return 0; // Нейтральная передача
    }
};

class ReverseGear : public GearStrategy {
public:
    double calculateSpeed(double rpm) const override {
        return -0.02 * rpm; // Задняя передача - отрицательная скорость
    }

    int getGearNumber() const override {
        return -1; // Задняя передача
    }
};

class ForwardGear : public GearStrategy {
private:
    int gear;
public:
    explicit ForwardGear(int gear) {
        try {
            if (gear < 1 || gear > 5) {
                throw std::invalid_argument("Передача должна быть в диапазоне от 1 до 5. Сброс скорости.");
            }
            this->gear = gear;
        } catch (const std::exception& ex) {
            std::cerr << "Ошибка: " << ex.what() << std::endl;
            this->gear = 0;  // Переходим на нейтральную передачу по умолчанию
        }
    }

    double calculateSpeed(double rpm) const override {
        return gear == 0 ? 0 : 0.1 * gear * rpm; // Если передача 0, скорость 0
    }

    int getGearNumber() const override {
        return gear; // Возвращаем номер передачи
    }
};

// Класс автомобиля
class Car {
private:
    std::unique_ptr<GearStrategy> strategy; // Текущая стратегия передачи
    double engineRPM; // Частота вращения двигателя
    double speed; // Текущая скорость автомобиля

public:
    Car() : strategy(std::make_unique<NeutralGear>()), engineRPM(0.0), speed(0.0) {}

    // Установить частоту вращения двигателя
    void setEngineRPM(double rpm) {
        try {
            if (rpm < 0) {
                throw std::invalid_argument("RPM не может быть отрицательным");
            }
            engineRPM = rpm;
            speed = strategy->calculateSpeed(engineRPM);
        } catch (const std::exception& ex) {
            std::cerr << "Ошибка: " << ex.what() << std::endl;
        }
    }

    // Изменить стратегию передачи
    void changeGear(std::unique_ptr<GearStrategy> newStrategy) {
        try {
            strategy = std::move(newStrategy);
            speed = strategy->calculateSpeed(engineRPM);
        } catch (const std::exception& ex) {
            std::cerr << "Ошибка: " << ex.what() << std::endl;
        }
    }

    // Получить текущую скорость
    double getSpeed() const {
        return speed;
    }

    // Получить текущую передачу (числовое значение)
    int getGear() const {
        return strategy->getGearNumber();
    }
};

int main() {
    Car myCar;

    myCar.setEngineRPM(3000);

    // Переключаемся на первую передачу

    std::cout << "Передача 1: " << std::endl;
    myCar.changeGear(std::make_unique<ForwardGear>(1));
    std::cout << "Передача: " << myCar.getGear() << ", Скорость: " << myCar.getSpeed() << " км/ч\n" << std::endl;

    // Переключаемся на третью передачу
    std::cout << "Передача 3: " << std::endl;
    myCar.changeGear(std::make_unique<ForwardGear>(3));
    std::cout << "Передача: " << myCar.getGear() << ", Скорость: " << myCar.getSpeed() << " км/ч\n" << std::endl;

    // Переключаемся на некорректную передачу (ошибка)
    std::cout << "Передача 0: " << std::endl;
    myCar.changeGear(std::make_unique<ForwardGear>(0));  // Ошибка: передача 0
    std::cout << "Передача: " << myCar.getGear() << ", Скорость: " << myCar.getSpeed() << " км/ч\n" << std::endl;

    // Переключаемся на несуществующую передачу (ошибка)
    std::cout << "Передача 6: " << std::endl;
    myCar.changeGear(std::make_unique<ForwardGear>(6));  // Ошибка: передача 6
    std::cout << "Передача: " << myCar.getGear() << ", Скорость: " << myCar.getSpeed() << " км/ч\n" << std::endl;

    // Переключаемся на заднюю передачу
    std::cout << "Передача задняя: " << std::endl;
    myCar.changeGear(std::make_unique<ReverseGear>());
    std::cout << "Передача: " << myCar.getGear() << ", Скорость: " << myCar.getSpeed() << " км/ч\n" << std::endl;

    // Изменяем частоту вращения двигателя
    std::cout << "Частота 1500: " << std::endl;
    myCar.setEngineRPM(1500);
    std::cout << "Передача: " << myCar.getGear() << ", Скорость: " << myCar.getSpeed() << " км/ч\n" << std::endl;

    // Изменяем частоту вращения на отрицательную
    std::cout << "Частота -500: " << std::endl;
    myCar.setEngineRPM(-500);  // Ошибка: отрицательное значение RPM
    std::cout << "Передача: " << myCar.getGear() << ", Скорость: " << myCar.getSpeed() << " км/ч\n" << std::endl;

    // Переключаемся на нейтральную передачу
    std::cout << "Передача нейтральная: " << std::endl;
    myCar.changeGear(std::make_unique<NeutralGear>());
    std::cout << "Передача: " << myCar.getGear() << ", Скорость: " << myCar.getSpeed() << " км/ч\n" << std::endl;

    return 0;
}
