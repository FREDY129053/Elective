#include <iostream>
#include <string>

/* 
  Следующая важная вещь в ООП это наследование.
  Наследование позволяет создавать новые классы, на основе уже существующих.

  Мы уже создали в прошлом файле класс Animal, но он не позволял вывести информацию как в первом файле(с помощью static)

  С помощью наследования мы можем перенять все атрибуты и методы у Animal и создать у каждого класса свой метод titlePrint()
*/

// Создадим общий класс, от которого все будут наследоваться
class Animal {
  // Объявляем защищенные переменные, которые будут доступны у потомков
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

// Наследуемся и создаем метод для вывода заголовка
class Pigeon : public Animal {
  public:
    Pigeon(int hp, float speed, std::string env) : Animal(hp, speed, env) {}  // Вызываем конструктор родителя

    static void titlePrint() {
      std::cout << "\tPIGEON INFO:" << std::endl;
    }
};

class Dog : public Animal {
  public:
    Dog(int hp, float speed, std::string env) : Animal(hp, speed, env) {}

    static void titlePrint() {
      std::cout << "\tDOG INFO:" << std::endl;
    }
};

class Dolphin : public Animal {
  public:
    Dolphin(int hp, float speed, std::string env) : Animal(hp, speed, env) {}

    static void titlePrint() {
      std::cout << "\tDOLPHIN INFO:" << std::endl;
    }
};

int main() {
  // Создаем экземпляры классов
  Pigeon pigeon = Pigeon(100, 40, "Air");
  Dog dog = Dog(90, 25, "Earth");
  Dolphin dolphin = Dolphin(65, 70, "Water");

  // Выводим информацию о голубе
  Pigeon::titlePrint();  // Используем статический метод
  std::cout << "Pigeon health: " << pigeon.getHealth() << std::endl;
  std::cout << "Pigeon speed: " << pigeon.getSpeed() << std::endl;
  pigeon.animalInfo();
  std::cout << std::endl;

  // Выводим информацию о собаке
  Dog::titlePrint();  // Используем статический метод
  std::cout << "Dog health: " << dog.getHealth() << std::endl;
  std::cout << "Dog speed: " << dog.getSpeed() << std::endl;
  dog.animalInfo();
  std::cout << std::endl;

  // Выводим информацию о дельфине
  Dolphin::titlePrint();  // Используем статический метод
  std::cout << "Dolphin health: " << dolphin.getHealth() << std::endl;
  std::cout << "Dolphin speed: " << dolphin.getSpeed() << std::endl;
  dolphin.animalInfo();
  std::cout << std::endl;

  return 0;
}


// 77 строк в первом файле VS 59 строк в текущем файле. Удобно)