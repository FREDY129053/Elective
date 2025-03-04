#include <iostream>
#include <string>

class Animal {
  private:
    int healthPoint;
    float moveSpeed;
    std::string livingEnv;
  public:
    Animal(int healthPoint, float moveSpeed, std::string livingEnv) {
      this->healthPoint = healthPoint;
      this->moveSpeed = moveSpeed;
      this->livingEnv = livingEnv;
    }

    int getHealthPoint() { return healthPoint; }
    float getMoveSpeed() { return moveSpeed; }
    std::string getLivingEnv() { return livingEnv; }

    void setHealthPoint(int healthPoint) { this->healthPoint = healthPoint; }
    void setMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }
    void setLivingEnv(std::string livingEnv) { this->livingEnv = livingEnv; }

    virtual void saySomething() = 0;
};


class Pigeon : public Animal{
  public:
    Pigeon(int health, float speed, std::string env) : Animal(health, speed, env) {};

    void fly() {
      std::cout << "I'm flying!" << std::endl;
    }

    void saySomething() override {
      std::cout << "I'm a pigeon!" << std::endl;
    }
};

class Dog : public Animal {
  public:
    Dog(int health, float speed, std::string env) : Animal(health, speed, env) {};

    void walk() {
      std::cout << "I'm walk!" << std::endl;
    }

    void saySomething() override {
      std::cout << "I'm a dog!" << std::endl;
    }
};

class Dolphin : public Animal {
  private:
    int IQ;
  public:
    Dolphin(int health, float speed, std::string env, int iq) : Animal(health, speed, env) {
      this->IQ = iq;
    };

    void swim() {
      std::cout << "I'm swim!" << std::endl;
    }

    void saySomething() override {
      std::cout << "I'm a dolphin!" << std::endl;
    }
};



int main() {
  Pigeon Nastya = Pigeon(100, 20.0, "Air");
  Dog Alina = Dog(200, 20.0, "Earth");
  Dolphin Rodion = Dolphin(300, 20.0, "Water", 200);

  // std::cout << DIMA.getIQ();
  Nastya.saySomething();
  Alina.saySomething();
  Rodion.saySomething();

  std::cout << std::endl;

  Nastya.fly();
  Alina.walk();
  Rodion.swim();

  return 0;
}