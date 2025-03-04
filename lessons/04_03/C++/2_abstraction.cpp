#include <iostream>
#include <string>

/* 
  В прошлом файле получилось ОЧЕНЬ много кода, который повторяется.
  Данную проблему поможет решить наследование.

  Голубь, собака и дельфин - животные. Это их объединяет, у них общий класс "Животное"
*/

// Создадим общий класс для всех
class Animal {
  protected:
    int healthPoint;  // Здоровье
    float moveSpeed;  // Скорость движения
    std::string livingEnv;  // Среда обитания

  public:
    Animal(int hp, float speed, std::string env) : healthPoint(hp), moveSpeed(speed), livingEnv(env) {}

    int getHealth() const { return healthPoint; }
    void setHealth(int health) { healthPoint = health; }
    
    int getSpeed() const { return moveSpeed; }
    void setSpeed(int speed) { moveSpeed = speed; }

    void animalInfo() {
      std::cout << "Animal lives in " << livingEnv << std::endl;
    }
};

int main() {
  // Создаем экземпляры классов
  Animal pigeon = Animal(100, 40, "Air");
  Animal dog = Animal(90, 25, "Earth");
  Animal dolphin = Animal(65, 70, "Water");

  // Выводим информацию о голубе
  std::cout << "\tPigeon INFO:" << std::endl;
  std::cout << "Pigeon health: " << pigeon.getHealth() << std::endl;
  std::cout << "Pigeon speed: " << pigeon.getSpeed() << std::endl;
  pigeon.animalInfo();
  std::cout << std::endl;

  // Выводим информацию о собаке
  std::cout << "\tDOG INFO:" << std::endl;
  std::cout << "Dog health: " << dog.getHealth() << std::endl;
  std::cout << "Dog speed: " << dog.getSpeed() << std::endl;
  dog.animalInfo();
  std::cout << std::endl;

  // Выводим информацию о дельфине
  std::cout << "\tDOLPHIN INFO:" << std::endl;
  std::cout << "Dolphin health: " << dolphin.getHealth() << std::endl;
  std::cout << "Dolphin speed: " << dolphin.getSpeed() << std::endl;
  dolphin.animalInfo();
  std::cout << std::endl;

  return 0;
}