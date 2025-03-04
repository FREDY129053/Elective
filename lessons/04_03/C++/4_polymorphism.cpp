#include <iostream>
#include <string>
#include <vector>
#include <memory>  // GPT сказал для памяти

// Создадим общий АБСТРАКТНЫЙ класс, от которого все будут наследоваться
// Это еще один уровень абстракции

/*
  По сути это значит:
    Я создам класс Animal в котором укажу все методы, которые нужно перезаписать в его потомках

  Абстрактный класс удобен, чтобы понять что будет реализовываться
*/
class Animal {
  protected:
    int healthPoint;
    float moveSpeed; 
    std::string livingEnv;  

  public:
    Animal(int hp, float speed, std::string env) : healthPoint(hp), moveSpeed(speed), livingEnv(env) {}

    // Ключево слово virtual для обозначения функций, которые будут переопределены в дочерних класса

    /*
      = 0 говорит компилятору, что у этого метода нет реализации в базовом классе, и он обязательно должен быть переопределен в классе-наследнике.

      Такие классы с хотя бы одним = 0 называются абстрактными, и их нельзя создавать напрямую!
      Пример:
        Animal a(100, 2.5, "land");  // Ошибка! Нельзя создать объект абстрактного класса

      Но можно создать объект наследника, который переопределит все = 0 методы.
    */

    virtual int getHealth() const = 0;
    virtual void setHealth(int health) = 0;
    
    virtual int getSpeed() const = 0;
    virtual void setSpeed(int speed) = 0;

    virtual void animalInfo() = 0;

    virtual void saySomething() = 0; 

    virtual ~Animal() = default;  // Деструктор, для очистки памяти, в С++ же нет сборщика мусора😒
};

class Pigeon : public Animal {
  public:
    Pigeon(int hp, float speed, std::string env) : Animal(hp, speed, env) {}

    // Ключевое слово override позволяет "переписать" функцию в дочернем классе и сделать иную реализацию

    int getHealth() const override {
      return healthPoint * 100;
    }
    void setHealth(int health) override{
      healthPoint = health / 100;
    }

    int getSpeed() const override {
      return moveSpeed * 10;
    }
    void setSpeed(int speed) override{
      moveSpeed = speed / 10;
    }

    void animalInfo() override{
      std::cout << "Animal lives in " << livingEnv << std::endl;
    }

    void saySomething() override {
      std::cout << "Pigeon says: Cock-a-doodle-doo!" << std::endl;
    }
};

class Dog : public Animal {
  public:
    Dog(int hp, float speed, std::string env) : Animal(hp, speed, env) {}

    int getHealth() const override {
      return healthPoint * 2;
    }
    void setHealth(int health) override{
      healthPoint = health / 2;
    }

    int getSpeed() const override {
      return moveSpeed * 15;
    }
    void setSpeed(int speed) override{
      moveSpeed = speed / 15;
    }

    void animalInfo() override{
      std::cout << "Animal lives in " << livingEnv << std::endl;
    }

    void saySomething() override {
      std::cout << "Dog says: Gav-gav-no!" << std::endl;
    }
};

class Dolphin : public Animal {
  public:
    Dolphin(int hp, float speed, std::string env) : Animal(hp, speed, env) {}

    int getHealth() const override {
      return healthPoint * 3;
    }
    void setHealth(int health)override {
      healthPoint = health / 3;
    }

    int getSpeed() const override {
      return moveSpeed * 2345678;
    }
    void setSpeed(int speed) override{
      moveSpeed = speed / 2345678;
    }

    void animalInfo() override{
      std::cout << "Animal lives in " << livingEnv << std::endl;
    }

    void saySomething() override {
      std::cout << "Dolphin says: F*ck Microsoft!" << std::endl;
    }
};

int main() {
  /*
    Изначально было так:
    std::vector<Animal*> animals = { new Pigeon(), new Dog(), new Dolphin() };
    ...
    for (auto& animal : animals) {
      delete animal;
    }

    Но GPT сказал поменять, чтобы автоматически чистить память:
      👉 Вывод: Используй unique_ptr и не парься с delete! 🚀
  */
  std::vector<std::unique_ptr<Animal>> animals;
  animals.push_back(std::make_unique<Pigeon>(100, 23.5, "Air"));
  animals.push_back(std::make_unique<Dog>(20, 12.2, "Earth"));
  animals.push_back(std::make_unique<Dolphin>(300, 45.6, "Water"));

  for (const auto& animal : animals) {
    animal->animalInfo();
    animal->saySomething();
    std::cout << "Health: " << animal->getHealth() << std::endl;
    std::cout << "Speed: " << animal->getSpeed() << std::endl;
    std::cout << std::endl;
  }

  return 0;
}

// Абстракция страннная вещь - ее может быть много и тогда будет плохо, ее может быть мало и тогда будет плохо
// По наитию надо делать)